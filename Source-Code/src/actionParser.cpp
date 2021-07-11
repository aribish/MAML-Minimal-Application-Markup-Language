#include "actionParser.h"

std::string rootPath;
int tempX, tempY, tempW, tempH, tempR, tempFontSize, tempFontStyle;;
std::string tempInner, tempTitle, tempIcon, tempSrc, tempFont;
sf::Color tempBg, tempFg;
bool tempDefault, tempUseArrowKeys, tempResize;

std::vector<std::string> ab::separateList(std::string str)
{
  std::string buf;
  std::vector<std::string> list;

  for(int i = 0; i < str.length(); i++)
  {
    if (str[i] != ',' && str[i] != ' ')
      buf += str[i];

    if (str[i] == ',' || i == str.length() - 1)
    {
      list.push_back(buf);
      buf = "";
    }
  }

  return list;
}

void ab::addGraphic(Scene &scene, unsigned int shape)
{
  scene.addGraphic(ab::Graphic(tempX, tempY, tempW, tempH, shape, tempBg));
}
void ab::addText(Scene &scene, unsigned int shape, int defaultFontSize, int defaultFontStyle)
{
  if (tempFontSize == Constants::ERROR_INT)
    tempFontSize = defaultFontSize;
  if (tempFontStyle == Constants::ERROR_INT)
    tempFontStyle = defaultFontStyle;

  scene.addText(new ab::Text(tempX, tempY, tempW, tempH, shape, tempBg, tempFg, tempInner, tempFont, tempFontSize, tempFontStyle));
}

void ab::setRootPath(std::string root)
{
  rootPath = root;
}

void ab::setDefaultAttrVals()
{
  tempX = 0;
  tempY = 0;
  tempW = 16;
  tempH = 16;
  tempR = 8;
  tempBg = sf::Color(0, 0, 0, 0);
  tempFg = sf::Color(0, 0, 0, 255);
  tempTitle = "My MAML Presentation";
  tempDefault = false;
  tempResize = false;
  tempUseArrowKeys = false;
  tempIcon = ab::Constants::ICON_FILE_PLACEHOLDER;
  tempFont = ab::Constants::FONT_FILE_PLACEHOLDER;
  tempFontSize = ab::Constants::ERROR_INT; // just, let it happen man
  tempFontStyle = ab::Constants::ERROR_INT; // same here brother
}
bool ab::setAttribute_Int(std::string attr, std::string val) // these setAttribute_TYPE() functions look wacky but they make code expansion WAYYYYY easier at the price of just one temporary variable
{
  int temp = 0;

  if (attr == "x" || attr == "y" || attr == "width" || attr == "height" || attr == "radius" || attr == "font-size")
  {
    temp = ab::stringToInt(val);

    if (temp == ab::Constants::ERROR_INT)
    {
      ab::invalidAttributeParameterErr(val);
    }

    if (attr == "x")
      tempX = temp;
    else if (attr == "y")
      tempY = temp;
    else if (attr == "width")
      tempW = temp;
    else if (attr == "height")
      tempH = temp;
    else if (attr == "radius")
      tempR = temp;
    else if (attr == "font-size")
      tempFontSize = temp;

    return true;
  }

  return false;
}
bool ab::setAttribute_Color(std::string attr, std::string val)
{
  sf::Color temp;

  if (attr == "bg" || attr == "fg")
  {
    temp = ab::hexToRGBA(val);

    if (attr == "bg")
      tempBg = temp;
    else if (attr == "fg")
      tempFg = temp;

    return true;
  }

  return false;
}
bool ab::setAttribute_Bool(std::string attr, std::string val) // this doesn't need a temp variable or to set the attributes to false because the boolean attributes are false by default
{
  if (attr == "default" || attr == "resize" || attr == "scene-switching")
  {
    if (val == "true")
    {
      if (attr == "default")
        tempDefault = true;
      else if (attr == "resize")
        tempResize = true;
      else if (attr == "scene-switching")
        tempUseArrowKeys = true;
    }
    else if (val != "false")
    {
      ab::invalidAttributeParameterErr(val);
    }

    return true;
  }

  return false;
}
bool ab::setAttribute_String(std::string attr, std::string val)
{
  std::string temp;

  if (attr == "title")  // raw strings
  {
    tempTitle = val;
    return true;
  }
  else if (attr == "icon" || attr == "src" || attr == "font") // files
  {
    if (val[0] == '/')  // absolute path
      temp == val;
    else                // relative path
    {
      temp = getcwd(NULL, 80);
      temp += '/' + val;
    }

    if (attr == "icon")
      tempIcon = temp;
    else if (attr == "src")
      tempSrc = temp;
    else if (attr == "font")
      tempFont = temp;

    return true;
  }

  return false;
}
bool ab::setAttribute_List(std::string attr, std::string val)
{
  if (attr == "style")
  {
    bool errorFound = false;
    if (val == "plain")
    {
      tempFontStyle = ab::Constants::PLAIN;
    }
    if (val != "plain")
    {
      std::vector<std::string> styles = ab::separateList(val);

      for(int j = 0; j < styles.size(); j++)
      {
        if (styles[j] == "bold")
        {
          tempFontStyle |= ab::Constants::BOLD;
        }
        else if (styles[j] == "italic")
        {
          tempFontStyle |= ab::Constants::ITALIC;
        }
        else if (styles[j] == "underlined")
        {
          tempFontStyle |= ab::Constants::UNDERLINED;
        }
        else
        {
          errorFound = true;
          ab::unrecognizedObjectErr(styles[j]);
        }
      }

      if (errorFound)
        ab::invalidAttributeParameterErr(val);
    }
  }
  else
    return false;

  return true;
}
void ab::setTempAttributes(ab::lexObj &lexObject)
{
  std::vector<std::string> attrs = ab::lexAttributes(lexObject);
  bool attrFound = false;

  //sets the default values
  setDefaultAttrVals();

  for(int i = 0; i < attrs.size(); i += 2)
  {
    if (i < attrs.size())
    {
      if (!attrFound)
        attrFound = setAttribute_Int(attrs[i], attrs[i + 1]);
      if  (!attrFound)
        attrFound = setAttribute_Color(attrs[i], attrs[i + 1]);
      if  (!attrFound)
        attrFound = setAttribute_Bool(attrs[i], attrs[i + 1]);
      if  (!attrFound)
        attrFound = setAttribute_String(attrs[i], attrs[i + 1]);
      if (!attrFound)
        attrFound = setAttribute_List(attrs[i], attrs[i + 1]);
      if (!attrFound)
        ab::unrecognizedObjectErr(attrs[i]);

      attrFound = false;
    }
  }
}

void ab::createGraphicsObjects(std::vector<lexObj> lexObjects, std::vector<Scene> &scenes, sf::RenderWindow &window, sf::Color &windowColor, bool &keySwitching)
{
  bool windowExists = false;
  bool defaultSceneExists = false;
  bool innerTextSet = false;
  int sceneIndex = -1;
  int extraDupTags = 0;
  int indexMod = 0;

  for(int i = 0; i < lexObjects.size(); i++)
  {
    tempInner = "";

    if (lexObjects[i].getTypeID() == Constants::TAG)
    {
      setTempAttributes(lexObjects[i]);

      if (lexObjects[i].getValue() == "window" && !windowExists)
      {
        keySwitching = tempUseArrowKeys;
        windowExists = true;
        windowColor = tempBg;

        if (tempResize)
          window.create(sf::VideoMode(tempW, tempH), tempTitle, sf::Style::Default);
        else
          window.create(sf::VideoMode(tempW, tempH), tempTitle, sf::Style::Titlebar | sf::Style::Close);

        window.clear(windowColor);
        window.display();

        if (tempIcon != Constants::ICON_FILE_PLACEHOLDER)
        {
          if (fileExists(tempIcon))
          {
            sf::Image icon;
            icon.loadFromFile(tempIcon);
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
          }
          else
          {
            ab::fileNotFoundErr(tempIcon);
          }
        }
      }
      else if (lexObjects[i].getValue() == "scene")
      {
          sceneIndex++;
          scenes.push_back(ab::Scene());
          scenes[sceneIndex].isDisplaying = tempDefault;

          // if more than one default scene, set the first default scene as the only default scene (err checking)
          if (defaultSceneExists && tempDefault)
          {
            scenes[sceneIndex].isDisplaying = false;
            ab::tooManyDefaultScenesErr();
          }
      }
      else if (sceneIndex > -1)
      {
        // get inner text ///////////////////////
        if (lexObjects[i].getValue()[0] != '/')
        {
          indexMod = 0;

          for(int j = i + 1; j < lexObjects.size(); j++)
          {
            if (!innerTextSet && lexObjects[j].getTypeID() == Constants::INNER_TEXT)
            {
              tempInner = lexObjects[j].getValue();
              innerTextSet = true;
            }
            else if (lexObjects[j].getValue() == lexObjects[i].getValue())
            {
              extraDupTags++;
            }
            else if (lexObjects[j].getValue() == '/' + lexObjects[i].getValue())
            {
              if (extraDupTags == 0)
              {
                indexMod = j - i - 2;
                break;
              }
              else
                extraDupTags--;
            }
            else if (j == lexObjects.size() - 1)
            {
              if (innerTextSet)
                indexMod = 1;
              else
                indexMod = 0;

              ab::missingClosingTagErr(lexObjects[i].getValue());
              break;
            }
          }
        }
        /////////////////////////////////////////

        if (lexObjects[i].getValue() == "/rectangle" || lexObjects[i].getValue() == "rectangle")
        {
          if (tempInner == "")
            ab::addGraphic(scenes[sceneIndex], ab::Constants::RECTANGLE);
          else
            ab::addText(scenes[sceneIndex], ab::Constants::RECTANGLE, 24, ab::Constants::PLAIN);
        }
        else if (lexObjects[i].getValue() == "/circle" || lexObjects[i].getValue() == "circle")
        {
          if (tempInner == "")
            ab::addGraphic(scenes[sceneIndex], ab::Constants::CIRCLE);
          else
            ab::addText(scenes[sceneIndex], ab::Constants::CIRCLE, 24, ab::Constants::PLAIN);
        }
        else if (lexObjects[i].getValue() == "/triangle" || lexObjects[i].getValue() == "triangle")
        {
          if (tempInner == "")
            ab::addGraphic(scenes[sceneIndex], ab::Constants::TRIANGLE);
          else
            ab::addText(scenes[sceneIndex], ab::Constants::TRIANGLE, 24, ab::Constants::PLAIN);
        }
        else if (lexObjects[i].getValue() == "/image" || lexObjects[i].getValue() == "image")
        {
          if (fileExists(tempSrc))
          {
            scenes[sceneIndex].addImage(new ab::Image(tempX, tempY, tempW, tempH, tempSrc));
          }
          else
          {
            ab::fileNotFoundErr(tempSrc);
          }
        }
        else if (lexObjects[i].getValue() == "/paragraph" || lexObjects[i].getValue() == "paragraph")
        {
          ab::addText(scenes[sceneIndex], ab::Constants::RECTANGLE, 24, ab::Constants::PLAIN);
        }
        else if (lexObjects[i].getValue() == "/header-lg" || lexObjects[i].getValue() == "header-lg")
        {
          ab::addText(scenes[sceneIndex], ab::Constants::RECTANGLE, 42, ab::Constants::BOLD);
        }
        else if (lexObjects[i].getValue() == "/header-m" || lexObjects[i].getValue() == "header-m")
        {
          ab::addText(scenes[sceneIndex], ab::Constants::RECTANGLE, 36, ab::Constants::BOLD);
        }
        else if (lexObjects[i].getValue() == "/header-sm" || lexObjects[i].getValue() == "header-sm")
        {
          ab::addText(scenes[sceneIndex], ab::Constants::RECTANGLE, 30, ab::Constants::BOLD);
        }
        else if (lexObjects[i].getValue() != "/scene" && lexObjects[i].getValue() != "/window")
        {
          ab::unrecognizedObjectErr(lexObjects[i].getValue());
        }

        i += indexMod;
      }
    }
  }

  // if only one scene, set that automatically to default (for user confenience)
  if (sceneIndex == 0)
    scenes[0].isDisplaying = true;
}
