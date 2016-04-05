#include <iostream>
#include <boost/array.hpp>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    typedef boost::array<string, 3> array;
    array a;
    a[0] = "Boris";
    a.at(1) = "Anton";
    *a.rbegin() = "Caesar";

    for (array::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << endl;

    sort(a.begin(), a.end());

    for (array::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << endl;

    cout << a.size() << " " << a.max_size() << endl;

    return 0;
}
