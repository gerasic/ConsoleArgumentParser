class BaseType {
public:
    BaseType(char short_name, std::string&& long_name, std::string&& desc)
            : short_name_(short_name)
            , long_name_(std::move(long_name))
            , description_(std::move(desc))
            , is_have_value_(false)
            , is_have_store_value_(false)
            , is_have_store_values_(false)
            , is_multi_(false)
            , is_positional_(false)
            , is_have_default_value_(false)
            , min_amount_of_args_(0)
            , amount_of_args_(0)
    {}


    virtual int GetIntValue() {
        throw std::runtime_error("Not int.");
    }
    virtual bool GetFlag() {
        throw std::runtime_error("Not bool.");
    }
    virtual std::string& GetStringValue() {
        throw std::runtime_error("Not string to call GetStringValue.");
    }

    virtual int GetIntValue(size_t at) {
        throw std::runtime_error("Not int.");
    }
    virtual bool GetFlag(size_t at) {
        throw std::runtime_error("Not bool.");
    }
    virtual std::string& GetStringValue(size_t at) {
        throw std::runtime_error("Not string to call GetStringValue.");
    }


    virtual BaseType& Default(int value) {
        throw std::runtime_error("Not int to call Default.");
    }
    virtual BaseType& Default(std::string&& value) {
        throw std::runtime_error("Not string to call Default.");
    }
    virtual BaseType& Default(bool value) {
        throw std::runtime_error("Not bool to call Default.");
    }


    virtual BaseType& StoreValue(int& value) {
        throw std::runtime_error("Not int to call StoreValue.");
    }
    virtual BaseType& StoreValue(std::string& value) {
        throw std::runtime_error("Not string to call StoreValue.");
    }
    virtual BaseType& StoreValue(bool& value) {
        throw std::runtime_error("Not bool to call StoreValue.");
    }

    virtual BaseType& StoreValues(std::vector<int>& values) {
        throw std::runtime_error("Not int to call StoreValues.");
    }
    virtual BaseType& StoreValues(std::vector<std::string>& values) {
        throw std::runtime_error("Not string to call StoreValues.");
    }
    virtual BaseType& StoreValues(std::vector<bool>& values) {
        throw std::runtime_error("Not bool to call StoreValues.");
    }


    virtual BaseType& MultiValue() {
        throw std::runtime_error("Can't call MultiValue from BaseType.");
    }
    virtual BaseType& MultiValue(size_t count_of_args) {
        throw std::runtime_error("Can't call MultiValue from BaseType.");
    }


    virtual BaseType& Positional() {
        throw std::runtime_error("Can't call Positional from BaseType.");
    }


    virtual void SetValue(int value) {
        throw std::runtime_error("Can't SetValue in a BaseType object.");
    }
    virtual void SetValue(const std::string_view& value) {
        throw std::runtime_error("Can't SetValue in a BaseType object.");
    }
    virtual void SetValue() {
        throw std::runtime_error("Can't SetValue in a BaseType object.");
    }


    bool IsHaveValue() const {
        if (is_have_store_values_ && min_amount_of_args_ > amount_of_args_) {
            return false;
        }

        return is_have_value_;
    }
    bool IsPositional() const {
        return is_positional_;
    }
    bool IsMulti() const {
        return is_multi_;
    }
    bool IsHaveDefault() const {
        return is_have_value_;
    }


    virtual bool IsString() const {
        return false;
    }
    virtual bool IsInt() const {
        return false;
    }
    virtual bool IsFlag() const {
        return false;
    }
    virtual bool IsHelp() const {
        return false;
    }


    char GetShortName() const {
        return short_name_;
    }
    const std::string& GetLongName() const {
        return long_name_;
    }
    const std::string& GetDesc() const {
        return description_;
    }
protected:
    char short_name_;
    std::string long_name_;
    std::string description_;

    bool is_have_value_;
    bool is_have_store_value_;
    bool is_have_store_values_;
    bool is_multi_;
    bool is_positional_;
    bool is_have_default_value_;

    size_t min_amount_of_args_;
    size_t amount_of_args_;
};
