#include <cmath>
#include <random>
#include <functional>
#include "bulletsprite.h"
#include "gameData.h"
#include "renderContext.h"



BulletSprite::~BulletSprite() { } 

BulletSprite::BulletSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Image* img,const Image* imgL,const Image* imgR):
  Drawable(n, pos, vel), 
  image( img ),
	imageL(imgL),
	imageR(imgR),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

BulletSprite::BulletSprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")) 
           ),
  image( RenderContext::getInstance().getImageR(name) ),
  imageL( RenderContext::getInstance().getImageL(name) ),
  imageR( RenderContext::getInstance().getImageR(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

BulletSprite::BulletSprite(const BulletSprite& s) :
  Drawable(s), 
  image(s.image),
imageL(s.imageL),
imageR(s.imageR),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

BulletSprite& BulletSprite::operator=(const BulletSprite& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
	imageL=(rhs.imageL);
imageR=(rhs.imageR);
worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}



void BulletSprite::draw() const { 
  if(getScale() < SCALE_EPSILON) return;
	
   image->draw(getX(), getY(), getScale()); }

void BulletSprite::update(Uint32 ticks) { 

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
 if(getVelocityX()<0)
 {
	image=imageL; 
 }
	if(getVelocityX()>0)
 {
	image=imageR; 
 } 
	 
}
