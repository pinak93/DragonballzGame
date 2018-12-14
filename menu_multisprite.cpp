#include "menu_multisprite.h"
#include "gameData.h"
#include "imageFactory.h"

void MenuMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
		
	}
}

MenuMultiSprite::MenuMultiSprite( const std::string& name, int X, int Y) :
  Drawable(name, 
           Vector2f(X,Y), 
           Vector2f(0,0)
           ),
  images( ImageFactory::getInstance().getImages(name) ),
PlayerName(Gamedata::getInstance().getXmlStr(name+"/Tag")),
name(Gamedata::getInstance().getXmlStr(name+"/Name")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
	  
  }

MenuMultiSprite::MenuMultiSprite(const MenuMultiSprite& s) :
  Drawable(s), 
  images(s.images),
PlayerName(s.PlayerName),
name(s.name),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

MenuMultiSprite& MenuMultiSprite::operator=(const MenuMultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
		PlayerName=(s.PlayerName);
	name=(s.name);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void MenuMultiSprite::draw() const { 
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void MenuMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr); 

}




