#include "DataDescription.h"

using std::string;

bool DataDescription::ContainsProperty(string property)
{
    return m_propAttributes.count(property) != 0;
}

bool DataDescription::ContainsPropertyWithValue(string property, string value)
{
    if (m_propAttributes.count(property))
        return m_propAttributes[property] == value;

    return false;
}