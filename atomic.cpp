#include <iostream>
#include <boost/atomic.hpp>
#include <thread>

using namespace std;

boost::atomic<int> a{0};

void thread()
{
    ++a;
}

int main()
{
    std::thread t1{thread};
    std::thread t2{thread};
    t1.join();
    t2.join();
    cout << a << endl;
    return 0;
}
