// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"
#include "menuEngine.h"

int main(int, char*[]) {
bool keepPlaying = false;
	 bool setMenu = true;
	std::string PlayerName;
	//bool MainLoop=false;

   try {
	   
	  while ( setMenu ) {
       MenuEngine* engine = new MenuEngine;
       setMenu = engine->play();
		  PlayerName=engine->getPlayerName();
		  keepPlaying=engine->getGameReady();
		  //MainLoop=engine->getExit();
       delete engine;
     } 
	
     while ( keepPlaying ) {
       Engine* engine = new Engine(PlayerName);
       keepPlaying = engine->play();
       delete engine;
     }
		   
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
