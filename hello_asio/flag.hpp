#ifndef FLAG_HPP_INCLUDED
#define FLAG_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class Option
{
public:
    Option(const std::string& option = "", const std::string& defValue = "",
           const std::string& desc = ""):
        option(option), defaultValue(defValue), description(desc)
    {}

    std::string option;
    std::string defaultValue;
    std::string description;
};

class Flag
{
public:
    void addOption(const std::string& option, const std::string& defValue,
                   const std::string& desc);
    void addOption(const Option& option);

    bool parse(int argc, const char* argv[]);

    bool getString(const std::string& option, std::string& value);
    bool getInt(const std::string& option, int& value);

    std::string help();

private:
    std::map<std::string, Option> options;
    std::vector<std::string> args;
};

#endif
