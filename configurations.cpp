#include "configurations.h"

void configurations::insert(const property& config_property) 
{
    auto search = m_config_properties.find(config_property.hash_key());

    if (search == m_config_properties.end()) //insert unique properties only
    {
        m_config_properties[config_property.hash_key()] = config_property;
    }
}

void configurations::insert(property&& config_property)
{
    auto search = m_config_properties.find(config_property.hash_key());

    if (search == m_config_properties.end()) //insert unique properties only
    {
        m_config_properties[config_property.hash_key()] = std::move(config_property);
    }
}

bool configurations::exists(const std::string& key) const
{
    auto search = m_config_properties.find(key);
    return search != m_config_properties.end();
}
