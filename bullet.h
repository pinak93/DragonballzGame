#include <iostream>
#include "bulletsprite.h"
#include "gameData.h"


class Bullet : public BulletSprite {
public:
  explicit Bullet(const string& name,const string& mName) :
    BulletSprite(name), 
	makerName(mName),
	dead(false),
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
    damage(Gamedata::getInstance().getXmlInt(name+"/damage")),
	Type(name),
	tooFar(false) 
  { 
	
	}

  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
	int getDamage() const { return damage; }
	std::string getMakerName() const { return makerName; }
 void setMakerName(const string N)  {  makerName=N; }
  bool isDead() const { return dead;}
	void setDead(const bool N)  {dead=N;}
	void reset() {
    tooFar = false;
    distance = 0;
  }
	void setType(const std::string& s) {Type=s;}
 std::string getType() const{ return Type; }

  private:
	std::string makerName;
bool dead;
  float distance;
  float maxDistance;
	int damage;	
	std::string Type;
  bool tooFar;
};
