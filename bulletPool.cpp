#include <iostream>
#include <sstream>
#include <cmath>
#include "ioMod.h"
#include "gameData.h"
#include "bulletPool.h"

CollisionStrategy* getStrategy(const string& name) {
  std::string sName = Gamedata::getInstance().getXmlStr(name+"/strategy");
  if ( sName == "midpoint" ) return new MidPointCollisionStrategy;
  if ( sName == "rectangular" ) return new RectangularCollisionStrategy;
  if ( sName == "perpixel" ) return new PerPixelCollisionStrategy;
  throw std::string("No strategy in getStrategy");
}

BulletPool& BulletPool::getInstance() {
  static BulletPool BulletPool; 
  return BulletPool;
}

BulletPool::~BulletPool() {
  delete strategy;
}

BulletPool::BulletPool(const std::string& fn,const std::string& fn1,const std::string& fn2) :
  Haikai(fn1),
KiBlast(fn),
MegBlast(fn2),
  strategy( getStrategy(fn) ),
  frameInterval(Gamedata::getInstance().getXmlInt(fn+"/interval")),
  timeSinceLastFrame( 0 ),
  bulletList(),
  freeList(),
Exploding()
{ }

bool BulletPool::collidedWith( Drawable* obj,std::string Maker) const {
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
   if(ptr->getMakerName()==Maker) {
	  if(obj->isSpritExploding())
	  {}
	  else
	  {
    if ( strategy->execute(*ptr, *obj) ) {
     if((!(obj->shouldDefend(ptr->getX()))) || !(obj->isDefending())   ) {        //check if sprite is defending
		obj->takeDamage(ptr->getDamage());
   
    }
      if(ptr->getType()!=MegBlast){
       freeList.push_back(*ptr);
      }
     ptr = bulletList.erase(ptr);
      return true;   
    }}
  }
    ++ptr;
  }
  return false;
}

void BulletPool::shoot(const Vector2f& position, const Vector2f& velocity,std::string makerName) {
	if (timeSinceLastFrame > frameInterval) {
    // If no bullets in pool, make one:
    if ( freeList.empty() ) {
  
		Bullet b(KiBlast,makerName);
      b.setPosition( position );
      b.setVelocity( velocity );
      bulletList.push_back( b );
	  }
    else {
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setMakerName(makerName);
      b.setVelocity(velocity);
      b.setPosition(position);
      bulletList.push_back( b );
    }
		timeSinceLastFrame = 0;
	}
}

void BulletPool::Megshoot(const Vector2f& position, const Vector2f& velocity,std::string makerName) {
	if (timeSinceLastFrame > frameInterval) {
    // If no bullets in pool, make one:
		Bullet b(MegBlast,makerName);
      b.setPosition( position );
      b.setVelocity( velocity );
      bulletList.push_back( b );
	  
		timeSinceLastFrame = 0;
	}
}



void BulletPool::draw() const { 

  for ( Bullet bullet : bulletList ) {
    bullet.draw();
  }
  if(!Exploding.empty())
  {
   for ( ExplodingProjectile e : Exploding ) {
    e.draw();
  } 
  }
}

void BulletPool::update(Uint32 ticks) { 
	timeSinceLastFrame += ticks;
  
    std::list<ExplodingProjectile>::iterator E1 = Exploding.begin();
 while (E1 != Exploding.end()) {
    E1->update(ticks);
   
   if ((E1->getExploding()) ) {  // Check to see if we should free a Bullet
      E1 = Exploding.erase(E1);
    } else 
    {
      ++E1;
    }
   
 }
  
  std::list<Bullet>::iterator ptr = bulletList.begin();
 while (ptr != bulletList.end()) {
    ptr->update(ticks);
   
    
    if ((ptr->goneTooFar()) ) {  // Check to see if we should free a Bullet
 if(ptr->getType()!=MegBlast){
      freeList.push_back(*ptr);
	}
		ptr = bulletList.erase(ptr);
    } else 
    {
      ++ptr;
    }
    
       
  }
 
 
  
  
  
  
    if(!bulletList.empty()){
    std::list<Bullet>::iterator ptr1 = bulletList.begin();
   while (ptr1 !=bulletList.end())
   {
     std::list<Bullet>::iterator ptr2=ptr++;
     while(ptr2!=bulletList.end())
     {
       if(ptr1->getMakerName()!=ptr2->getMakerName())
       if(strategy->execute(*ptr1, *ptr2))
       {
      // ptr2->explode();
          ptr1->setDead(true);
         ptr2->setDead(true);
         ExplodingProjectile E("explosion",ptr1->getX(),ptr1->getY());
         Exploding.push_back(E);
         std::cout<<"DEAD"<<std::endl;
       }
      ++ptr2;
     }
     
      ++ptr1;
   }
     
    }
 
   
 ptr = bulletList.begin();
 while (ptr != bulletList.end()) {
    ptr->update(ticks);
   
    if (ptr->isDead() ) {  // Check to see if we should free a Bullet
      std::cout<<"deletedone"<<std::endl;
     ptr->setDead(false);
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
    } else 
    {
      ++ptr;
    }
    
       
  }
 
  
  
  
  
  
  
  
  
}
