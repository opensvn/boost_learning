#include <iostream>
#include <vector>
#include <boost/progress.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

using namespace std;

int main()
{
    vector<int> v(100);
    boost::progress_display pd(v.size());

    vector<int>::iterator pos;
    for (pos = v.begin(); pos != v.end(); ++pos)
    {
        ++pd;
        // if someone else uses ostream, progress_display behaves stupid as below.
//        cout << pos - v.begin() << endl;
//        pd.restart(v.size());
//        pd += (pos - v.begin() + 1);
        boost::this_thread::sleep(boost::posix_time::millisec(200));
    }

    return 0;
}
