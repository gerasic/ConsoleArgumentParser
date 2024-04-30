class IntType : public BaseType {
public:
    IntType(char short_name, std::string&& long_name, std::string&& desc)
            : BaseType(short_name, std::move(long_name), std::move(desc))
            , value_()
            , store_value_(nullptr)
            , store_values_(nullptr)
    {}

    int GetIntValue() override {
        return value_;
    }
    int GetIntValue(size_t at) override {
        return values_[at];
    }

    void SetValue(const std::string_view& value) override {
        is_have_value_ = true;

        if (is_have_store_value_) {
            *store_value_ = ConvertToInt(value);
        } else if (is_have_store_values_) {
            store_values_->push_back(ConvertToInt(value));
            ++amount_of_args_;
        }

        if (is_multi_) {
            values_.push_back(ConvertToInt(value));
        } else {
            value_ = ConvertToInt(value);
        }
    }

    IntType& Default(int value) override {
        value_ = value;
        is_have_value_ = true;
        is_have_default_value_ = true;

        return *this;
    }

    IntType& StoreValue(int& value) override {
        is_have_store_value_ = true;
        store_value_ = &value;

        return *this;
    }
    IntType& StoreValues(std::vector<int>& values) override {
        is_have_store_values_ = true;
        store_values_ = &values;

        return *this;
    }

    IntType& MultiValue() override {
        is_multi_ = true;
        return *this;
    }
    IntType& MultiValue(size_t count_of_args) override {
        is_multi_ = true;
        min_amount_of_args_ = count_of_args;

        return *this;
    }

    IntType& Positional() override {
        is_positional_ = true;
        return *this;
    }

    bool IsInt() const override {
        return true;
    }
private:
    int value_;
    std::vector<int> values_;

    int* store_value_;
    std::vector<int>* store_values_;

    static int ConvertToInt(const std::string_view& sv) {
        try {
            return std::stoi(std::string(sv));
        } catch(const std::invalid_argument& e) {
            throw std::runtime_error("Invalid argument for ConvertToInt: " + std::string(e.what()));
        } catch(const std::out_of_range& e) {
            throw std::runtime_error("Out of range for ConvertToInt: " + std::string(e.what()));
        }
    }
};
