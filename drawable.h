#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "image.h"

class Player;

// Drawable is an Abstract Base Class (ABC) that specifies the methods
// that derived classes may or must have.
class Drawable {
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel): 
    name(n), position(pos), velocity(vel), scale(1.0) {}

  Drawable(const Drawable& s) : 
    name(s.name), position(s.position), velocity(s.velocity), scale(s.scale)
    { }

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float getScale() const  { return scale; }
  void  setScale(float s) { scale = s; }
  virtual int getScaledWidth() const = 0;
  virtual int getScaledHeight() const = 0;
  virtual const SDL_Surface* getSurface() const = 0;
  
  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }

  virtual const Image* getImage() const = 0;

  float getX() const  { return position[0]; }
  void  setX(float x) { position[0] = x;    }

  float getY() const  { return position[1]; }
  void  setY(float y) { position[1] = y;    }

  const Vector2f& getVelocity() const    { return velocity; }
  void  setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const    { return position; }
  void  setPosition(const Vector2f& pos) { position = pos;  }
	virtual void setPlayerPos(const Vector2f&) {throw std::string("I don't have a player");}
	virtual bool isDefending() const {throw std::string("I can't defend");}
virtual  bool blockControl() const {throw std::string("I can't defend");}
 virtual int getLives() const { throw std::string("I don't have lives");}
  float getVelocityX() const   { return velocity[0]; }
  void  setVelocityX(float vx) { velocity[0] = vx;   }
  float getVelocityY() const   { return velocity[1]; }
  void  setVelocityY(float vy) { velocity[1] = vy;   }
	virtual void explode() { throw std::string("I don't explode"); }
 virtual bool getExploding() const {throw std::string("I don't explode");}
    virtual bool isSpritExploding(){ throw std::string("I am not a sprite");}
	 virtual void completedDefending(){ throw std::string("I don't defend");}
   virtual bool shouldDefend(const int) {throw std::string("I don't defend");}
	virtual bool isDead() const {throw std::string("I don't Die");}
  virtual void takeDamage(const int)  {throw std::string("I don't take Damage");}
	virtual  bool collidedWith( Drawable*) const {throw std::string("I don't collied with bullet");}
  
	virtual  bool collidedWith( Player*) const {throw std::string("I don't collied with player");}
	
	virtual void attach( Drawable*) {throw std::string("I don't attach"); } 
  virtual void detach( Drawable* ){throw std::string("I don't detach");}
	virtual float getPowerLoadValue()const {throw std::string("I don't have power");}

	virtual  void killSprite() {throw std::string("I don't have power");}
virtual  void Falling()  {throw std::string("I don't have Fall");}
	virtual float getHealth() const {throw std::string("I don't have health");}
	virtual int getattackDamage() {
     throw std::string("I don't have attack");}
	    virtual  bool getFalling() const {throw std::string("I don't have Fall");}
	  virtual bool getGameStatus() const {throw std::string("I don't can't set this ");}
private:
  
  std::string name;
  Vector2f position;
  Vector2f velocity;
  float scale;
};
#endif
