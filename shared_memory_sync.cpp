#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace std;

int main()
{
    boost::interprocess::managed_shared_memory managed_shm(
            boost::interprocess::open_or_create,
            "shm", 1024);

    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx");
    boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd");
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);

    while (*i < 10)
    {
        if (*i % 2 == 0)
        {
            ++(*i);
            named_cnd.notify_all();
            named_cnd.wait(lock);
        }
        else
        {
            cout << *i << endl;
            ++(*i);
            named_cnd.notify_all();
            named_cnd.wait(lock);
        }
    }

    named_cnd.notify_all();
//    named_mtx.lock();
//    boost::interprocess::interprocess_mutex *mtx =
//        managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")();

//    mtx->lock();
//    ++(*i);
//    cout << *i << endl;
//    mtx->unlock();
//    named_mtx.unlock();

    boost::interprocess::shared_memory_object::remove("shm");
    boost::interprocess::named_mutex::remove("mtx");
    boost::interprocess::named_condition::remove("cnd");

    return 0;
}
