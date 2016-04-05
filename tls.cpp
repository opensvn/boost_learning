#include <iostream>
#include <boost/thread.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;

void init_number_generator()
{
    static bool done = false;
    if (!done)
    {
        done = true;
        srand(static_cast<unsigned int>(time(0)));
    }
}

void init_number_generator2()
{
    static boost::thread_specific_ptr<bool> tls;
    if (!tls.get())
        tls.reset(new bool(false));
    if (!*tls)
    {
        *tls = true;
        srand(static_cast<unsigned int>(time(0)));
    }
}

boost::mutex mutex;

void random_number_generator()
{
//    init_number_generator();
    init_number_generator2();
    int i = rand();
    boost::lock_guard<boost::mutex> lock(mutex);
    cout << i << endl;
}

int main()
{
    boost::thread t[3];

    for (int i = 0; i < 3; ++i)
        t[i] = boost::thread(random_number_generator);

    for (int i = 0; i < 3; ++i)
        t[i].join();

    return 0;
}
