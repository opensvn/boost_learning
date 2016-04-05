#include <iostream>
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

using namespace std;

int fab(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return fab(n - 1) + fab(n - 2);
}

int main()
{
    typedef boost::packaged_task<int> pti_t;
    typedef boost::unique_future<int> ufi_t;

    boost::array<pti_t, 5> ap;
    boost::array<ufi_t, 5> au;

    for (int i = 0; i < 5; ++i)
    {
        ap[i] = pti_t(boost::bind(fab, i + 10));
        au[i] = ap[i].get_future();
        boost::thread(boost::move(ap[i]));
    }
//    boost::wait_for_all(au.begin(), au.end());
//    BOOST_FOREACH(ufi_t &uf, au)
//    {
//        cout << uf.get() << endl;
//    }

    boost::wait_for_any(au[3], au[4], au[2]);
    BOOST_FOREACH(ufi_t &uf, au)
    {
        if (uf.is_ready() && uf.has_value())
            cout << uf.get() << endl;
    }
    return 0;
}
