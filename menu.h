#include <vector>
#include <string>
#include "SDL.h"
#include "gameData.h"
#include "clock.h"
#include "ioMod.h"
#include "sprite_box.h"
#include "menu_multisprite.h"

class Menu {
public:
  Menu(SDL_Renderer*);
  void draw() const;
void update(Uint32);
  void incrIcon();
  void decrIcon();

~Menu();
  int getOptionNo() const { return currentOption; }
  int getNumStars() const;
	void setPlayScreen(const bool) ;
  	bool getPlayScreen() const {return NextScreen;}
  std::string getPlayerName() const {
    return Player[Player_count]->getPlayerName();}
  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
private:
  SDL_Renderer* renderer;
  Gamedata& gdata;
  SDL_Rect hudFrame;
  SDL_Color menuColor;
  Clock& clock;
  IoMod& io;
  std::vector<std::string> options;
  std::vector<int> optionLoc;
  SpriteBox clicks;
  int currentClick;
  int currentOption;
  int spaces;
  int startClickX;
  int startClickY;
  int clickX;
  int clickY;
	bool NextScreen;
  int players, Player_count;
	std::vector<MenuMultiSprite *> Player;
  void drawBackground() const;
  int getInputEventLoop() const;
};
