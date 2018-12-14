#include <string>
#include <iostream>
#include <ctime>
#include "player_sound.h"
#include "gameData.h"
#include "imageFactory.h"
using std::string;




SDLSoundPlayer::~SDLSoundPlayer() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
 for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  Mix_CloseAudio();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}

SDLSoundPlayer::SDLSoundPlayer(std::string Player) : 
  volume(SDL_MIX_MAXVOLUME), 
  currentSound(-1), 
  audioRate(22050), 
  audioChannels(1), 
  audioBuffers(4096),
  sounds(),
  channels() 
{
 if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }

  sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/StartTrack").c_str()) ); //0
     sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Kick").c_str()) );   //1
     sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Punch").c_str()));   //2 
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Time").c_str()) );  //3 
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Dead").c_str()) );  //4
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Fall").c_str()) );  //5
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Dying").c_str()) );  //6
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Mega").c_str()) );   //7
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/MBlast").c_str() ));  //8
         sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr(Player+"/Sound/Kiblast").c_str()) );   //9


  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  std::cout << "Music and Sound is loaded" << std::endl;
}
SDLSoundPlayer::SDLSoundPlayer(const SDLSoundPlayer& s) :
 volume(s.volume), 
  currentSound(s.currentSound), 
  audioRate(s.audioRate), 
  audioChannels(s.audioChannels), 
  audioBuffers(s.audioBuffers),
  sounds(s.audioBuffers),
  channels(s.channels)
{}



void SDLSoundPlayer::play( int index) {
 if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = 
     Mix_PlayChannel(-1, sounds[index], 0);

}




void SDLSoundPlayer::operator[](int index) {
  if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = 
     Mix_PlayChannel(-1, sounds[index], 0);

}
