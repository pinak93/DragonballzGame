#include <SDL_image.h>
#include "HUD.h"
#include "gameData.h"
#include "renderContext.h"
#include <sstream>

HUD::~HUD() { 
}

HUD& HUD::getInstance() {
  static HUD instance;
  return instance;
}
HUD::HUD() : 
 renderer( RenderContext::getInstance().getRenderer() ),
Name(Gamedata::getInstance().getXmlStr("PlayerName/Name")),
startX(Gamedata::getInstance().getXmlInt("HUD/Xloc")),
startY(Gamedata::getInstance().getXmlInt("HUD/Yloc")),
width(Gamedata::getInstance().getXmlInt("HUD/width")),
height(Gamedata::getInstance().getXmlInt("HUD/height")),
Border(Gamedata::getInstance().getXmlBool("HUD/Border")),
Bg_Color({0xff, 0,0,0}),
Text(Gamedata::getInstance().getXmlStr("HUD/Text"))
{

	
  Bg_Color.r = Gamedata::getInstance().getXmlInt("HUD/Bg_red");
  Bg_Color.g = Gamedata::getInstance().getXmlInt("HUD/Bg_green"); 
  Bg_Color.b = Gamedata::getInstance().getXmlInt("HUD/Bg_blue");
  Bg_Color.a = Gamedata::getInstance().getXmlInt("HUD/Bg_alpha");
}

void HUD::draw(int fps,bool InfoTab,bool FlyMode) const {
 	if(InfoTab)
	{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, Bg_Color.r,Bg_Color.g,Bg_Color.b,Bg_Color.a );
   SDL_Rect r;
        r.x = startX;  
		r.y = startY;
        r.w = width;
        r.h = height;   
         SDL_RenderFillRect( renderer, &r ); 
	std::stringstream strm;
	strm << Text ;
		strm <<'\n' ;
	strm << "C - Toggle Fly Mode";
		strm << '\n';
	strm << "F - MegaBlast";
		strm << '\n';	
	strm << "SPACE - KiBlast";
		strm << '\n';	
	strm << "E - Toggle Triple Fire Mode";
		strm << '\n';		
	strm << "FPS:"+std::to_string(fps);
		strm << '\n';
		if(FlyMode )
		{	
	strm << "Fly Movement";
	strm << '\n';
	strm << "W - Up , S - Down";
	strm << '\n';
	strm << "A - Left , D - Right";
	strm << '\n';
	}
	else
	{	
	strm << "Walking";
	strm << '\n';
	strm << "W - Jump";
	strm << '\n';
	strm << "A - Right , D - Left";
	strm << '\n';
	}
	strm << '\n';	
	strm << "Combact";
	strm << '\n';
	strm << "L - Kick";
	strm << '\n';
	strm << "I + L - Double Kick";
	strm << '\n';
	strm << "J - Punch";
	strm << '\n';
	strm << "I + J - Heavy Punch";
	IoMod::getInstance().writeText(strm.str(),startX+10,startY+10,Bg_Color);
	}
	

}

