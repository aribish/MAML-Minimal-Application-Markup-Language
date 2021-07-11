#include "utils.h"

const int ab::Constants::ERROR_INT = -2147483647;

const std::string ab::Constants::FONT_FILE_PLACEHOLDER = "$$$%^%"; // "\u211D\u2107\u2102\u0166\u2127\u039C";
const std::string ab::Constants::ICON_FILE_PLACEHOLDER = "~@~+))*"; // "\u2115\u03E4\u0442";

const int ab::Constants::TAG = 0;
const int ab::Constants::INNER_TEXT = 1;

const int ab::Constants::RECTANGLE = 0;
const int ab::Constants::TRIANGLE = 1;
const int ab::Constants::CIRCLE = 2;

const int ab::Constants::PLAIN = 0;
const int ab::Constants::BOLD = 1;
const int ab::Constants::ITALIC = 2;
const int ab::Constants::UNDERLINED = 4;

bool ab::fileExists(std::string path)
{
  bool good;
  std::ifstream in;

  in.open(path);
  good = in.good();
  return good;
}

int ab::pow(int num, int base)
{
  int powedNum = num;

  if (base == 0)
  {
    return 1;
  }

  for(int i = 1; i < base; i++)
  {
    powedNum *= num;
  }

  return powedNum;
}

int ab::stringToInt(std::string str)
{
  int parsed = 0;
  int temp;

  for(int i = str.length() - 1; i >= 0; i--)
  {
    if (str[i] >= 48 && str[i] <= 57)
    {
      temp = (str[i] - 48) * (pow(10, str.length() - i - 1));
      parsed += temp;
    }
    else if (i == 0 && str[i] == '-')
    {
      parsed -= parsed * 2;
    }
    else
    {
      return Constants::ERROR_INT;
    }
  }

  return parsed;
}

sf::Color ab::hexToRGBA(std::string hexString)
{
  sf::Color col = sf::Color(0, 0, 0, 255);
  int curChannel;

  if (hexString[0] == '#' && (hexString.length() == 9 || hexString.length() == 7))
  {
    if (hexString.length() == 7)
      col.a = 255;

    hexString.erase(0, 1);

    for(int i = 0; i < hexString.length(); i += 2)
    {
      if (hexString[i] >= 65 && hexString[i] <= 90)
        hexString[i] += 32;
      if (hexString[i + 1] >= 65 && hexString[i + 1] <= 90)
        hexString[i + 1] += 32;

      curChannel = 0;

      if (hexString[i] >= 48 && hexString[i] <= 57)
      {
        curChannel += (hexString[i] - 48) * 16;
      }
      else if (hexString[i] >= 97 && hexString[i] <= 102)
      {
        curChannel += (hexString[i] - 87) * 16;
      }
      else
      {
        ab::invalidAttributeParameterErr(hexString);
        col.r = 0;
        col.g = 0;
        col.b = 0;
        col.a = 255;
        break;
      }

      if (hexString[i + 1] >= 48 && hexString[i + 1] <= 57)
      {
        curChannel += hexString[i + 1] - 48;
      }
      else if (hexString[i + 1] >= 97 && hexString[i + 1] <= 102)
      {
        curChannel += hexString[i + 1] - 87;
      }
      else
      {
        ab::invalidAttributeParameterErr(hexString);
        col.r = 0;
        col.g = 0;
        col.b = 0;
        col.a = 255;
        break;
      }

      switch(i / 2)
      {
        case 0:
          col.r = curChannel;
          break;
        case 1:
          col.g = curChannel;
          break;
        case 2:
          col.b = curChannel;
          break;
        case 3:
          col.a = curChannel;
          break;
      }
    }
  }
  else
  {
    ab::invalidAttributeParameterErr(hexString);
  }

  return col;
}
