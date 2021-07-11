/*
// This file contains many different types of graphical objects
*/

#ifndef __COMPONENTS__INCLUDE__
#define __COMPONENTS__INCLUDE__

#include <SFML/Graphics.hpp>
#include "errFormatter.h"
#include "utils.h"

namespace ab
{
  /*
  A class that represents a simple triangle, circle, or a rectangle
  */
  class Graphic
  {
    public:
      Graphic();
      Graphic(int x, int y, int width, int height, unsigned int _shapeType, sf::Color fill);

      /*
      setTransform changes the position and size of the graphics object
      */
      void setTransform(int x, int y, int width, int height);
      /*
      setFill changes the fill color of the graphics object
      */
      void setFill(sf::Color fill);

      /*
      draw, takes a window object and draws the represented graphics object as long as a valid type was chosen
      */
      void draw(sf::RenderWindow &window);

    protected:
      sf::VertexArray vertexArray;
      sf::CircleShape circle;

      int shapeType;
  };
  /*
  Text represents a piece of text with multiple customizable properties
  */
  class Text: Graphic
  {
    public:
      Text(int x, int y, int width, int height, unsigned int _shapeType, sf::Color background, sf::Color foreground, std::string textVal, std::string fontFile, int fontSize, unsigned int fontStyle);

      /*
      // Sets the foreground color (The text color)
      */
      void setForeground(sf::Color col);
      /*
      // Bitch just look at the name of the method
      */
      void setText(std::string str);
      /*
      // Paints the text AND the graphics object
      */
      void drawText(sf::RenderWindow &window);
      /*
      fixTextOverflow adjusts the text value to account for text overflow
      */
      void fixTextOverflow(int width, int fontSize);

    private:
      sf::Text text;
      sf::Font font;
      bool canDraw;
  };
  /*
  A class that represents an image taken from an external file
  */
  class Image
  {
    public:
      Image();
      Image(int x, int y, int width, int height, std::string src, sf::Color recolor = sf::Color(255, 255, 255, 255));

      /*
      // Again, look at the fucking method name
      */
      void draw(sf::RenderWindow &window);

    private:
      sf::Texture texture;
      sf::Sprite sprite;
      bool canDraw;
  };
  /*
  A class that represents the graphics objects that are currently being displayed on the window
  */
  class Scene
  {
    public:
      /*
      The default constructor
      */
      Scene();
      /*
      getGraphics returns a list of the graphics objects contain within the scene object
      */
      std::vector<Graphic> getGraphics();
      /*
      getImages returns a list of images
      */
      std::vector<Image*> getImages();
      /*
      getText returns the internal list of text objects
      */
      std::vector<Text*> getText();
      /*
      addGraphic adds a new graphics object to the list of graphics object within the scene object
      */
      void addGraphic(Graphic g);
      /*
      addImage adds a new image to the internal list of images
      */
      void addImage(Image *i);
      /*
      addText adds a new text object to the internal list of text graphics objects.
      */
      void addText(Text* t);

      bool isDisplaying;

    private:
      std::vector<Graphic> graphics;
      std::vector<Image*> images;
      std::vector<Text*> text;
  };
}

#endif
