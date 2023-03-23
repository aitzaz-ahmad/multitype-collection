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

class configurations {
public:
    void insert(const property& config_property);
    bool exists(const std::string& key) const;
    
    template<class U>
    std::optional<U> get_value(const std::string& key) const;

    template<class U>
    std::optional<U> get_value(const property& config_property) const;

private:
    server_configs m_config_properties;
};
