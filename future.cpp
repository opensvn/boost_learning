#define BOOST_THREAD_PROVIDES_FUTURE

#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <functional>

using namespace std;

void accumulate(boost::promise<int> &p)
{
    int sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += i;
    p.set_value(sum);
}

int main()
{
    boost::promise<int> p;
    boost::future<int> f = p.get_future();
//    cout << f.get() << endl; // get() will block until a value stored in promise p.
    boost::thread t(accumulate, ref(p));
    cout << f.get() << endl;
    return 0;
}
