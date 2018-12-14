// This is the "pointers" example in the Brian example

#include <vector>
#include <list>
#include "chunk.h"
#include "gameData.h"
#include "imageFactory.h"


class ExplodingProjectile : public Sprite {
public:
explicit ExplodingProjectile(const std::string& s,int X,int Y) :
   Sprite("Explosion", 
           Vector2f(X,Y), 
           Vector2f(0,0),
		  ImageFactory::getInstance().getImage(s)
           ),
Main(ImageFactory::getInstance().getImages(s)),
currentFrame(0),
numberOfFrames(Gamedata::getInstance().getXmlInt(s+"/frames")),
frameInterval(Gamedata::getInstance().getXmlInt(s+"/frameInterval")),
DoneExploding(false),
timeSinceLastFrame(0)
{}
  
  
  ~ExplodingProjectile();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual bool getExploding() const {return DoneExploding;}
  
   std::vector<Image *> Main;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  bool DoneExploding;
    float timeSinceLastFrame;
   void advanceFrame(Uint32 ticks);

};
