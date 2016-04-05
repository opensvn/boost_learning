#include <iostream>
#include <locale>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>
#include <clocale>
#include <vector>
#include <string>

using namespace std;

int main()
{
//    std::cout << std::strcoll("ä", "z") << std::endl;
    locale::global(locale("German"));
//    std::cout << std::strcoll("ä", "z") << std::endl;
//    locale loc;
//    cout << loc.name() << endl;
//
//    setlocale(LC_ALL, "German");
    string s = "Boris Schäling";
//    cout << boost::algorithm::to_upper_copy(s) << endl;
//    cout << boost::algorithm::to_upper_copy(s, locale("German")) << endl;

//    std::cout << boost::algorithm::erase_first_copy(s, "i") << std::endl;
//    std::cout << boost::algorithm::erase_nth_copy(s, "i", 0) << std::endl;
//    std::cout << boost::algorithm::erase_last_copy(s, "i") << std::endl;
//    std::cout << boost::algorithm::erase_all_copy(s, "i") << std::endl;
//    std::cout << boost::algorithm::erase_head_copy(s, 5) << std::endl;
//    std::cout << boost::algorithm::erase_tail_copy(s, 8) << std::endl;

//    boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "Boris");
//    std::cout << r << std::endl;
//    r = boost::algorithm::find_first(s, "xyz");
//    std::cout << r << std::endl;

//    std::vector<std::string> v;
//    v.push_back("Boris");
//    v.push_back("Schäling");
//    std::cout << boost::algorithm::join(v, " ") << std::endl;

//    std::cout << boost::algorithm::replace_first_copy(s, "B", "D") << std::endl;
//    std::cout << boost::algorithm::replace_nth_copy(s, "B", 0, "D") << std::endl;
//    std::cout << boost::algorithm::replace_last_copy(s, "B", "D") << std::endl;
//    std::cout << boost::algorithm::replace_all_copy(s, "B", "D") << std::endl;
//    std::cout << boost::algorithm::replace_head_copy(s, 5, "Doris") << std::endl;
//    std::cout << boost::algorithm::replace_tail_copy(s, 8, "Becker") << std::endl;

//    s = "\t Boris Schäling \t";
//    std::cout << "." << boost::algorithm::trim_left_copy(s) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_right_copy(s) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_copy(s) << "." << std::endl;

//    s = "--Boris Schäling--";
//    std::cout << "." << boost::algorithm::trim_left_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_right_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl;
//
//    s = "123456789Boris Schäling123456789";
//    std::cout << "." << boost::algorithm::trim_left_copy_if(s, boost::algorithm::is_digit()) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_right_copy_if(s, boost::algorithm::is_digit()) << "." << std::endl;
//    std::cout << "." <<boost::algorithm::trim_copy_if(s, boost::algorithm::is_digit()) << "." << std::endl;

    s = "Boris Schäling";
//    std::cout << boost::algorithm::starts_with(s, "Boris") << std::endl;
//    std::cout << boost::algorithm::ends_with(s, "Schäling") << std::endl;
//    std::cout << boost::algorithm::contains(s, "is") << std::endl;
//    std::cout << boost::algorithm::lexicographical_compare(s, "Boris") << std::endl;

//    std::vector<std::string> v;
//    boost::algorithm::split(v, s, boost::algorithm::is_space());
//    std::cout << v.size() << std::endl;

//    boost::regex expr("\\w+\\s\\w+");
//    cout << boost::regex_match(s, expr) << endl;
//
//    expr = "(\\w+)\\s(\\w+)";
//    boost::smatch what;
//    if (boost::regex_search(s, what, expr)) {
//        cout << what[0] << endl;
//        cout << what[1] << " " << what[2] << endl;
//    }

//    s = " Boris Schäling ";
//    expr = "\\s";
//    string fmt("_");
//    cout << boost::regex_replace(s, expr, fmt) << endl;

//    s = "Boris Schäling";
//    expr = "(\\w+)\\s(\\w+)";
//    fmt = "\\2 \\1";
//    cout << boost::regex_replace(s, expr, fmt) << endl;
//    cout << boost::regex_replace(s, expr, fmt, boost::regex_constants::format_literal)
//        << endl;

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
//    s = "Boost C++ Libraries";
//    tokenizer tok(s);
//    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
//        cout << *it << endl;

//    boost::char_separator<char> sep(" ", "+", boost::keep_empty_tokens);
//    tokenizer token(s, sep);
//    for (tokenizer::iterator it = token.begin(); it != token.end(); ++it)
//        cout << *it << endl;

//    s = "Boost, \"C++ Libraries\"";
//    typedef boost::tokenizer<boost::escaped_list_separator<char> > token_esc;
//    token_esc t(s);
//    for (token_esc::iterator it = t.begin(); it != t.end(); ++it)
//        cout << *it << endl;

//    typedef boost::tokenizer<boost::offset_separator> token_off;
//    s = "Boost C++ Libraries";
//    int offsets[] = {5, 5, 9};
//    boost::offset_separator off_sep(offsets, offsets + 3);
//    token_off t2(s, off_sep);
//    for (token_off::iterator it = t2.begin(); it != t2.end(); ++it)
//        cout << *it << endl;

    cout << boost::format("%1%/%2%/%3%") % 16 % 9 % 2008 << endl;
    return 0;
}
