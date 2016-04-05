#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
//    boost::filesystem::path p("/home/yjz/");
//    cout << p.string()  << endl;
//    cout << p.root_name() << endl;
//    cout << p.root_directory() << endl;
//    cout << p.root_path() << endl;
//    cout << p.relative_path() << endl;
//    cout << p.parent_path() << endl;
//    cout << p.filename() << endl;
//    cout << p.file_string() << endl;
//    cout << p.directory_string() << endl;
//    boost::filesystem::path q("/");
//    cout << q.string() << endl;

    boost::filesystem::path p("photo.jpg.png");
    cout << p.stem() << endl;
    cout << p.extension() << endl;

    cout << boost::filesystem::current_path() << endl;

    return 0;
}
