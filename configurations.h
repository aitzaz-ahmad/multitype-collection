#pragma once

#include <any>
#include <string>
#include <optional>
#include <type_traits>
#include <unordered_map>


class property 
{
public:

    property()                              = default;
    ~property()                             = default;
    property(const property&)               = default;
    property& operator=(const property&)    = default;
    property(property&&)                    = default;
    property& operator=(property&&)         = default;

    property(const std::string& key,
             const std::any& val):  m_key(key),
                                    m_value(val) {
    }
    
    inline std::string hash_key() const {

        return m_key;
    }

    template<class T>
    std::optional<T> get_as() const {

        if (!m_value.has_value())
            return std::optional<T>{};

        if(m_value.type() != typeid(T))
            return std::optional<T>{};
        
        return std::optional{ std::any_cast<T>(m_value) };
    }

private:

    std::string m_key;
    std::any    m_value;
};

using server_configs = std::unordered_map<std::string, property>;

class configurations 
{
public:

    void insert(property&& config_property);
    void insert(const property& config_property);
    
    bool exists(const std::string& key) const;
    
    template<class U>
    std::optional<U> get_value(const std::string& key) const {

        if (!exists(key))
            return std::optional<U>{};

        const auto& config = m_config_properties.at(key);
        return std::optional{ config.get_as<U>() };
    }

    template<class U>
    std::optional<U> get_value(const property& config_property) const {

        const auto key = config_property.hash_key();
        if (!exists(key))
            return std::optional<U>{};

        const auto& config = m_config_properties.at(key);
        return std::optional{ config.get_as<U>() };
    }

    template<class U>
    U get_value_or(const std::string& key, U default_value) const {

        if (!exists(key))
            return default_value;

        const auto& config = m_config_properties.at(key).get_as<U>();
        return config.get_value_or(default_value);
    }

    template<class U>
    U get_value_or(const property& config_property, U default_value) const {

        const auto key = config_property.hash_key();
        if (!exists(key))
            return default_value;

        const auto& config = m_config_properties.at(key).get_as<U>();
        return config.get_value_or(default_value);
    }

private:
    server_configs m_config_properties;
};
