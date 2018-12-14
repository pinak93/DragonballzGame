#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "player.h"
#include "multisprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "drawable.h"

Engine::~Engine() { 
delete healthBar;
delete	powerBar;
	
	delete strategy;
for (auto& ptr : Sprites) {
	delete ptr;
}


	
//  delete checkCollision;
delete player;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine(std::string PlayerName) :
  rc( RenderContext::getInstance() ),
  clock( Clock::getInstance() ),
  healthBar(new HealthBar("HealthBar",PlayerName)),
powerBar(new HealthBar("PowerBar",PlayerName)),
  hud(HUD::getInstance()),
  renderer( rc.getRenderer() ),
  io( IoMod::getInstance() ),
  world_back("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  world_mid("mid", Gamedata::getInstance().getXmlInt("mid/factor") ),
  world_top("top", Gamedata::getInstance().getXmlInt("top/factor") ),
  Name(Gamedata::getInstance().getXmlStr("PlayerName/Name").c_str()),
	loc(Gamedata::getInstance().getXmlInt("PlayerName/loc")),
Num(Gamedata::getInstance().getXmlInt("Sprites/Num")),
  viewport( Viewport::getInstance() ),
Sprites(),
 player(new Player(PlayerName)),
  currentSprite(0),
Font_Color({0xff, 0,0,0}),
  makeVideo( false ),
InfoTab(true),
FlyMode(false),
spawnEnimiesTime(Gamedata::getInstance().getXmlInt("PlayerName/SpwanEnimiesTime")*1000),
lastTimeSinceSpawn(0),
MaxEnimies(Gamedata::getInstance().getXmlInt("PlayerName/MaxEnimies")),
spriteCounter(0),
strategy(new PerPixelCollisionStrategy())
{
//	Vector2f pos=player->getPosition();
  Sprites.reserve(Num);	
 Viewport::getInstance().setObjectToTrack(player);
	
	  Font_Color.r = Gamedata::getInstance().getXmlInt("PlayerName/red");
  Font_Color.g = Gamedata::getInstance().getXmlInt("PlayerName/green"); 
  Font_Color.b = Gamedata::getInstance().getXmlInt("PlayerName/blue");
  Font_Color.a = Gamedata::getInstance().getXmlInt("PlayerName/alpha");
	
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
	
	 world_back.draw();
  world_mid.draw();
  world_top.draw();
	player->draw();	
	
	for (auto& ptr : Sprites) {
	 ptr->draw();
		}
	healthBar->draw();
	powerBar->draw();
io.writeText(Name,0,400,Font_Color);	
	
	if(MaxEnimies>Sprites.size())
	{
	  std::stringstream stream;
	stream <<(float)((spawnEnimiesTime-lastTimeSinceSpawn)/1000);
	io.writeText1(stream.str(),Viewport::getInstance().getWidth()/2,30,Font_Color);
	}
	else
	{
			  std::stringstream stream;
	stream <<"Max Enemies";
	io.writeText1(stream.str(),Viewport::getInstance().getWidth()/2,30,Font_Color);	
	}
	
	
	
	viewport.draw();
  hud.draw(clock.getFps(),InfoTab,FlyMode);
  SDL_RenderPresent(renderer);
}



void Engine::update(Uint32 ticks) {
	lastTimeSinceSpawn=lastTimeSinceSpawn+ticks;
	player->update(ticks);
	player->killSprite();
	
	
	

	
	for (auto& ptr : Sprites) {
				
	 ptr->update(ticks);
}
	if(!Sprites.empty()){
Sprites[0]->collidedWith(player);
}
	checkForCollisions();
  world_back.update();
	 world_mid.update();
  world_top.update();
		healthBar->update(player->getHealth(),player->getLives());
	powerBar->update(player->getPowerLoadValue(),player->getLives());
  viewport.update();
	if((lastTimeSinceSpawn>spawnEnimiesTime)){
		ReSpawn();
	}

	  if( (player)->getGameStatus())
	  {
		  
	io.writeText1("GAME OVER",Viewport::getInstance().getWidth()/2,30,Font_Color);
	  SDL_Delay(10000);
	  }
}

void Engine::checkForCollisions() {
 
		auto it = Sprites.begin();
  while ( it != Sprites.end() ) {
	   Drawable* doa = *it;
	  if(!doa->getFalling()){
	   if ( strategy->execute(*doa, *player) ) {
	   
	doa->takeDamage(player->getattackDamage());
		if(player->getattackDamage()!=0)
		{
			doa->Falling();
		}
	   }
		  }
	  
	  if(doa->isDead())
		{
		doa->explode();
		}
    if ( doa->getExploding() ) {
      player->detach(doa);
      delete doa;
      it = Sprites.erase(it);
		
    }
    else ++it;
	  
  }
	}

void Engine::ReSpawn() {
	if(MaxEnimies>Sprites.size()){
		
 Sprites.emplace_back(new MultiSprite("S"+std::to_string(spriteCounter+1),
									  player->getPosition(),
									  player->getScaledWidth(),
									  player->getScaledHeight()));
    player->attach( Sprites[Sprites.size()-1] );
		lastTimeSinceSpawn=0;
	spriteCounter++;
	if(spriteCounter>=Num)
	{
	spriteCounter=0;
	}

	}
	}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
         // switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
		    if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
		  ///INFO TAB
		  else if (keystate[SDL_SCANCODE_F1] && !InfoTab) {
			   std::cout << "Information Tab Turned On" << std::endl;
      			 InfoTab=true;
      }
		 	  
		  else if (keystate[SDL_SCANCODE_F1] && InfoTab) {
			   std::cout << "Information Tab Turned Off" << std::endl;
      			 InfoTab=false;
      }   ///INFO TAB END
		
		  else if ((keystate[SDL_SCANCODE_W]) && !(static_cast<Player*>(player)->blockControl())) {
         static_cast<Player*>(player)->up();
      }  ///FLY MODE
	
		      
		  else if ((keystate[SDL_SCANCODE_C]) && !(FlyMode) && !(static_cast<Player*>(player)->blockControl()) ) {
			   std::cout << "Fly Mode On" << std::endl;
			        static_cast<Player*>(player)->SwitchToFly();
      			FlyMode=true;
      }
		 	  
		  else if (keystate[SDL_SCANCODE_C] && FlyMode  && !(static_cast<Player*>(player)->blockControl()) ) {
			   std::cout << "Fly Mode  Off" << std::endl;
			         static_cast<Player*>(player)->SwitchToFly();
      			FlyMode=false;
      }  ///FLY MODE END
		  else if (keystate[SDL_SCANCODE_E] && !(static_cast<Player*>(player)->blockControl()) ) {
			   std::cout << "Switch Triple Fire" << std::endl;
			         static_cast<Player*>(player)->setThripleFire();
      }  
		   else if ((keystate[SDL_SCANCODE_L]) & !(keystate[SDL_SCANCODE_I]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_Kick();
      }
		     else if ((keystate[SDL_SCANCODE_L]) & (keystate[SDL_SCANCODE_I]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_HKick();
      }
		  
		   else if ((keystate[SDL_SCANCODE_J]) & !(keystate[SDL_SCANCODE_I]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_Punch();
      }
		  
		  else if ((keystate[SDL_SCANCODE_J]) & (keystate[SDL_SCANCODE_I]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_HPunch();
      }
		  else if ((keystate[SDL_SCANCODE_SPACE]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_Shoot();
      }
		  else	if (keystate[SDL_SCANCODE_F] && !(static_cast<Player*>(player)->blockControl()) ) {
        static_cast<Player*>(player)->powerShoot();
      }	
		  
      }
    }

    // In this section of the event loop we allow key bounce:

  ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A] && !(static_cast<Player*>(player)->blockControl()) ) {
        static_cast<Player*>(player)->left();
      }
      if (keystate[SDL_SCANCODE_D] && !(static_cast<Player*>(player)->blockControl()) ) {
        static_cast<Player*>(player)->right();
      }
	
      if (keystate[SDL_SCANCODE_W] && !(static_cast<Player*>(player)->blockControl()) ) {
        static_cast<Player*>(player)->up();
      }
      if (keystate[SDL_SCANCODE_S] && !(static_cast<Player*>(player)->blockControl()) ) {
        static_cast<Player*>(player)->down();
	  }
	
		  if ((keystate[SDL_SCANCODE_B]) && !(static_cast<Player*>(player)->blockControl()) ) {
			         static_cast<Player*>(player)->Player_Defend();
      }  
      draw();
      update(ticks);
		//sound.Looping();
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
	  if( (player)->getGameStatus())
	  {
		  
		  done =(player)->getGameStatus();	
	  }
  }
	 return false;
}
