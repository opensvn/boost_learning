#include "flag.hpp"

#include <sstream>

void Flag::addOption(const std::string& option, const std::string& defValue,
                     const std::string& desc)
{
    addOption(Option(option, defValue, desc));
}

void Flag::addOption(const Option& option)
{
    options[option.option] = option;
}

bool beginWithDash(const std::string& s)
{
    if (s.empty())
    {
        return false;
    }

    if (s[0] == '-')
    {
        return true;
    }

    return false;
}

bool Flag::parse(int argc, const char* argv[])
{
    for (int i = 1; i < argc - 1; ++i)
    {
        std::string arg(argv[i]);

        if (!beginWithDash(arg))
        {
            args.push_back(arg);
        }
        else
        {
            std::string option = arg.substr(1);
            std::map<std::string, Option>::iterator it = options.find(option);
            if (it == options.end())
            {
                return false;
            }

            std::string value = argv[i+1];
            if (beginWithDash(value))
            {
                if (it->second.defaultValue.empty())
                {
                    return false;
                }
                else
                {
                    continue;
                }
            }

            it->second.defaultValue = value;
            ++i;
        }
    }

    std::string lastArg = argv[argc - 1];
    if (beginWithDash(lastArg))
    {
        return false;
    }

    args.push_back(lastArg);

    return true;
}

bool Flag::getString(const std::string& option, std::string& value)
{
    std::map<std::string, Option>::iterator it = options.find(option);
    if (it == options.end())
    {
        return false;
    }

    value = it->second.defaultValue;
    return true;
}

bool Flag::getInt(const std::string& option, int& value)
{
    std::map<std::string, Option>::iterator it = options.find(option);
    if (it == options.end())
    {
        return false;
    }

    std::stringstream ss(it->second.defaultValue);
    ss >> value;
    return true;
}

std::string Flag::help()
{
    std::stringstream stream;
    stream << "Usage:\n";
    for (std::map<std::string, Option>::iterator it = options.begin();
         it != options.end(); ++it)
    {
        stream << "-" << it->first << "\t" << it->second.description;
        if (!it->second.defaultValue.empty())
        {
            stream << " (default \"" << it->second.defaultValue
                      << "\")";
        }
        stream << "\n";
    }
}
