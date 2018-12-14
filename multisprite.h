#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "bulletPool.h"
#include "player.h"
#include "npc_sound.h"

class ExplodingSprite;

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&, const Vector2f position, const int width, const int height);
	
  MultiSprite(const MultiSprite&);
  ~MultiSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return Main_Walk[currentFrame]; 
  }
	void AI(float,float,float);
  void Flyoff(float,float);
  void Fire();
	 void HealthBar(int,int) const;
  std::string getName() const {return Name;}
  std::string getTag() const {return TagName;}
  int getScaledWidth()  const { 
    return getScale()*Main_Walk[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*Main_Walk[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return Main_Walk[currentFrame]->getSurface();
  }

	virtual void setPlayerPos(const Vector2f& p) { Playerposition = p; }
	virtual void explode();
  bool getStatus();
  virtual bool isSpritExploding(){ return explosion;}
bool sidechecker();
	void Shoot(float dist);
	virtual float getHealth() const {return Health;}
	virtual bool isDead() const {return Health<=0;}
  virtual void takeDamage(const int n)  {Health=Health-n;}
		virtual bool isDefending() const {return Defending;}
  virtual bool shouldDefend(const int);
  virtual void completedDefending();
  	 virtual bool collidedWith( Drawable*) const;
virtual bool getExploding() const {return Exploding;}
  virtual  void Falling();
    virtual  bool getFalling() const {return Fall;}
  
protected:
	  SDL_Renderer* renderer;
   std::vector<Image *> Main_Walk;
  std::vector<Image *> Walk_R;
  std::vector<Image *> Walk_L;
  std::vector<Image *> fly_R;
  std::vector<Image *> fly_L;
  std::vector<Image *> Defend_L;
  std::vector<Image *> Defend_R;
  std::vector<Image *> shoot_L;
  std::vector<Image *> shoot_R;
  std::vector<Image *> Fall_L;
  std::vector<Image *> Fall_R;
  float Health,SHealth,LastV;	
  std::string Name,TagName;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame,timetrail;
  float Keepdistance;
  int worldWidth;
  int worldHeight;
  bool FlyMode,OneLoop;
  int FlyVelocity;
  int WalkVelocity;
  int StartY,FireTime;
  Vector2f Playerposition;
  int PlayerW, PlayerH;
  ExplodingSprite* explosion;
	bool Exploding,fire;
	std::string bulletName;
  BulletPool& bullets;
  float minSpeed;
  bool Defending,Fall;
	SDLSoundNpc* sound;
  void advanceFrame(Uint32 ticks);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
