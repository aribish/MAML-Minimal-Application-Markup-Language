/*
// This file contains functions for printing out predictable errors in a pleasant, formatted manor.
*/

#ifndef __ERR__FORMATTER__INCLUDE__
#define __ERR__FORMATTER__INCLUDE__

#include <iostream>
#include <string>

namespace ab
{
  /*
  You know what this does...
  */
  void fileNotFoundErr(std::string snippet);
  /*
  fileNotSuppliedErr is a command line error that occurs when a file was not entered when running MAML
  */
  void fileNotSuppliedErr(std::string snippet);
  /*
  tooManyFilesErr is a command line error that occurs when more than one file was entered when running MAML
  */
  void tooManyFilesErr(std::string snippet);
  /*
  internalErr occurs when an error inside the MAML parser occurs. This error is not at fault to the user, but to ME!!!
  */
  void internalErr(int lineNum);
  /*
  noAttributeParameterSuppliedErr occurs when an attribute is supplied, but no parameter is supplied
  */
  void noAttributeParameterSuppliedErr(std::string snippet);
  /*
  invalidAttributeParameterErr occurs when the attribute parameter given does not match the required format for the givern attribute
  */
  void invalidAttributeParameterErr(std::string snippet);
  /*
  unrecognizedObjectErr occurs when an unrecognized tag/attribute/ect. is found
  */
  void unrecognizedObjectErr(std::string snippet);
  /*
  childrenNotAllowedErr occurs when a graphics tag is used within another graphical tag
  */
  void childrenNotAllowedErr(std::string snippet);
  /*
  missingClsingTagErr occurs when there is an opening tag without a closing tag
  */
  void missingClosingTagErr(std::string snippet);
  /*
  tooManyDefaultScenesErr occurs when, well, the user sets more than one scene as the default scene
  */
  void tooManyDefaultScenesErr();
}

#endif
