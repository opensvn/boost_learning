#include <boost/thread.hpp>
#include <iostream>

using namespace std;

void wait(int seconds)
{
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void run()
{
    for (int i = 0; i < 5; ++i)
    {
        wait(1);
        cout << i << endl;
    }
}

int main()
{
    boost::thread t(run);
    t.join();
}
