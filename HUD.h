#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ioMod.h"

class HUD {
public:
   static HUD& getInstance();
  ~HUD();
	void draw(int,bool,bool ) const;
private:
  SDL_Renderer* renderer;
	std::string Name;
  int startX, startY,width,height;	
  bool Border;
	SDL_Color Bg_Color;
 std::string Text;
  
  HUD();
  HUD(const HUD&);
  HUD& operator=(const HUD&);
	
};
