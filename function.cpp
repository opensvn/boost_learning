#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <boost/signal.hpp>
#include <cstdlib>
#include <cstring>

using namespace std;

class Add: public binary_function<int, int, void> {
public:
    void operator()(int i, int j) const {
        cout << i + j << endl;
    }
};

class DivideBy: public binary_function<int, int, int> {
public:
    int operator()(int n, int div) const {
        return n / div;
    }
};

void add(int i, int j) {
    cout << i + j << endl;
}

void add(int i, int j, ostream& os) {
    os << i + j << endl;
}

void print(int i) {
    cout << i << endl;
}

bool compare(int i, int j) {
    return i > j;
}

struct World {
    void hello(ostream& os) {
        os << "Hello, world!" << endl;
    }
};

void func() {
    cout << "Hello, signal!" << endl;
}

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);

//    for_each(v.begin(), v.end(), print);
//    for_each(v.begin(), v.end(), bind1st(Add(), 10));
    sort(v.begin(), v.end(), boost::bind(compare, _2, _1));
    for_each(v.begin(), v.end(), cout << boost::lambda::_1 << "\n");
    for_each(v.begin(), v.end(), boost::lambda::if_then(boost::lambda::_1 > 1,
                                                        cout << boost::lambda::_1));
    for_each(v.begin(), v.end(), boost::bind(add, 10, _1));
    for_each(v.begin(), v.end(), boost::bind(add, 10, _1, boost::ref(cout)));

    boost::function<int (const char*)> f = atoi;
    cout << f("1609") << endl;
    f = strlen;
    cout << f("1609") << endl;

    f = NULL;
    try {
//        f("");
    }
    catch (boost::bad_function_call& ex) {
        cout << ex.what() << endl;
    }
    boost::function<void (World*, ostream&)> f2 = &World::hello;
    World w;
    f2(&w, boost::ref(cout));

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

//    transform(v.begin(), v.end(), v.begin(), boost::bind(_1, boost::bind(DivideBy(), _1, 2)));
    transform(v.begin(), v.end(), v.begin(), boost::bind(DivideBy(), _1, 2));
    for_each(v.begin(), v.end(), cout << boost::lambda::_1 << "\n");

    vector<string> strings;
    strings.push_back("Boost");
    strings.push_back("C++");
    strings.push_back("Libraries");

    boost::function<int (string*)> s = &string::size;

    vector<int> sizes;
//    for_each(strings.begin(), strings.end(), sizes.push_back(
//                                                             s(&(boost::lambda::unlambda(boost::lambda::_1)))));

    for_each(sizes.begin(), sizes.end(), cout << boost::lambda::_1 << "\n");

//    boost::signal<void ()> s_;
//    s_.connect(func);
//    s_();

    boost::function<void ()> fsig;
    fsig = func;
    fsig();

    return 0;
}
