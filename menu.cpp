#include<sstream>
#include "menu.h"


Menu::~Menu() {
for (auto& ptr : Player) {
	delete ptr;
}

}

Menu::Menu(SDL_Renderer* rend) :  
  renderer(rend), 
  gdata(Gamedata::getInstance()), 
  hudFrame( {gdata.getXmlInt("menu/loc/x"),
             gdata.getXmlInt("menu/loc/y"),
             gdata.getXmlInt("menu/width"),
             gdata.getXmlInt("menu/height")}
  ),

  menuColor({static_cast<Uint8>(gdata.getXmlInt("menu/color/r")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/g")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/b")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/a"))}
  ),
  clock( Clock::getInstance() ),
  io( IoMod::getInstance() ),
  options(),
  optionLoc( { gdata.getXmlInt("menu/optionLoc/x"),
               gdata.getXmlInt("menu/optionLoc/y")}
           ),
  clicks( SpriteBox("clickOn")),
  currentClick(0),
  currentOption(0),
  spaces(gdata.getXmlInt("menu/spaces")),
  startClickX(optionLoc[0]-spaces),
  startClickY(optionLoc[1]+spaces),
  clickX(startClickX),
  clickY(startClickY),
NextScreen(false),
players(gdata.getXmlInt("menu/noOfPlayer")),
Player_count(0),
Player()
{
  int noOfOptions = gdata.getXmlInt("menu/noOfOptions");
  std::stringstream strm;
  for (int i = 0; i < noOfOptions; ++i) {
    strm.clear();
    strm.str("");
    strm << i;
    std::string option("menu/option"+strm.str());
    options.push_back(gdata.getXmlStr(option));
  }  
    
  int Y=clickY;
     Player.reserve(players);	
	for(int i=0;i<players;i++)
	{
 Player.push_back(new MenuMultiSprite("menu/Player"+std::to_string(i),clickX+clicks.getScaledWidth(),Y));
    Y+=Player[i]->getScaledHeight();
	}
 
}

	void Menu::setPlayScreen(const bool N) {
  
  NextScreen=N;
      clickY=Player[Player_count]->getY()+Player[Player_count]->getScaledHeight()/2;
  clickX=Player[Player_count]->getX()-clicks.getScaledWidth();
    
  }


void Menu::incrIcon() { 
  
   if(NextScreen)
  { 
     Player_count++;
  if(Player_count>=players)Player_count=0;
  clickY=Player[Player_count]->getY()+Player[Player_count]->getScaledHeight()/2;
  clickX=Player[Player_count]->getX()-clicks.getScaledWidth();

   }else
  {
  clickY += spaces; 
  if ( clickY > static_cast<int>(options.size())*spaces+optionLoc[1]) {
    clickY = startClickY;
    currentOption = 0;
  }
  else ++currentOption;   


  }
}

void Menu::decrIcon() { 

  
    if(NextScreen)
  {
    Player_count--;
  if(Player_count<0)Player_count=players-1;
  clickY=Player[Player_count]->getY()+Player[Player_count]->getScaledHeight()/2;
  clickX=Player[Player_count]->getX()-clicks.getScaledWidth();
      
      
      
    }else
  {
   clickY -= spaces; 
  if ( clickY < spaces+optionLoc[1]) {
    clickY = startClickY+2*spaces;
    currentOption = options.size()-1;
  }
  else --currentOption;

  }
}


int Menu::getInputEventLoop() const {
  SDL_Event event;
  bool done = false;
  std::string inNumber = " ";
  std::string msg = "Press return/esc when finished."; 
  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
     
      SDL_RenderPresent(renderer);
    }
  }
  return atoi( inNumber.c_str() );
}

int Menu::getNumStars() const {
  int numStars = getInputEventLoop();
  return numStars;
}

void Menu::draw() const {
  if(NextScreen)
  { 
	  io.writeText1("Select Player", 400, 150,menuColor);
      for (auto& ptr : Player) {
       ptr->draw();     
       io.writeText(ptr->getname(), ptr->getX()+ptr->getScaledWidth(),  ptr->getY()+(ptr->getScaledHeight()/2),menuColor);
        
}  
      clicks.getImage()->draw(0, 0, clickX, clickY);
  }else
  {
     int space = spaces;

  for ( const std::string& option : options ) {
    io.writeText(option, optionLoc[0], optionLoc[1]+space,menuColor);
    space += spaces;
  }
  // We have to draw the clickOn & clickOff relative to the screen,
  // and we don't want to offset by the location of the viewprot:
  clicks.getImage()->draw(0, 0, clickX, clickY);
  }

  
  
}

void Menu::update(Uint32 ticks) {
	
  
   for (auto& ptr : Player) {
       ptr->update(ticks);
      
}
  
  
}


