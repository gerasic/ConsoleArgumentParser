#include "ArgParser.h"
#include "iostream"

using namespace ArgumentParser;

ArgParser::ArgParser(const std::string& name) : name_(name) {}
ArgParser::ArgParser(std::string&& name) : name_(std::move(name)) {}


//====================================================STRING============================================================
StringType& ArgParser::AddStringArgument(std::string&& long_name) {
    return AddStringArgument(' ', std::move(long_name), "");
}
StringType& ArgParser::AddStringArgument(char short_name, std::string&& long_name) {
    return AddStringArgument(short_name, std::move(long_name), "");
}
StringType& ArgParser::AddStringArgument(std::string&& long_name, std::string&& description) {
    return AddStringArgument(' ', std::move(long_name), std::move(description));
}
StringType& ArgParser::AddStringArgument(char short_name, std::string&& long_name, std::string&& description) {
    std::shared_ptr<StringType> new_arg = std::make_shared<StringType>(short_name, std::move(long_name), std::move(description));

    const std::string& long_name_ = new_arg->GetLongName();

    if (!long_name_.empty()) long_name_keys_[long_name_] = new_arg;
    if (short_name != ' ') short_name_keys_[short_name] = new_arg;

    return *new_arg;
}

std::string ArgParser::GetStringValue(const std::string& key) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetStringValue();
}
std::string ArgParser::GetStringValue(const std::string& key, size_t at) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetStringValue(at);
}


//=====================================================INT==============================================================
IntType& ArgParser::AddIntArgument(std::string&& long_name) {
    return AddIntArgument(' ', std::move(long_name), "");
}
IntType& ArgParser::AddIntArgument(char short_name, std::string&& long_name) {
    return AddIntArgument(short_name, std::move(long_name), "");
}
IntType& ArgParser::AddIntArgument(std::string&& long_name, std::string&& description) {
    return AddIntArgument(' ', std::move(long_name), std::move(description));
}
IntType& ArgParser::AddIntArgument(char short_name, std::string&& long_name, std::string&& description) {
    std::shared_ptr<IntType> new_arg = std::make_shared<IntType>(short_name, std::move(long_name), std::move(description));

    const std::string& long_name_ = new_arg->GetLongName();

    if (!long_name_.empty()) long_name_keys_[long_name_] = new_arg;
    if (short_name != ' ') short_name_keys_[short_name] = new_arg;

    return *new_arg;
}

int ArgParser::GetIntValue(const std::string& key) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetIntValue();
}
int ArgParser::GetIntValue(const std::string& key, size_t at) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetIntValue(at);
}


//=====================================================FLAGS============================================================
FlagType& ArgParser::AddFlag(std::string&& long_name) {
    return AddFlag(' ', std::move(long_name), "");
}
FlagType& ArgParser::AddFlag(char short_name, std::string&& long_name) {
    return AddFlag(short_name, std::move(long_name), "");
}
FlagType& ArgParser::AddFlag(std::string&& long_name, std::string&& description) {
    return AddFlag(' ', std::move(long_name), std::move(description));
}
FlagType& ArgParser::AddFlag(char short_name, std::string&& long_name, std::string&& description) {
    std::shared_ptr<FlagType> new_arg = std::make_shared<FlagType>(short_name, std::move(long_name), std::move(description));

    const std::string& long_name_ = new_arg->GetLongName();

    if (!long_name_.empty()) long_name_keys_[long_name_] = new_arg;
    if (short_name != ' ') short_name_keys_[short_name] = new_arg;

    return *new_arg;
}

bool ArgParser::GetFlag(const std::string &key) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetFlag();
}
bool ArgParser::GetFlag(const std::string &key, size_t at) {
    if (!long_name_keys_.contains(key)) {
        throw std::invalid_argument("No such argument.");
    }

    return long_name_keys_[key]->GetFlag(at);
}


//======================================================HELP============================================================
FlagType& ArgParser::AddHelp(std::string&& long_name) {
    return AddFlag(' ', std::move(long_name), "");
}
FlagType& ArgParser::AddHelp(char short_name, std::string&& long_name) {
    return AddFlag(short_name, std::move(long_name), "");
}
FlagType& ArgParser::AddHelp(std::string&& long_name, std::string&& description) {
    return AddFlag(' ', std::move(long_name), std::move(description));
}
FlagType& ArgParser::AddHelp(char short_name, std::string&& long_name, std::string&& description) {
    std::shared_ptr<FlagType> new_arg = std::make_shared<FlagType>(short_name, std::move(long_name), std::move(description));

    new_arg->SetHelp();

    const std::string& long_name_ = new_arg->GetLongName();

    if (!long_name_.empty()) long_name_keys_[long_name_] = new_arg;
    if (short_name != ' ') short_name_keys_[short_name] = new_arg;

    return *new_arg;
}

std::string ArgParser::HelpDescription() {
    std::string desc;

    desc += name_ + "\n";
    for (auto& [key, value] : long_name_keys_) {
        if (value->IsHelp()) {
            desc += value->GetDesc();
        }
    }
    desc += "\n\n";

    for (auto& [key, value] : long_name_keys_) {
        desc += "-";
        desc.push_back(value->GetShortName());
        desc += ",\t";
        desc += "--" + value->GetLongName() + GetType(value) + ",\t";
        desc += value->GetDesc() + " ";

        if (value->IsMulti() || value->IsHaveDefault() || value->IsPositional()) {
            desc += " [ ";
            if (value->IsMulti()) { desc += "repeated "; }
            if (value->IsHaveDefault()) { desc += "defaulted "; }
            if (value->IsPositional()) { desc += "positional "; }

            desc += "]";
        }

        desc += "\n";
    }

    return desc;
}

std::string ArgParser::GetType(const std::shared_ptr<BaseType>& ptr) {
    if (ptr->IsString()) {
        return "=<string>";
    } else if (ptr->IsInt()) {
        return "=<int>";
    } else if (ptr->IsFlag()) {
        return "=<bool>";
    }

    return "undefined type";
}


//======================================================PARSE===========================================================
bool ArgParser::Parse(int argc, char** argv) {
    return Parse({argv, argv + argc});
}
bool ArgParser::Parse(const std::vector<std::string>& arguments) {
    std::string_view positional_key; // for only positional arguments

    for (int i = 1; i < arguments.size(); ++i) {
        std::string_view current_argument = arguments[i];

        ArgumentInfo arg_info = GetInfoAboutArgument(current_argument);

        if (arg_info.is_long_argument && IsHelp(current_argument)) {
            std::cout << this->HelpDescription();
            return true;
        } else if (arg_info.is_long_argument && arg_info.equal_sign_position != std::string_view::npos) {
            auto [arg_key, arg_value] = ParseKeyValue(current_argument, arg_info.equal_sign_position);

            if (long_name_keys_.contains(arg_key)) {
                long_name_keys_.find(arg_key)->second->SetValue(arg_value);
            }
        } else if (arg_info.is_long_argument && IsMulti(current_argument)) {
            while (++i < arguments.size()) {
                std::string_view next_argument = arguments[i];
                if (next_argument.starts_with("-") || next_argument.starts_with("--")) {
                    --i;
                    break;
                }

                if (long_name_keys_.contains(current_argument.substr(2))) {
                    long_name_keys_.find(current_argument.substr(2))->second->SetValue(next_argument);
                }
            }
        } else if (arg_info.is_long_argument && IsFlag(current_argument)) {
            long_name_keys_.find(current_argument.substr(2))->second->SetValue();
        } else if (arg_info.is_long_argument && arg_info.equal_sign_position == std::string_view::npos && (i + 1) != arguments.size()) {
            std::string_view next_argument = arguments[++i];
            if (next_argument.starts_with("-") || next_argument.starts_with("--")) {
                return false;
            }

            if (long_name_keys_.contains(current_argument.substr(2))) {
                long_name_keys_.find(current_argument.substr(2))->second->SetValue(next_argument);
            }
        } else if (arg_info.is_short_argument && IsHelp(current_argument)) {
            std::cout << this->HelpDescription();
            return true;
        } else if (arg_info.is_short_argument && arg_info.equal_sign_position != std::string_view::npos) {
            auto [arg_key, arg_value] = ParseKeyValue(current_argument, arg_info.equal_sign_position);

            if (short_name_keys_.contains(arg_key[0])) {
                short_name_keys_.find(arg_key[0])->second->SetValue(arg_value);
            }
        } else if (arg_info.is_short_argument && IsMulti(current_argument)) {
            while (++i < arguments.size()) {
                std::string_view next_argument = arguments[i];
                if (next_argument.starts_with("-") || next_argument.starts_with("--")) {
                    --i;
                    break;
                }

                if (short_name_keys_.contains(current_argument[1])) {
                    short_name_keys_.find(current_argument[1])->second->SetValue(next_argument);
                }
            }
        } else if (arg_info.is_short_argument && IsFlag(current_argument)) {
            for (int j = 1; j < current_argument.size(); ++j) {
                short_name_keys_.find(current_argument[j])->second->SetValue();
            }
        } else if (arg_info.is_short_argument && arg_info.equal_sign_position == std::string_view::npos && (i + 1) != arguments.size()) {
            std::string_view next_argument = arguments[++i];
            if (next_argument.starts_with("-") || next_argument.starts_with("--")) {
                return false;
            }

            if (short_name_keys_.contains(current_argument[1])) {
                short_name_keys_.find(current_argument[1])->second->SetValue(next_argument);
            }
        } else if (arg_info.is_positional_argument) {
            if (positional_key.empty()) {
                for (auto& key : long_name_keys_) {
                    if (key.second->IsPositional()) {
                        positional_key = key.first;
                        break;
                    }
                }

                if (positional_key.empty()) {
                    return false;
                }
            }

            long_name_keys_.find(positional_key)->second->SetValue(current_argument);
        }
    }

    for (auto& arg : long_name_keys_) {
        if (!arg.second->IsHaveValue()) {
            return false;
        }
    }

    return true;
}

ArgumentInfo ArgParser::GetInfoAboutArgument(const std::string_view& sv) {
    ArgumentInfo arg_info;

    if (sv.size() >= 3 && sv.starts_with("--")) {
        arg_info.is_long_argument = true;
    } else if (sv.size() >= 2 && sv.starts_with("-")) {
        arg_info.is_short_argument = true;
    } else {
        arg_info.is_positional_argument = true;
    }

    arg_info.equal_sign_position = (int)sv.find_first_of('=');

    return arg_info;
}

bool ArgParser::IsMulti(const std::string_view& argument) {
    if (argument.starts_with("--")) {
        auto key = argument.substr(2);

        if (long_name_keys_.contains(key)) {
            return long_name_keys_.find(key)->second->IsMulti();
        }
    } else if (argument.starts_with("-")) {
        auto key = argument[1];

        if (short_name_keys_.contains(key)) {
            return short_name_keys_[key]->IsMulti();
        }
    }


    return false;
}
bool ArgParser::IsPositional(const std::string_view& arg_key) {
    if (short_name_keys_.contains(arg_key[0])
        && short_name_keys_.find(arg_key[0])->second->IsPositional()) {
        return true;
    }
    if (long_name_keys_.contains(arg_key)
        && long_name_keys_.find(arg_key)->second->IsPositional()) {
        return true;
    }
    return false;
}
bool ArgParser::IsFlag(const std::string_view& argument) {
    if (argument.starts_with("--")) {
        std::string_view key = argument.substr(2);

        if (!long_name_keys_.contains(key) || !long_name_keys_.find(key)->second->IsFlag()) {
            return false;
        }
    } else if (argument.starts_with("-")) {
        for (int i = 1; i < argument.size(); ++i) {
            char key = argument[i];
            if (!short_name_keys_.contains(key) || !short_name_keys_.find(key)->second->IsFlag()) {
                return false;
            }
        }
    }

    return true;
}
bool ArgParser::IsHelp(const std::string_view& argument) {
    if (argument.starts_with("--")) {
        std::string_view key = argument.substr(2);

        if (long_name_keys_.contains(key) && long_name_keys_.find(key)->second->IsHelp()) {
            return true;
        }
    } else if (argument.starts_with("-")) {
        char key = argument[1];

        if (short_name_keys_.contains(key) && short_name_keys_.find(key)->second->IsHelp()) {
            return true;
        }
    }

    return false;
}

std::pair<std::string_view, std::string_view> ArgParser::ParseKeyValue(const std::string_view& current_argument, int sign_position) {
    std::string_view arg_key;
    std::string_view arg_value;

    if (current_argument.starts_with("--")) {
        arg_key = current_argument.substr(2, sign_position - 2);
        arg_value = current_argument.substr(sign_position + 1);
    } else if (current_argument.starts_with("-")) {
        arg_key = current_argument.substr(1, sign_position - 1);
        arg_value = current_argument.substr(sign_position + 1);
    }

    return std::make_pair(arg_key, arg_value);
}
