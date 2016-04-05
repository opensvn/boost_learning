#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace std;

boost::uint64_t sa[10] = {0};

void calc1()
{
    for (int i = 0; i < 100000000; ++i)
        sa[0] += i;
}

void calc2()
{
    for (int i = 100000000; i < 200000000; ++i)
        sa[1] += i;
}

void calc3()
{
    for (int i = 200000000; i < 300000000; ++i)
        sa[2] += i;
}

void calc4()
{
    for (int i = 300000000; i < 400000000; ++i)
        sa[3] += i;
}

void calc5()
{
    for (int i = 400000000; i < 500000000; ++i)
        sa[4] += i;
}

void calc6()
{
    for (int i = 500000000; i < 600000000; ++i)
        sa[5] += i;
}

void calc7()
{
    for (int i = 600000000; i < 700000000; ++i)
        sa[6] += i;
}

void calc8()
{
    for (int i = 700000000; i < 800000000; ++i)
        sa[7] += i;
}

void calc9()
{
    for (int i = 800000000; i < 900000000; ++i)
        sa[8] += i;
}

void calc10()
{
    for (int i = 900000000; i < 1000000000; ++i)
        sa[9] += i;
}

int main()
{
    boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();

    boost::thread ta[10];
    typedef void (*FA)();
    FA fa[10] = {calc1, calc2, calc3, calc4, calc5, calc6,
                 calc7, calc8, calc9, calc10};

    for (int i = 0; i < 10; ++i)
        ta[i] = boost::thread(fa[i]);

    for (int i = 0; i < 10; ++i)
        ta[i].join();

    boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();

    cout << "Elapse time: " << end - start << endl;
    boost::uint64_t sum = 0;
    for (int i = 0; i < 10; ++i)
        sum += sa[i];
    cout << "Sum = " << sum << endl;

    return 0;
}
