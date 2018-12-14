#include <vector>
#include <SDL.h>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "HUD.h"
#include "drawable.h"
#include "player.h"
#include "healthBar.h"
#include "collisionStrategy.h"
#include "sound.h"
class Engine {
public:
  Engine (std::string);
  ~Engine ();
  bool play();
private:
  const RenderContext& rc;
  Clock& clock;
	  HealthBar* healthBar;
  HealthBar* powerBar;
  HUD& hud;
  SDL_Renderer * const renderer;
	  const IoMod& io;
  World world_back;
  World world_mid;
  World world_top;
   Drawable* getImage(const std::string&);
  std::string Name;
	int loc,Num;
  Viewport& viewport;
  std::vector<Drawable *> Sprites;
	Drawable * player;
  int currentSprite;
 SDL_Color Font_Color;
  bool makeVideo;
  bool InfoTab;
  bool FlyMode;
   //   SDLSound sound;
  unsigned spawnEnimiesTime,lastTimeSinceSpawn,MaxEnimies;
  int spriteCounter;
      CollisionStrategy* strategy;
  void draw() const;
  void update(Uint32);
 //void displayTab() const;
  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void printScales() const;
  void checkForCollisions();
	  void ReSpawn();
};
