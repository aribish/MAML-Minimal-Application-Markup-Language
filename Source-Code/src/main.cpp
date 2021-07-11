/*
// This file takes all lists/functions/class/... and structures the actual program
*/

#include <SFML/Graphics.hpp>
#include "lexer.h"
#include "lexObj.h"
#include "actionParser.h"
#include "errFormatter.h"

sf::Color windowColor;
sf::RenderWindow window;
sf::Event event;

std::string loadFile(std::string path, int buf)
{
  char contents[buf];
  std::ifstream in;

  in.open(path);
  in.read(contents, buf);
  in.close();

  return contents;
}

int main(int argc, char **argv)
{
  bool keySwitching = false;
  int currentScene = -1;
  std::string doc;
  std::vector<ab::lexObj> lexObjects;
  std::vector<ab::Scene> scenes;

  if (argc == 2)
  {
    std::string path;

    if (argv[1][0] == '/') // if absolute path
      path = argv[1];
    else // if relative path
    {
      path = getcwd(NULL, 64);
      path += "/";
      path += argv[1];
    }

    if (ab::fileExists(path))
    {
      doc = loadFile(path, 3200);
      lexObjects = ab::lexDocument(doc);

      ab::setRootPath(path.erase(path.find_last_of("/") + 1));
      ab::createGraphicsObjects(lexObjects, scenes, window, windowColor, keySwitching);

      while(window.isOpen())
      {
        while(window.pollEvent(event))
        {
          // events ///////////////////
          if (event.type == sf::Event::Closed)
          {
            window.close();
          }
          else if (event.type == sf::Event::KeyPressed && keySwitching)
          {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            {
              scenes[currentScene].isDisplaying = false;

              if (event.key.code == sf::Keyboard::Left)
              {
                if (currentScene > 0)
                  currentScene--;
                else
                  currentScene = scenes.size() - 1;
              }
              else if (event.key.code == sf::Keyboard::Right)
              {
                if (currentScene < scenes.size() - 1)
                  currentScene++;
                else
                  currentScene = 0;
              }

              scenes[currentScene].isDisplaying = true;
            }
          }
          /////////////////////////////

          for(int i = 0; i < scenes.size(); i++)
          {
            if (scenes[i].isDisplaying)
            {
              if (currentScene == -1)
                currentScene = i;

              window.clear(windowColor);
              for(int j = 0; j < scenes[i].getGraphics().size(); j++)
              {
                scenes[i].getGraphics()[j].draw(window);
              }
              for(int j = 0; j < scenes[i].getImages().size(); j++)
              {
                scenes[i].getImages()[j]->draw(window);
              }
              for(int j = 0; j < scenes[i].getText().size(); j++)
              {
                scenes[i].getText()[j]->drawText(window);
              }
              window.display();
            }
          }
        }
      }
    }
    else
    {
      ab::fileNotFoundErr(argv[1]);
    }
  }
  else if (argc == 1)
  {
    ab::fileNotSuppliedErr("No Snippet Available");
  }
  else if (argc > 2)
  {
    std::string snippet = argv[1];

    for(int i = 2; i < argc; i++)
    {
      snippet += ", ";
      snippet += argv[i];
    }

    ab::tooManyFilesErr(snippet);
  }

  return 0;
}
