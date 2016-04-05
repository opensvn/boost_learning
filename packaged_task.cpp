#define BOOST_THREAD_PROVIDES_FUTURE

#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <utility>

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
    boost::packaged_task<int> task(accumulate);
    boost::future<int> f = task.get_future();
    boost::thread t(move(task));
    cout << f.get() << endl;
    return 0;
}
