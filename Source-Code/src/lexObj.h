/*
This file contains a data structure that represents an object created from a MAML tag
*/

#ifndef __LEX__OBJ__INCLUDE__
#define __LEX__OBJ__INCLUDE__

#include <string>
#include "utils.h"

namespace ab
{
  /*
  lexObj (Lexically Analyzed Object) is a simple class that contains information on an object extracted from a MAML document
  */
  struct lexObj
  {
    private:
      int typeID;
      std::string value;

    public:
      lexObj(int _typeID, std::string _value);
      /*
      Sets the value represented by the lexObj
      */
      void setValue(std::string _value);
      /*
      Returns the type of the lexObj (can be a TAG or INNER_TEXT)
      */
      int getTypeID();
      /*
      Gets the value represented by the lexObj
      */
      std::string getValue();

  };
}

#endif
