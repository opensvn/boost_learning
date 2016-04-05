#include <iostream>
#include <cstring>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

boost::shared_array<char> get(const char *s)
{
    int size = std::strlen(s);
    boost::shared_array<char> p(new char[size + 1]);
    std::strncpy(p.get(), s, size + 1);
    return p;
}

void print(boost::weak_ptr<char> &p)
{
    boost::shared_ptr<char> s = p.lock();
    if (s)
        std::cout << s.get() << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << argv[0] << " <data>" << std::endl;
        return 1;
    }

    boost::shared_array<char> text = get(argv[1]);
    print(text);

    return 0;
}
