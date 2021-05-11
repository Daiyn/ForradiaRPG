/*+===================================================================
  File:      CDATADESCRIPTION.H

  Summary:   Describes class representening an element in the content 
             database describing properties for different kind of 
             content such as tiles, object etc.

  Classes:   CDataDescription

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_DATADESCRIPTION_H
#define FORRADIACLIENT_DATADESCRIPTION_H

#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDataDescription

  Summary:  Short summary of purpose and content of CMyClass.
            Short summary of purpose and content of CMyClass.

  Methods:  MyMethodOne
              Short description of MyMethodOne.
            MyMethodTwo
              Short description of MyMethodTwo.
            CMyClass
              Constructor.
            ~CMyClass
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class CDataDescription
{
public:

    unordered_map<string, string> m_propAttributes;

    bool ContainsProperty(string property);
    bool ContainsPropertyWithValue(string property, string value);

protected:

private:

};


#endif //FORRADIACLIENT_DATADESCRIPTION_H
