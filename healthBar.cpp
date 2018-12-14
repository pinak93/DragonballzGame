#include<sstream>
#include "healthBar.h"
#include "renderContext.h"
#include "viewport.h"

HealthBar::HealthBar(const std::string& name,const std::string& Player) :  
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")) 
           ),
  renderer(RenderContext::getInstance().getRenderer()),
  barRect( { Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
             Gamedata::getInstance().getXmlInt(name+"/startLoc/y"),
             Gamedata::getInstance().getXmlInt(name+"/width"),
             Gamedata::getInstance().getXmlInt(name+"/height")}
  ),
  currentLength(barRect.w), 
  increment(barRect.w/Gamedata::getInstance().getXmlInt(name+"/increment")),
  interval(Gamedata::getInstance().getXmlInt(name+"/interval")),
  deltaTime(0),
Lives_Value(Gamedata::getInstance().getXmlInt(Player+"/Lives/Value")),
Lives(Gamedata::getInstance().getXmlBool(name+"/Flag")),
Lives_img( ImageFactory::getInstance().getImage(Player+"/Lives")),
  barColor(
    {(Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/r"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/g"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/b"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/a")}
  ),
  backColor(
    {(Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/r"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/g"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/b"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/a")}
  )
{}
void HealthBar::update(Uint32 ticks) {
	ticks++;
}

void HealthBar::update(float power,int Lives) {
	if((power<=220) && (power>=0))
	{
  currentLength=power;
}
  
  Lives_Value=Lives;
}
void HealthBar::draw() const {

  
  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // Set the health bar background color:
  SDL_SetRenderDrawColor( 
    renderer, backColor.r, backColor.g, backColor.b, backColor.a );
  // Draw the  background
  SDL_RenderFillRect( renderer, &barRect );

  SDL_SetRenderDrawColor( 
    renderer, barColor.r, barColor.g, barColor.b, barColor.a );
  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  SDL_Rect healthRect = {x, y, currentLength, barRect.h};
  
    if(Lives)
  {
  int x = static_cast<int>(getX());
for(int i=Lives_Value;i>0;i--)
	{

		Lives_img->draw((x+Viewport::getInstance().getX()),(getY()+20+Viewport::getInstance().getY()));
    x+=Lives_img->getWidth()+10;
	}	
  }
  
if(currentLength>0)
	{
  SDL_RenderFillRect( renderer, &healthRect );
	}
  // Set the  color for the health bar outline:
  SDL_SetRenderDrawColor( 
    renderer, barColor.r, barColor.g, barColor.b, barColor.a );
  SDL_RenderDrawRect( renderer, &barRect );
	
	
  
	
}

