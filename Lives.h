

#include "SDL.h"
#include "gameData.h"
#include "drawable.h"

class Lives : public Drawable {
public:
  Lives(const std::string&);
  void draw() const;
  void update(Uint32);
  void update(int);
  void reset() { currentLength = barRect.w; }

  Lives(const Lives&) = delete;
  Lives& operator=(const Lives&) = delete;

  virtual int getScaledWidth() const  { return Lives_img->getWidth(); }
  virtual int getScaledHeight() const { return Lives_img->getHeight(); }
  virtual const Image* getImage() const { 
    throw std::string("No image in HealthBar");
  }
  virtual const SDL_Surface* getSurface() const { 
    throw std::string("No Surface");
  }
  
  
private:

  int Lives_Value;
  	bool Lives;
 Image * Lives_img;

};
