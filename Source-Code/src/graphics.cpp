#include "graphics.h"
#include <iostream>

ab::Graphic::Graphic()
{
  shapeType = -1;
}
ab::Graphic::Graphic(int x, int y, int width, int height, unsigned int _shapeType, sf::Color fill)
{
  shapeType = _shapeType;

  if (shapeType == ab::Constants::RECTANGLE)
  {
    vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
    vertexArray.resize(4);
    vertexArray[0].color = fill;
    vertexArray[0].position = sf::Vector2f(x, y + height);
    vertexArray[1].color = fill;
    vertexArray[1].position = sf::Vector2f(x, y);
    vertexArray[2].color = fill;
    vertexArray[2].position = sf::Vector2f(x + width, y);
    vertexArray[3].color = fill;
    vertexArray[3].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::TRIANGLE)
  {
    vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertexArray.resize(3);
    vertexArray[0].color = fill;
    vertexArray[0].position = sf::Vector2f(x + width / 2, y);
    vertexArray[1].color = fill;
    vertexArray[1].position = sf::Vector2f(x, y + height);
    vertexArray[2].color = fill;
    vertexArray[2].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::CIRCLE)
  {
    circle.setPosition(x, y);
    circle.setRadius(width);
    circle.setFillColor(fill);
  }
}

void ab::Graphic::setTransform(int x, int y, int width, int height)
{
  if (shapeType == ab::Constants::RECTANGLE)
  {
    vertexArray[0].position = sf::Vector2f(x, y + height);
    vertexArray[1].position = sf::Vector2f(x, y);
    vertexArray[2].position = sf::Vector2f(x + width, y);
    vertexArray[3].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::TRIANGLE)
  {
    vertexArray[0].position = sf::Vector2f(x + width / 2, y);
    vertexArray[1].position = sf::Vector2f(x, y + height);
    vertexArray[2].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::CIRCLE)
  {
    circle.setPosition(x, y);
    circle.setRadius(width);
  }
  else
  {
    ab::internalErr(39); // CHANGE THIS WHEN NEEDED /////////////////////////////////////////////////////////////////////////
  }
}
void ab::Graphic::setFill(sf::Color fill)
{
  if (shapeType == ab::Constants::RECTANGLE || shapeType == ab::Constants::TRIANGLE)
  {
    vertexArray[0].color = fill;
    vertexArray[1].color = fill;
    vertexArray[2].color = fill;

    if (shapeType == ab::Constants::RECTANGLE)
      vertexArray[3].color = fill;
  }
  else if (shapeType == ab::Constants::CIRCLE)
  {
    circle.setFillColor(fill);
  }
  else
  {
    ab::internalErr(69); // CHANGE THIS WHEN NEEDED /////////////////////////////////////////////////////////////////////////
  }
}

void ab::Graphic::draw(sf::RenderWindow &window)
{
  if (shapeType == ab::Constants::RECTANGLE || shapeType == ab::Constants::TRIANGLE)
  {
    window.draw(vertexArray);
  }
  else if (shapeType == ab::Constants::CIRCLE)
  {
    window.draw(circle);
  }
  else
  {
    ab::internalErr(90); // CHANGE THIS WHEN NEEDED /////////////////////////////////////////////////////////////////////////
  }
}
ab::Text::Text(int x, int y, int width, int height, unsigned int _shapeType, sf::Color background,
               sf::Color foreground, std::string textVal, std::string fontFile, int fontSize, unsigned int fontStyle)
{
  shapeType = _shapeType;
  canDraw = false;

  if (shapeType == ab::Constants::RECTANGLE)
  {
    canDraw = true;

    vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
    vertexArray.resize(4);
    vertexArray[0].color = background;
    vertexArray[0].position = sf::Vector2f(x, y + height);
    vertexArray[1].color = background;
    vertexArray[1].position = sf::Vector2f(x, y);
    vertexArray[2].color = background;
    vertexArray[2].position = sf::Vector2f(x + width, y);
    vertexArray[3].color = background;
    vertexArray[3].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::TRIANGLE)
  {
    canDraw = true;

    vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertexArray.resize(3);
    vertexArray[0].color = background;
    vertexArray[0].position = sf::Vector2f(x + width / 2, y);
    vertexArray[1].color = background;
    vertexArray[1].position = sf::Vector2f(x, y + height);
    vertexArray[2].color = background;
    vertexArray[2].position = sf::Vector2f(x + width, y + height);
  }
  else if (shapeType == ab::Constants::CIRCLE)
  {
    canDraw = true;

    circle.setPosition(x, y);
    circle.setRadius(width);
    circle.setFillColor(background);
  }

  if (!fileExists(fontFile))
  {
    if (fontFile != ab::Constants::FONT_FILE_PLACEHOLDER)
      ab::fileNotFoundErr(fontFile);
    canDraw = false;
  }
  else
  {
    font.loadFromFile(fontFile);
    text.setFont(font);
    text.setStyle(fontStyle);
    text.setCharacterSize(fontSize);
    text.setString(textVal);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(foreground);
    fixTextOverflow(width, fontSize);
  }
}
void ab::Text::drawText(sf::RenderWindow &window)
{
  if (canDraw)
  {
    if (shapeType == ab::Constants::RECTANGLE || shapeType == ab::Constants::TRIANGLE)
    {
      window.draw(vertexArray);
    }
    else if (shapeType == ab::Constants::CIRCLE)
    {
      window.draw(circle);
    }
    else
    {
      ab::internalErr(165); // CHANGE THIS WHEN NEEDED /////////////////////////////////////////////////////////////////////////
    }

    if (text.getString().toAnsiString() != "")
      window.draw(text);
  }
}
void ab::Text::setForeground(sf::Color col)
{
  text.setFillColor(col);
}
void ab::Text::setText(std::string str)
{
  text.setString(str);
}
void ab::Text::fixTextOverflow(int width, int fontSize)
{
  std::string textVal = text.getString().toAnsiString();
  int rawTextW = (text.getGlobalBounds().width - text.getGlobalBounds().left) * 1.3; // the piexl width of the text object
  int newlineSpacing = textVal.length() / (rawTextW / (width * 1.3)); // the amount of characters between each overflow point
  int temp = 0;

  if (textVal.length() > 0 && rawTextW - width > fontSize * 2.6) // if text : graphic overlap > max overlap
  {
    for(int i = 0; i < textVal.length(); i++)
    {
      temp++;

      if (textVal[i] == '\n') // the newline normally counts as a character, but it shouldn't in
        temp--; // this situation because it doesn't take up screen space

      if (textVal[i] == '\n' || i == textVal.length() - 1 || temp >= newlineSpacing)
      {
        if (temp >= newlineSpacing)
        {
          for(int j = i - 1; j >= 0; j--)
          {
            if (textVal[j] == ' ')
            {
              textVal[j] = '\n';

              for(int t = j + 1; t < textVal.length(); t++)
              {
                if (textVal[t] == '\n')
                {
                  textVal[t] = ' ';
                  break;
                }
              }

              break;
            }
          }
        }

        temp = 0;
      }
    }

    std::cout << "AAAAAAAAHHHHHHHHHH:\n" << textVal << '\n';

    text.setString(textVal);
  }
  // else
  // {
  //    Resize the background object to fit with the text
  // }
}

ab::Image::Image()
{
  canDraw = false;
}
ab::Image::Image(int x, int y, int width, int height, std::string src, sf::Color recolor)
{
  canDraw = true;


  if (!ab::fileExists(src))
  {
    ab::fileNotFoundErr(src);
    canDraw = false;
  }
  else
  {
    texture.loadFromFile(src);
    texture.setSmooth(true);
    sprite.setColor(recolor);
    sprite.setTexture(texture, true);
    sprite.scale(width / sprite.getTextureRect().width, height / sprite.getTextureRect().height);
    sprite.setPosition(sf::Vector2f(x, y));
  }
}
void ab::Image::draw(sf::RenderWindow &window)
{
  if (canDraw)
  {
    window.draw(sprite);
  }
}

ab::Scene::Scene()
{
  isDisplaying = false;
}
std::vector<ab::Graphic> ab::Scene::getGraphics()
{
  return graphics;
}
std::vector<ab::Image*> ab::Scene::getImages()
{
  return images;
}
std::vector<ab::Text*> ab::Scene::getText()
{
  return text;
}
void ab::Scene::addGraphic(ab::Graphic g)
{
  graphics.push_back(g);
}
void ab::Scene::addImage(Image *i)
{
  images.push_back(i);
}
void ab::Scene::addText(Text *t)
{
  text.push_back(t);
}
