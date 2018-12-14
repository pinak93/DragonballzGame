#ifndef SPRITEBOX__H
#define SPRITEBOX__H
#include <string>
#include "drawable.h"

class SpriteBox : public Drawable {
public:
  SpriteBox(const std::string&);
  SpriteBox(const std::string&, const Vector2f& pos, const Vector2f& vel, 
         const Image*);
  SpriteBox(const SpriteBox&);
  virtual ~SpriteBox() { } 
  SpriteBox& operator=(const SpriteBox&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const { 
    return image->getSurface();
  }
  int getScaledWidth()  const { return getScale()*image->getWidth();  } 
  int getScaledHeight() const { return getScale()*image->getHeight(); } 

private:
  const Image * image;

protected:
  int worldWidth;
  int worldHeight;

  int getDistance(const SpriteBox*) const;
  Vector2f makeVelocity(int, int) const;
};
#endif
