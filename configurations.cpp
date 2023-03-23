#include "configurations.h"

void configurations::insert(const property& config_property) 
{
    auto search = m_config_properties.find(config_property.hash_key());

    if (search == m_config_properties.end()) //insert unique properties only
    {
        m_config_properties[config_property.hash_key()] = config_property;
    }
}

bool configurations::exists(const std::string& key) const
{
    auto search = m_config_properties.find(key);
    return search != m_config_properties.end();
}

template<typename U>
std::optional<U> configurations::get_value(const std::string& key) const
{
    if (!exists(key))
    {
        return std::optional<U>{};
    }

    const auto& config = m_config_properties.at(key);
    return std::optional{ config.get_as<U>() };
}

template<class U>
std::optional<U> configurations::get_value(const property& config_property) const
{
    const auto key = config_property.hash_key();
    if (!exists(key))
    {
        return std::optional<U>{};
    }

    const auto& config = m_config_properties.at(key);
    return std::optional{ config.get_as<U>() };
}

//TODO: Move the following region into a separate cpp file (and include configurations.cpp file in it)
#pragma region - template specializations for configuration::get_value member function
template std::optional<int> configurations::get_value(const std::string& key) const;

template std::optional<bool> configurations::get_value(const std::string& key) const;

template std::optional<std::string> configurations::get_value(const std::string& key) const;

#pragma endregion - template specializations for configuration::get_value member function

#pragma region - template specializations for configuration::get_value member function
template std::optional<int> configurations::get_value(const property& config_property) const;

template std::optional<bool> configurations::get_value(const property& config_property) const;

template std::optional<std::string> configurations::get_value(const property& config_property) const;

#pragma endregion - template specializations for configuration::get_value member function
