#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&, const Vector2f position, const int width, const int height);
	
  MultiSprite(const MultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return Main_Walk[currentFrame]; 
  }
	virtual  void SetImage_Switch()  { 
    
    if(setter)
    {
		currentFrame=0;
      Main_Walk=Walk_L;
		numberOfFrames=numberOfFrames_L;
    }
    else
    {
      currentFrame=0;
      Main_Walk=Walk_R;
		numberOfFrames=numberOfFrames_R;
    }
  
  }
	
	
  int getScaledWidth()  const { 
    return getScale()*Main_Walk[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*Main_Walk[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return Main_Walk[currentFrame]->getSurface();
  }
	
		virtual void setPlayerPos(const Vector2f& p) { Playerposition = p; }
	

protected:
   std::vector<Image *> Main_Walk;
  std::vector<Image *> Walk_R;
  std::vector<Image *> Walk_L;
  std::string Name;
  bool setter;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned numberOfFrames_R;
  unsigned numberOfFrames_L;
  unsigned frameInterval;
  float timeSinceLastFrame;
	 Vector2f Playerposition;
  int PlayerW, PlayerH;
  int worldWidth;
  int worldHeight;
  void advanceFrame(Uint32 ticks);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
