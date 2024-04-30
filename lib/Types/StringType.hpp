class StringType : public BaseType {
public:
    StringType(char short_name, std::string&& long_name, std::string&& desc)
            : BaseType(short_name, std::move(long_name), std::move(desc))
            , value_()
            , store_value_(nullptr)
            , store_values_(nullptr)
    {}

    std::string& GetStringValue() override {
        return value_;
    }
    std::string& GetStringValue(size_t index) override {
        return values_[index];
    }

    void SetValue(const std::string_view& value) override {
        is_have_value_ = true;

        if (is_have_store_value_) {
            *store_value_ = std::string(value);
        } else if (is_have_store_values_) {
            store_values_->push_back(std::string(value));
            ++amount_of_args_;
        }

        if (is_multi_) {
            values_.push_back(std::string(value));
        } else {
            value_ = value;
        }
    }

    StringType& Default(std::string&& value) override {
        value_ = std::move(value);
        is_have_value_ = true;
        is_have_default_value_ = true;

        return *this;
    }

    StringType& StoreValue(std::string& value) override {
        is_have_store_value_ = true;
        store_value_ = &value;

        return *this;
    }
    StringType& StoreValues(std::vector<std::string>& values) override {
        is_have_store_values_ = true;
        store_values_ = &values;

        return *this;
    }

    StringType& MultiValue() override {
        is_multi_ = true;
        return *this;
    }
    StringType& MultiValue(size_t count_of_args) override {
        is_multi_ = true;
        min_amount_of_args_ = count_of_args;

        return *this;
    }

    StringType& Positional() override {
        is_positional_ = true;
        return *this;
    }

    bool IsString() const override {
        return true;
    }
private:
    std::string value_;
    std::vector<std::string> values_;

    std::string* store_value_;
    std::vector<std::string>* store_values_;
};
