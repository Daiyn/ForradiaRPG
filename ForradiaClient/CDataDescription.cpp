#include "CDataDescription.h"

using std::string;

bool CDataDescription::ContainsProperty(string property) {

    return m_propAttributes.count(property) != 0;

}

bool CDataDescription::ContainsPropertyWithValue(string property, string value) {

    if (m_propAttributes.count(property))
        return m_propAttributes[property] == value;

    return false;

}