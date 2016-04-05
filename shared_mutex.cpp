#include <iostream>
#include <boost/thread.hpp>

using namespace std;

boost::mutex io_mu;

class rw_data
{
private:
    int m_x;
    boost::shared_mutex rw_mu;
public:
    rw_data() : m_x(0)
    { }

    void write()
    {
        boost::unique_lock<boost::shared_mutex> ul(rw_mu);
        ++m_x;
    }

    void read(int *x)
    {
        boost::shared_lock<boost::shared_mutex> sl(rw_mu);
        *x = m_x;
    }

    int get_value()
    { return m_x; }
};

void writer(rw_data &d)
{
    for (int i = 0; i < 20; ++i)
    {
        boost::this_thread::sleep(boost::posix_time::millisec(10));
        d.write();
        boost::mutex::scoped_lock lock(io_mu);
        cout << boost::this_thread::get_id() << " write " << d.get_value() << endl;
    }
}

void reader(rw_data &d)
{
    int x;
    for (int i = 0; i < 10; ++i)
    {
        boost::this_thread::sleep(boost::posix_time::millisec(5));
        d.read(&x);
        boost::mutex::scoped_lock lock(io_mu);
        cout << boost::this_thread::get_id() << " reader: " << x << endl;
    }
}

int main()
{
    rw_data d;
    boost::thread_group pool;

    for (int i = 0; i < 4; ++i)
        pool.create_thread(bind(reader, boost::ref(d)));

    for (int i = 0; i < 2; ++i)
        pool.create_thread(bind(writer, boost::ref(d)));

    pool.join_all();

    return 0;
}
