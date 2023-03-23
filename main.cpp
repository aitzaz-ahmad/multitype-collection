// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include "configurations.h"

inline std::string bool_to_alpha(bool val)
{
    return val ? "true" : "false";
}

int main()
{
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "  Multi-type Key-Value Store Stub  " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    auto app_config = configurations{};
    app_config.insert(property{ "app_version",        { "1.0.0" } });
	app_config.insert(property{ "dev_build",          true });
    app_config.insert(property{ "database_ip",        std::string { "192.168.15.120" } });
    app_config.insert(property{ "database_port",      3306 });
    app_config.insert(property{ "database_name",      std::string { "atmdemo" } });
    app_config.insert(property{ "database_user",      std::string { "root" } });
    app_config.insert(property{ "database_password",  std::string { "Transact123!!" } });
    app_config.insert(property{ "database_instances", 10 });

    auto key     = std::string{ "app_version" };
    std::cout << "key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(key) << std::endl;

    auto str_config = app_config.get_value<std::string>(key);
    auto version    = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << version << std::endl;

    key = std::string{ "dev_build" };
    std::cout << "key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(key) << std::endl;

    auto bool_config    = app_config.get_value<bool>(key);
    auto is_dev_build   = bool_config.has_value() ? bool_to_alpha(bool_config.value()) : std::string{ "std::nullopt_t" };
    std::cout << "get_value<bool>: " << is_dev_build << std::endl;

    str_config      = app_config.get_value<std::string>(key);
    is_dev_build    = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << is_dev_build << std::endl;

    key = std::string{ "app_name" };
    std::cout << "key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(key) << std::endl;

    str_config      = app_config.get_value<std::string>(key);
    auto app_name   = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << app_name << std::endl;

    key = std::string{ "database_ip" };
    std::cout << "key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(key) << std::endl;

    str_config = app_config.get_value<std::string>(key);
    auto db_ip = str_config.value_or(std::string{ "std::nullopt_t" });
    std::cout << "get_value<string>: " << db_ip << std::endl;

    key = std::string{ "database_port" };
    std::cout << "key: " << key << std::endl;
    std::cout << "exists: " << std::boolalpha << app_config.exists(key) << std::endl;

    auto int_config = app_config.get_value<int>(key);
    auto db_port    = int_config.has_value() ? std::to_string(int_config.value()) : std::string{ "std::nullopt_t" };
    std::cout << "get_value<int>: " << db_port << std::endl;

    std::cout << "Press any key to continue..." << std::endl;
    auto key_stroke = char{};
    std::cin >> key_stroke;

    return 0;
}
