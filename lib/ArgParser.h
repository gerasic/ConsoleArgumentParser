#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>

#include "Types/BaseType.hpp"
#include "Types/StringType.hpp"
#include "Types/IntType.hpp"
#include "Types/FlagType.hpp"

struct MyHash {       // for arguments in HashTables
    using is_transparent = void;

    size_t operator()(std::string_view value) const {
        return std::hash<std::string_view>{}(value);
    }

    size_t operator()(const std::string& value) const {
        return std::hash<std::string>{}(value);
    }
};

namespace ArgumentParser {

struct ArgumentInfo {
    bool is_long_argument = false;
    bool is_short_argument = false;
    bool is_positional_argument = false;
    int equal_sign_position = (int)std::string::npos;
};

class ArgParser {
public:
    ArgParser(const std::string& name);
    ArgParser(std::string&& name);

    
    StringType& AddStringArgument(std::string &&long_name);
    StringType& AddStringArgument(char short_name, std::string &&long_name);
    StringType& AddStringArgument(std::string &&long_name, std::string &&description);
    StringType& AddStringArgument(char, std::string&&, std::string&&);

    std::string GetStringValue(const std::string& key);
    std::string GetStringValue(const std::string& key, size_t at);


    IntType& AddIntArgument(std::string &&long_name);
    IntType& AddIntArgument(char short_name, std::string &&long_name);
    IntType& AddIntArgument(std::string &&long_name, std::string &&description);
    IntType& AddIntArgument(char, std::string&&, std::string&&);

    int GetIntValue(const std::string& key);
    int GetIntValue(const std::string& key, size_t at);


    FlagType& AddFlag(std::string &&long_name);
    FlagType& AddFlag(char short_name, std::string &&long_name);
    FlagType& AddFlag(std::string &&long_name, std::string &&description);
    FlagType& AddFlag(char, std::string&&, std::string&&);

    bool GetFlag(const std::string& key);
    bool GetFlag(const std::string& key, size_t at);


    FlagType& AddHelp(std::string &&long_name);
    FlagType& AddHelp(char short_name, std::string &&long_name);
    FlagType& AddHelp(std::string &&long_name, std::string &&description);
    FlagType& AddHelp(char, std::string&&, std::string&&);

    std::string HelpDescription();


    bool Parse(int argc, char** argv);
    bool Parse(const std::vector<std::string>& arguments);

private:
    std::string name_;
    std::unordered_map<std::string, std::shared_ptr<BaseType>, MyHash, std::equal_to<>> long_name_keys_;
    std::unordered_map<char, std::shared_ptr<BaseType>> short_name_keys_;

    static ArgumentInfo GetInfoAboutArgument(const std::string_view& sv);

    bool IsPositional(const std::string_view& arg_key);
    bool IsMulti(const std::string_view& argument);

    bool IsFlag(const std::string_view& argument);
    bool IsHelp(const std::string_view& argument);

    static std::pair<std::string_view, std::string_view> ParseKeyValue(const std::string_view& current_argument, int sign_position);

    static std::string GetType(const std::shared_ptr<BaseType>& ptr);
}; // ArgParser

} // namespace ArgumentParser
