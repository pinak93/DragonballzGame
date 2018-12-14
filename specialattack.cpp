#include "multisprite.h"
#include "gameData.h"
#include "imageFactory.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name,const Vector2f position, const int width, const int height) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
Main_Walk( ImageFactory::getInstance().getImages(name) ),
  Walk_R( ImageFactory::getInstance().getImages(name) ),
  Walk_L( ImageFactory::getInstance().getImages(name) ),

  Name(name),
setter(false),
  currentFrame(0),
	numberOfFrames(Gamedata::getInstance().getXmlInt(name+"/frames")),
  numberOfFrames_R( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  numberOfFrames_L( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
Playerposition(position),
PlayerW(width), 
PlayerH(height),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  Main_Walk(s.Main_Walk),
  Walk_R( s.Walk_R),
  Walk_L( s.Walk_L ),
  Name(s.Name),
setter(s.setter),
  currentFrame(s.currentFrame),
numberOfFrames(s.numberOfFrames),
   numberOfFrames_R( s.numberOfFrames_R ),
  numberOfFrames_L( s.numberOfFrames_L ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
Playerposition(s.Playerposition),
PlayerW(s.PlayerW), 
PlayerH(s.PlayerH),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
   Drawable::operator=(s);
  Main_Walk=(s.Main_Walk);
  Walk_R=( s.Walk_R);
  Walk_L=( s.Walk_L );
  Name = (s.Name);
	setter=(s.setter);
  currentFrame = (s.currentFrame);
	numberOfFrames=(s.numberOfFrames);
    numberOfFrames_R=( s.numberOfFrames_R );
  numberOfFrames_L=( s.numberOfFrames_L );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
	Playerposition=(s.Playerposition);
PlayerW=(s.PlayerW); 
PlayerH=(s.PlayerH);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void MultiSprite::draw() const { 
  Main_Walk[currentFrame]->draw(getX(), getY(), getScale());
	
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
	
  if ( getX() < 0) {
	  setX(worldWidth);
	  setVelocityX( -fabs( getVelocityX() ) );
	  std::cout<<"test";
	  if(setter) {setter=false;}else{setter=true;};
	   SetImage_Switch();
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}
