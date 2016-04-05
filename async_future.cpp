#define BOOST_THREAD_PROVIDES_FUTURE

#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

using namespace std;

int accumulate()
{
    int sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += i;
    return sum;
}

int main()
{
    boost::future<int> f = boost::async(accumulate);
    cout << f.get() << endl;
    return 0;
}
