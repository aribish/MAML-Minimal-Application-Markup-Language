/*
// This file converts a list of lexObj's to actual graphical objects
*/

#ifndef __ACTION__PARSER__INCLUDE__
#define __ACTION__PARSER__INCLUDE__

#include <vector>
#include <unistd.h>
#include "lexer.h"
#include "graphics.h"

namespace ab
{
  /*
  separateList takes a string a separates it into multiple strings for each comma character
  */
  std::vector<std::string> separateList(std::string str);

  /*
  **Add Documentation!!!
  */
  void addGraphic(Scene &scene, unsigned int shape);
  /*
  **Add Documentation!!!
  */
  void addText(Scene &scene, unsigned int shape, int defaultFontSize, int defaultFontStyle);

  /*
  setDefaultAttrVals sets the internal attribute variables to their default values
  */
  void setDefaultAttrVals();

  /*
  setAttribute_Int sets an attribute value that takes an integer parameter
  */
  bool setAttribute_Int(std::string attr, std::string val);
  /*
  setAttribute_Color sets an attribute value that takes a color parameter
  */
  bool setAttribute_Color(std::string attr, std::string val);
  /*
  setAttribute_Bool sets an attribute value that takes a boolean parameter
  */
  bool setAttribute_Bool(std::string attr, std::string val);
  /*
  setAttribute_String sets an attribute value that takes a string parameter
  */
  bool setAttribute_String(std::string attr, std::string val);
  /*
  setAttribute_List sets an attribute value that takes a list parameter
  */
  bool setAttribute_List(std::string attr, std::string val);

  /*
  setRootPath sets the path that is used to find files in attributes
  */
  void setRootPath(std::string root);
  /*
  createGraphicsObjects creates complete graphical objects out of lexObj's, and puts them into scene objects
  */
  void createGraphicsObjects(std::vector<lexObj> lexObjects, std::vector<ab::Scene> &scenes, sf::RenderWindow &window, sf::Color &windowColor, bool &keySwitching);
  /*
  setTempAttributes is an internal function that sets the temporary attributes for the graphical objects created in the createGraphicsObjects funtion
  */
  void setTempAttributes(lexObj &lexObject);
}

#endif
