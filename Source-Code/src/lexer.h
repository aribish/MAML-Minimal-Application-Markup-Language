/*
// This file converts a MAML document to a list of lexObj's and attributes
*/

#ifndef __LEXER__INCLUDE__
#define __LEXER__INCLUDE__

#include <vector>
#include "lexObj.h"

namespace ab
{
  /*
  lexDocument takes a formmated MAML document and turns it into a list of lexically analyzed objects (lexObj's)
  */
  std::vector<lexObj> lexDocument(std::string doc);
  /*
  lexAttributes takes a lexObject and extracts it's attributes and attribute values
  */
  std::vector<std::string> lexAttributes(lexObj &tag);
}

#endif
