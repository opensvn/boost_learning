#include <iostream>
#include <stack>
#include <boost/thread.hpp>

using namespace std;

boost::mutex io_mu;

class Buffer
{
private:
    boost::mutex mu;
    boost::condition_variable_any cond_put;
    boost::condition_variable_any cond_get;
    stack<int> stk;
    int un_read, capacity;
    bool is_full() { return un_read == capacity; }
    bool is_empty() { return un_read == 0; }
public:
    Buffer(size_t n): un_read(0), capacity(n) {}
    void put(int x)
    {
        {
            boost::mutex::scoped_lock lock(mu);
            while (is_full())
            {
                {
                    boost::mutex::scoped_lock lock(io_mu);
                    cout << "full waiting..." << endl;
                }
                cond_put.wait(mu);
            }
            stk.push(x);
            ++un_read;
        }
        cond_get.notify_one();
    }

    void get(int *x)
    {
        {
            boost::mutex::scoped_lock lock(mu);
            while (is_empty())
            {
                {
                    boost::mutex::scoped_lock lock(io_mu);
                    cout << "empty waiting..." << endl;
                }
                cond_get.wait(mu);
            }
            --un_read;
            *x = stk.top();
            stk.pop();
        }
        cond_put.notify_one();
    }
};

Buffer buf(5);

void producer(int n)
{
    for (int i = 0; i < n; ++i)
    {
        buf.put(i);
        {
            boost::mutex::scoped_lock lock(io_mu);
            cout << "put " << i << endl;
        }
    }
}

void consumer(int n)
{
    int x;
    for (int i = 0; i < n; ++i)
    {
        buf.get(&x);
        boost::mutex::scoped_lock lock(io_mu);
        cout << boost::this_thread::get_id() << " get " << x << endl;
    }
}

int main()
{
    boost::thread t1(producer, 20);
    boost::thread t2(consumer, 10);
    boost::thread t3(consumer, 10);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
