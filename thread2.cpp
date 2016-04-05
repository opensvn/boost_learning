#include <iostream>
#include <boost/thread.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

boost::mutex mutex;
boost::condition_variable_any cond;
vector<int> random_numbers;

void wait(int seconds)
{
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void fill_()
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 5; ++i)
    {
        boost::unique_lock<boost::mutex> lock(mutex);
        random_numbers.push_back(rand() % 100);
        cout << "fill " << random_numbers.back() << endl;
        cond.notify_all();
        cond.wait(mutex);
    }
}

void print()
{
    size_t next_size = 1;
    for (int i = 0; i < 5; ++i)
    {
        boost::unique_lock<boost::mutex> lock(mutex);
        while (random_numbers.size() != next_size)
            cond.wait(mutex);
        cout << "print " << random_numbers.back() << endl;
        ++next_size;
        cond.notify_all();
    }
}

int sum = 0;

void count_()
{
    size_t next_size = 1;
    for (int i = 0; i < 5; ++i)
    {
        boost::unique_lock<boost::mutex> lock(mutex);
        while (random_numbers.size() != next_size)
            cond.wait(mutex);
        cout << "count " << random_numbers.back() << endl;
        ++next_size;
        sum += random_numbers.back();
        cond.notify_all();
    }
}

int main()
{
    boost::thread t1(fill_);
    boost::thread t2(print);
//    boost::thread t3(count_);
    t1.join();
    t2.join();
//    t3.join();

//    cout << "Sum: " << sum << endl;

    return 0;
}
