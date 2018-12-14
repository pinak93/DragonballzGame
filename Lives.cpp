#include<sstream>
#include "healthBar.h"
#include "renderContext.h"

HealthBar::HealthBar(const std::string& name) :  
  Drawable("Lives", 
           Vector2f(X,Y), 
           Vector2f(0,0) ),
Lives_Value(Gamedata::getInstance().getXmlInt("Beerus/Lives/Value")),
Lives(Gamedata::getInstance().getXmlBool(name+"/Flag")),
Lives_img( ImageFactory::getInstance().getImage("Beerus/Lives"))
{}
void HealthBar::update(Uint32 ticks) {
	std::cout<<ticks;
}

void HealthBar::update(float power,int Lives) {
  Lives_Value=Lives;
}
void HealthBar::draw() const {
  if(Lives)
  {
  int x = static_cast<int>(getX());
for(int i=Lives_Value;i>0;i--)
	{
  x+=Lives_img->getWidth();
		Lives_img->draw(getX(),getY()+20,1);
	}	
  }
  
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
if(currentLength>=0)
	{
  SDL_RenderFillRect( renderer, &healthRect );
	}
  // Set the  color for the health bar outline:
  SDL_SetRenderDrawColor( 
    renderer, barColor.r, barColor.g, barColor.b, barColor.a );
  SDL_RenderDrawRect( renderer, &barRect );
	
	
  
	
}

