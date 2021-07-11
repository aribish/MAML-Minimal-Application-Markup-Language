#include "lexObj.h"

ab::lexObj::lexObj(int _typeID, std::string _value)
{
  typeID = _typeID;
  value = _value;
}

void ab::lexObj::setValue(std::string _value)
{
  value = _value;
}

int ab::lexObj::getTypeID()
{
  return typeID;
}

std::string ab::lexObj::getValue()
{
  return value;
}
