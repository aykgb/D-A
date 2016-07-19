#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void erase_signed_r(string& str)
{
    if(str.front() == '-' || str.front() == '+')
        str.erase(str.begin());
}

string erase_signed(string str)
{
    if(str.front() == '-' || str.front() == '+')
        str.erase(str.begin());
    return str;
}


/* The convertion function will not care the sign byte.
 */
void digits2chars_r(string& str)
{
    std::for_each(str.begin(), str.end(), [](char &a) {
         a += '0';
    });
}

string digits2chars(string str)
{
    std::for_each(str.begin(), str.end(), [](char &a) {
        if(a >= 0 && a <= 9 ) a += '0';
    });
    return str;
}

void chars2digits_r(string& str)
{
    std::for_each(str.begin(), str.end(), [](char &a) {
        a -= '0';
    });
}

string chars2digits(string str)
{
    std::for_each(str.begin(), str.end(), [](char &a) {
        if(a >= '0' && a <= '9' ) a -= '0';
    });
    return str;
}

namespace BigNumber
{
/* 1. the low char corresponds the low digit, for example:
 *     in "12345", the '5' represents the number 50000
 *      and '1' represents the number 1.
 * 2. The parameter shall not include the signed.
 */
int _compare(string str1, string str2)
{
    if(str1.size() > str2.size())
        return 1;
    else if(str1.size() < str2.size())
        return -1;
    else
    {
        string::reverse_iterator it1 = str1.rbegin();
        string::reverse_iterator it2 = str2.rbegin();
        for(; it1 != str1.rend(); ++it1, ++it2)
        {
            if(*it1 > *it2) return 1;
            if(*it1 < *it2) return -1;
        }
        return 0;
    }
}

/* Basic addition
 * 1. Only allow the two positive digit addition
 * 2. Operate the really digit format
 * 3. The parameter lower digit is on ahead(the low digit aligned).
 */
string _add(string str1, string str2)
{
    if(_compare(str1, str2) < 0)
        std::swap(str1, str2);

    /* Addition by byte. */
    for(string::size_type i = 0; i < str2.size(); ++i)
        str1[i] += str2[i];

    /* Handle the carry. */
    for(string::size_type i = 0; i < str1.size(); ++i)
    {
        if(str1[i] > 9)
        {
            if(i < str1.size() - 1)
            {
                str1[i + 1] += str1[i] / 10;
                str1[i] = str1[i] % 10;
            }
            else
            {
                str1.push_back(str1[i] / 10);
                str1[i] = str1[i] % 10;
            }
        }
    }


    return str1;
}

/* Basic subtraction
 * 1. Only allow the situation that both str1 & str2 is positive and
 *    str1 - str2 >= 0
 * 2. Operate the really digit format
 * 3. The parameter lower digit is on ahead(keep low digit aligned).
 * 4. when the str1 == str2, it shall return "";
 */
string _minus(string str1, string str2)
{
    if(_compare(str1, str2) == 0)
//        return string(1, 0);
        return "";

    for(string::size_type i = 0; i < str2.size(); ++i)
    {
        if(str1[i] >= str2[i])
        {
            str1[i] -= str2[i];
        }
        else
        {
            /* Notice: the situation will not be present which
               the highest digit need a borrow. So that it will
               not cause index out of bound. */
            str1[i+1] -= 1;
            str1[i] -= str2[i] - 10;
        }
    }

    /* Eliminate redundant 0 */
#if 0
    while(str1.back() == 0 && str1.size() > 1)
        str1.pop_back();
#endif
    while(0 == str1.back())
        str1.pop_back();

    return str1;
}

bool _pretreatment(string &str)
{
    /* Check the signed. */
    bool sign = true;
    if(str.front() == '-') sign = false;

    /* Erase the signed charactor. */
    erase_signed_r(str);

    /* Convert to the real digit format. */
    chars2digits_r(str);

    /* keep the low digit aligned. */
    std::reverse(str.begin(), str.end());

    return sign;
}

// '+'
string add(string str1, string str2)
{
    bool sign = true;
    bool sign1 = _pretreatment(str1);
    bool sign2 = _pretreatment(str2);

    if(sign1 && sign2)
        str1 =  _add(str1, str2);
    if(!sign1 && !sign2)
    {
        str1 = _add(str1, str2);
        sign = false;
    }
    if(sign1 && !sign2)
    {
        if(_compare(str1, str2) >= 0)
        {
            str1 = _minus(str1, str2);
        }
        else
        {
            str1 = _minus(str2, str1);
            sign = false;
        }
    }
    if(!sign1 && sign2)
    {
        if(_compare(str1, str2) >= 0)
        {
            str1 = _minus(str1, str2);
            sign = false;
        }
        else
        {
            str1 = _minus(str2, str1);
        }
    }

    if(str1 == "") str1 = "0";
    if(!sign) str1.push_back('-');
    std::reverse(str1.begin(), str1.end());

    return str1;
}

// '-'
string minus(string str1, string str2)
{
    if(str2.front() == '-')
        str2.front() = '+';
    else if(str2.front() == '+')
        str2.front() = '-';
    else
        str2 = '-' + str2;

    return add(str1, str2);
}

/* 'x' --- multiplication--> dislocation --> addition
 * For example: 81 + 81 = 162 that the char type can't hold correctly.
 *  We can simply expand the digit by using _add() method.
 *         9  9  9  1
 *       x 9
 *       -------------
 *         81 81 81 9   <--- tmp
 *       + 0  0  0  0   <--- res
 *       -------------
 *      8  9  9  1  9   <--- res
 */
string multiple(string str1, string str2)
{
    bool sign1 = _pretreatment(str1);
    bool sign2 = _pretreatment(str2);

    /* Make sure the abs value of str1 is the bigger one. */
    if(_compare(str1, str2) < 0)
    {
        std::swap(sign1, sign2);
        std::swap(str1, str2);
    }

    string res(str1.size(), 0);
    for(string::size_type i = 0; i < str2.size(); ++i)
    {
        /* Simulate the single step of the multiplication. */
        string tmp;
        for(string::size_type j = 0; j < str1.size(); ++j)
            tmp.push_back(str1[j] * str2[i]);


        /* Keep the right dislocation. */
        for(string::size_type k = 0; k < i; ++k)
            tmp = static_cast<char>(0) + tmp;
        // std::cout << "tmp: " << digits2chars(tmp) << std::endl;;

        /* Accumulate the tmp to res in every loop. */
        res = _add(tmp, res);
        // std::cout << "res: " << digits2chars(res) << std::endl;
    }

    if( sign1 != sign2) res.push_back('-');
    std::reverse(res.begin(), res.end());

    return res;
}

/* 1. In this method, dividend ==  divisor x [0..9].
 *    So, the dividend.size() - divisor.size() == 0/1
 */
std::tuple<char, string> _try_quotient(string dividend, string divisor)
{
    if(_compare(dividend, divisor) < 0)
        return std::tuple<char, string>(0, dividend);  // Dividend is the remainder.

    char quotient = 1;
    dividend = _minus(dividend, divisor);
    while(_compare(dividend, divisor) >= 0)
    {
        quotient++;
        dividend = _minus(dividend, divisor);
    }

    return std::tuple<char, string>(quotient, dividend);
}

/*      1          30
 *    -----        -----
      9999|99      4321|123
        99         369
      -----        -----
      990          172
 */
std::tuple<string, string> divide(string dividend, string divisor)
{
    bool sign1 = _pretreatment(dividend);
    bool sign2 = _pretreatment(divisor);

    string quotient, remainder;
    if(_compare(dividend, divisor) < 0)
    {
        quotient = string(1, 0);
        remainder = divisor;
    }
    else if(_compare(dividend, divisor) == 0)
    {
        quotient = string(1, 1);
        remainder = string(1, 0);
    }
    else
    {
        /* Find the proper */
        int npos = dividend.size() - divisor.size();
        string div(dividend, npos, divisor.size());

        auto res = _try_quotient(div, divisor);
        while(npos > 0)
        {
            quotient.push_back(std::get<0>(res));
            div = dividend[--npos] + std::get<1>(res);
            res = _try_quotient(div, divisor);
        }

        quotient.push_back(std::get<0>(res));
        remainder = std::get<1>(res);
    }

    std::reverse(remainder.begin(), remainder.end());

    if(quotient.front() == 0 && quotient.size() > 1)
        quotient = string(quotient, 1, quotient.size() - 1);

    if("" == remainder) remainder.push_back(0);

    if(sign1 != sign2)
    {
        quotient = '-' + quotient;
        remainder = '-' + remainder;
    }


    return std::tuple<string, string>(quotient, remainder);
}

};


#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void print_elapsed_time(void)
{
    static struct timespec start;
    struct timespec curr;
    static int first_call = 1;
    int secs, nsecs;

    if (first_call)
    {
        first_call = 0;

        if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
            handle_error("clock_gettime");
    }

    if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
        handle_error("clock_gettime");

    secs = curr.tv_sec - start.tv_sec;
    nsecs = curr.tv_nsec - start.tv_nsec;

    if (nsecs < 0)
    {
        secs--;
        nsecs += 1000000000;
    }

    printf("## %d.%03d ##\n", secs, (nsecs + 500000) / 1000000);
}

int main(int argc, char* argv[])
{
    string str1;
    string str2;

    if(argc == 3)
    {
        str1.assign(argv[1]);
        str2.assign(argv[2]);
    }
    else
    {
        std::cout << "err: wrong number of parameter." << std::endl;
        return -1;
    }

    // std::cout << _compare(str1, str2) << std::endl;;

    // std::cout << digits2chars
    //   (
    //    BigNumber::_add(
    //                    chars2digits_r(std::move(str1)),
    //                    chars2digits_r(std::move(str2))
    //                    )
    //    )
    // << std::endl;
    // std::cout << str1 << " " << str2 << std::endl;

//    std::cout << digits2chars(BigNumber::_add(chars2digits(str1),
//                              chars2digits(str2))) << std::endl;
//    std::cout << digits2chars(BigNumber::_minus(chars2digits(str1),
//                              chars2digits(str2))) << std::endl;
    print_elapsed_time();
    std::cout << "str1 + str2 = " << digits2chars(BigNumber::add(str1, str2)) << std::endl;
    std::cout << "str1 - str2 = " << digits2chars(BigNumber::minus(str1, str2)) << std::endl;
    std::cout << "str2 - str1 = " << digits2chars(BigNumber::minus(str2, str1)) << std::endl;

    std::cout << "str1 * str2 = " << digits2chars(BigNumber::multiple(str1, str2)) << std::endl;

    std::cout << "str1 / str2 = " << digits2chars(std::get<0>(BigNumber::divide(str1, str2)))
              << std::endl;
    std::cout << "str1 % str2 = " << digits2chars(std::get<1>(BigNumber::divide(str1, str2)))
              << std::endl;

    std::cout << "str2 / str1 = " << digits2chars(std::get<0>(BigNumber::divide(str2, str1)))
              << std::endl;
    std::cout << "str2 % str1 = " << digits2chars(std::get<1>(BigNumber::divide(str2, str1)))
              << std::endl;
    print_elapsed_time();

    return 0;

}
