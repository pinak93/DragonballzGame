#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "sprite.h"
#include "gameData.h"
#include "menuEngine.h"
#include "renderContext.h"

MenuEngine::~MenuEngine() { }

MenuEngine::MenuEngine() :
  clock( Clock::getInstance() ),
  renderer( RenderContext::getInstance().getRenderer() ),
  menu( renderer ),
  optionChoice(-1),
  starsOption(false),
gameReady(false),
exit(false),
wall_img( ImageFactory::getInstance().getImage("menu/Wall")),
sound()
{
}

void MenuEngine::draw() const {
 	wall_img->draw(0,0);
	menu.draw();

  SDL_RenderPresent(renderer);
}

bool MenuEngine::starsOptionChosen() { 
  if ( starsOption ) {
    starsOption = false;
    return true; 
  }
  return false;
}

void MenuEngine::update(Uint32 ticks) {
	menu.update(ticks);
}

bool MenuEngine::play() {
  SDL_Event event;
  const Uint8* keystate;
	Uint32 ticks = clock.getElapsedTicks();
  bool done = false;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) {setGameReady(false); done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
        menu.setPlayScreen(false);
          setGameReady(false);
        }
        if (keystate[SDL_SCANCODE_DOWN] ) menu.incrIcon();
        if (keystate[SDL_SCANCODE_UP] ) menu.decrIcon();
        if (keystate[SDL_SCANCODE_RETURN] ) {
          if(!menu.getPlayScreen()){
          optionChoice = menu.getOptionNo();
          if ( optionChoice == 0 ) {menu.setPlayScreen(true);setGameReady(true);}
          if ( optionChoice == 1 ) { done = true; break;}
			  if ( optionChoice == 2 ) {done = true; 
										setExit(true);
										
										break; }
		  }else
		  {
			done=  true;  
		  }
			
			
        }
      }
    }
    // In this section of the event loop we allow key bounce:
	  ticks = clock.getElapsedTicks();
	  if(ticks > 0)
	  {
    draw();
   		sound.Looping();
	 update(ticks);
	  }
  }
	
	return false;
}
