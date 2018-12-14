#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "multisprite.h"
#include <list>
#include "bulletPool.h"
#include "player_sound.h"


class Player : public Drawable {
public:
  Player(const std::string&);
	
  Player(const Player&);
  ~Player();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return Main[currentFrame]; 
  }
	
  int getScaledWidth()  const { 
    return getScale()*Main[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*Main[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return Main[currentFrame]->getSurface();
  }

  
	void SwitchToFly();
	void switch_walk();
	void SetImage_WalkRight();
	void SetImage_WalkLeft();
	void SetImage_standing();
	//Movement
	void up();
  	void right();
  	void left();
	void down();
	void stop();
	//combact
	void Player_Kick();
	void Player_HKick();
	void Player_Punch();
  void Player_HPunch();
	void Player_Shoot();
		void Player_Defend();
	bool sidechecker();
  	void Player_Die();
  	void Player_Revive();
	void setThripleFire() {FireMode=!FireMode;};
	bool getThripleFire() const {return FireMode;};
	//Obsereve
  std::list<Drawable*> observers;
  virtual void attach( Drawable* o ) { observers.push_back(o); } 
  virtual void detach( Drawable* o);	
  	virtual void setPlayerPos(const Vector2f&) {}
 virtual  bool collidedWith( Drawable*) const;
 virtual void killSprite();
  virtual void takeDamage(const int n)  { if (Health>=0)Health=Health-n;}
	void powerShootLoad(int i){ if(LoadPower<=SHealth){LoadPower+=i;}}
  void powerShoot();
void resetPower(){LoadPower=0; }
virtual bool isDefending() const {return Defending;}
 virtual float getPowerLoadValue()const {return LoadPower;}
 virtual int getLives() const { return Lives;}
   float LoadPower;
	virtual float getHealth() const {return Health;}
	 virtual bool isSpritExploding(){ return false;}
  virtual bool getGameStatus() const {return GameOver;}
  virtual  bool blockControl() const {return BlockControls;}
   virtual bool shouldDefend(const int) {return true;}
   virtual int getattackDamage() {
     int damage=currentAttack;
     return damage;}
protected:
  std::vector<Image *> Main;
  
  std::vector<Image *> Walk_R;
  std::vector<Image *> Walk_L;
  std::vector<Image *> Standing;
  
  std::vector<Image *> Fly_R;
  std::vector<Image *> Fly_L;
  std::vector<Image *> Fly_S;	
  
  std::vector<Image *> Kick_R;
	std::vector<Image *> HKick_R;
	std::vector<Image *> Punch_R;
	std::vector<Image *> HPunch_R;
  std::vector<Image *> Shoot_R;
  
  std::vector<Image *> Kick_L;
	std::vector<Image *> HKick_L;
	std::vector<Image *> Punch_L;
	std::vector<Image *> HPunch_L;
  std::vector<Image *> Shoot_L;
	std::vector<Image *> Defend_L;
  std::vector<Image *> Defend_R;
	
  
	std::vector<Image *> Die_L;
  std::vector<Image *> Die_R;

	std::vector<Image *> Revive_L;
  std::vector<Image *> Revive_R;

  std::vector<Image *> Mega_L;
  std::vector<Image *> Mega_R;
	
  
  std::string Name;
  enum MODE {LEFT, RIGHT};
  MODE currentLookSide;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  unsigned ylocation;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
	float last_velocity;
 Vector2f initialVelocity;
	  enum attackType{NOTHING=0,KICK=2,HKICK=4,PUNCH=2,HPUNCH=4};
  attackType currentAttack;
	bool Fly,OneLoop,powerFire,FireMode,Defending,Dying,Revive,GameOver,BlockControls;
	std::string bulletName;
  BulletPool& bullets;
  float minSpeed;
  int FireCounter,Lives;
	float Health,SHealth;
	SDLSoundPlayer* sound;
  void advanceFrame(Uint32 ticks);
  Player& operator=(const Player&);
};
#endif
