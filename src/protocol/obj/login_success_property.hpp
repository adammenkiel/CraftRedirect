#include <string>

struct login_success_property {
    std::string name;
    std::string value;
    bool is_signed;
    std::string signature;

    login_success_property(std::string name, std::string value, std::string signature)
        : name(name), value(value), is_signed(true), signature(signature) {}
    login_success_property(std::string name, std::string value) 
        : name(name), value(value), is_signed(false), signature("") {}
    login_success_property(std::string name, std::string value, bool is_signed, std::string signature)
        : name(name), value(value), is_signed(is_signed), signature(signature) {}
};