#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/once.hpp>
#include <boost/thread/barrier.hpp>
#include <string>

using namespace std;

template <typename T>
class basic_atom: boost::noncopyable
{
private:
    T n;
    typedef boost::mutex mutex_t;
    mutex_t mu;
public:
    basic_atom(T x = T()): n(x) {}
    T operator++()
    {
        mutex_t::scoped_lock lock(mu);
        return ++n;
    }
    operator T() { return n; }
};

typedef basic_atom<int> atom_int;

static int g_count;
void init_count()
{
    cout << "should call once." << endl;
    g_count = 0;
}

boost::once_flag of = BOOST_ONCE_INIT;
void call_func()
{
    boost::call_once(of, init_count);
}

boost::barrier br(5);
boost::mutex io_mu;

void printing(atom_int &x)
{
    {
        boost::mutex::scoped_lock lock(io_mu);
        cout << "thread " << ++x << " arrived barrier." << endl;
    }
    br.wait();

    boost::mutex::scoped_lock lock(io_mu);
    cout << "thread run." << endl;
}

void end_msg(const string &msg)
{
    cout << msg << endl;
}

void tss_printing()
{
    boost::thread_specific_ptr<int> pi;
    pi.reset(new int());

    ++(*pi);
    boost::mutex::scoped_lock lock(io_mu);
    cout << "thread v=" << *pi << endl;

    boost::this_thread::at_thread_exit(boost::bind(end_msg, "end"));
}

int main()
{
    (boost::thread(call_func));
    boost::thread(call_func);

    boost::this_thread::sleep(boost::posix_time::seconds(1));

    atom_int x;
    boost::thread_group tg;
    for (int i = 0; i < 5; ++i)
        tg.create_thread(boost::bind(printing, boost::ref(x)));
    tg.join_all();

    (boost::thread(tss_printing));
    (boost::thread(tss_printing));
    boost::this_thread::sleep(boost::posix_time::seconds(1));

    return 0;
}
