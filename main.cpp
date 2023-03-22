// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include "configurations.h"

inline std::string bool_to_alpha(bool val)
{
    return val ? "true" : "false";
}

class AnsiString : public std::string {

public:
    void print() {
        std::cout << this << std::endl;
    }
};

int main()
{
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "  Multi-type Key-Value Store Stub  " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    auto app_config         = configurations{};
    const auto& app_version = static_cast<std::string>(AnsiString{ "1.0.0" });
    app_config.insert(property{ "general",  "version",   app_version });
    app_config.insert(property{ "general",  "internal",  true });
    app_config.insert(property{ "database", "ip",        std::string { "192.168.15.120" } });
    app_config.insert(property{ "database", "port",      3306 });
    app_config.insert(property{ "database", "name",      std::string { "atmdemo" } });
    app_config.insert(property{ "database", "user",      std::string { "root" } });
    app_config.insert(property{ "database", "password",  std::string { "Transact123!!" } });
    app_config.insert(property{ "database", "instances", 10 });

    auto section = std::string{ "general" };
    auto key     = std::string{ "version" };
    std::cout << "section: " << section << ", key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(section, key) << std::endl;

    auto str_config = app_config.get_value<std::string>(section, key);
    auto version    = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << version << std::endl;

    key = std::string{ "internal" };
    std::cout << "section: " << section << ", key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(section, key) << std::endl;

    auto bool_config = app_config.get_value<bool>(section, key);
    auto isInternal  = bool_config.has_value() ? bool_to_alpha(bool_config.value()) : std::string{ "std::nullopt_t" };
    std::cout << "get_value<bool>: " << isInternal << std::endl;

    str_config = app_config.get_value<std::string>(section, key);
    isInternal = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << isInternal << std::endl;

    key = std::string{ "app_name" };
    std::cout << "section: " << section << ", key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(section, key) << std::endl;

    str_config      = app_config.get_value<std::string>(section, key);
    auto app_name   = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << app_name << std::endl;

    section = std::string{ "database" };
    key = std::string{ "ip" };
    std::cout << "section: " << section << ", key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(section, key) << std::endl;

    str_config = app_config.get_value<std::string>(section, key);
    auto db_ip = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << db_ip << std::endl;

    key = std::string{ "port" };
    std::cout << "section: " << section << ", key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(section, key) << std::endl;

    auto int_config = app_config.get_value<int>(section, key);
    auto db_port= int_config.has_value() ? std::to_string(int_config.value()) : std::string{ "std::nullopt_t" };
    std::cout << "get_value<int>: " << db_port << std::endl;

    std::cout << "Press any key to continue..." << std::endl;
    auto key_stroke = char{};
    std::cin >> key_stroke;

    return 0;
}
