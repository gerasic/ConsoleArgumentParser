class FlagType : public BaseType {
public:
    FlagType(char short_name, std::string&& long_name, std::string&& desc)
            : BaseType(short_name, std::move(long_name), std::move(desc))
            , value_()
            , store_value_(nullptr)
            , store_values_(nullptr)
            , is_help_(false) // for only help argument
    {}

    bool GetFlag() override {
        return value_;
    }
    bool GetFlag(size_t at) override {
        return values_[at];
    }

    void SetValue() override {
        is_have_value_ = true;

        if (is_have_store_value_) {
            *store_value_ = !value_;
        } else if (is_have_store_values_) {
            store_values_->push_back(!value_);
            ++amount_of_args_;
        }

        if (is_multi_) {
            values_.push_back(!value_);
        } else {
            value_ = !value_;
        }
    }
    void SetHelp() {
        is_help_ = true;
        is_have_value_ = true;
    }

    FlagType& Default(bool value) override {
        value_ = value;
        is_have_value_ = true;
        is_have_default_value_ = true;

        return *this;
    }

    FlagType& StoreValue(bool& value) override {
        is_have_store_value_ = true;
        store_value_ = &value;

        return *this;
    }
    FlagType& StoreValues(std::vector<bool>& values) override {
        is_have_store_values_ = true;
        store_values_ = &values;

        return *this;
    }

    FlagType& MultiValue() override {
        is_multi_ = true;
        return *this;
    }
    FlagType& MultiValue(size_t count_of_args) override {
        is_multi_ = true;
        min_amount_of_args_ = count_of_args;

        return *this;
    }

    FlagType& Positional() override {
        is_positional_ = true;
        return *this;
    }

    bool IsFlag() const override {
        return true;
    }
    bool IsHelp() const override {
        return is_help_;
    }

private:
    bool value_;
    std::vector<bool> values_;

    bool* store_value_;
    std::vector<bool>* store_values_;

    bool is_help_; // for only help argument
};
