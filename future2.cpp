#include <iostream>
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
    boost::packaged_task<int> pt(boost::bind(fab, 10));
    boost::unique_future<int> uf = pt.get_future();
    boost::thread(boost::move(pt));
    uf.wait();
    assert(uf.is_ready() && uf.has_value());
    cout << uf.get() << endl;
    return 0;
}
