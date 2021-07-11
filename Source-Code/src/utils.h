/*
// This file contains a collection of utility functions
*/

#ifndef __UTILS__INCLUDE__
#define __UTILS__INCLUDE__

#include <string>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
#include "errFormatter.h"

namespace ab
{
  namespace Constants
  {
      extern const int ERROR_INT;

      extern const std::string FONT_FILE_PLACEHOLDER;
      extern const std::string ICON_FILE_PLACEHOLDER;

      extern const int TAG;
      extern const int INNER_TEXT;

      extern const int RECTANGLE;
      extern const int TRIANGLE;
      extern const int CIRCLE;

      extern const int PLAIN;
      extern const int BOLD;
      extern const int ITALIC;
      extern const int UNDERLINED;
  }

  /*
  fileExists simply checks if a file exists
  */
  bool fileExists(std::string path);
  /*
  pow raises a num to the power of base
  */
  int pow(int num, int base);
  /*
  stringToInt converts a string to a signed integer using magic!!!
  */
  int stringToInt(std::string str);
  /*
  hexToRBGA converts a hexadecimal number (formatted as #RRGGBBAA) to SFML color object
  */
  sf::Color hexToRGBA(std::string hexString);
}

#endif
