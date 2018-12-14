#include <vector>
#include <SDL.h>
#include "menu.h"
#include "sound.h"
class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  bool play();
  int getOptionChoice() const { return optionChoice; }
  bool starsOptionChosen();
bool getGameReady() const { return gameReady;}
	void setGameReady(const bool N ) {gameReady=N;}
  bool getExit() {return exit;}  
  void setExit(const bool N ) {exit=N;}
    std::string getPlayerName() const {return menu.getPlayerName();}
  
private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;
  int optionChoice;
  bool starsOption,gameReady,exit;
Image* wall_img;
	SDLSound sound;
  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
