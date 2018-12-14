#ifndef BULLETPOOL__H
#define BULLETPOOL__H
#include <list>
#include "bullet.h"
#include "collisionStrategy.h"
#include "explodingprojectile.h"

class BulletPool {
public:
	static BulletPool& getInstance();

  ~BulletPool();
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel,std::string Mname);
  void Megshoot(const Vector2f& pos, const Vector2f& vel,std::string Mname);

  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
  bool shooting() const { return bulletList.empty(); }
  bool collidedWith(Drawable* obj,std::string Maker) const;
	bool TimeChecked() const{return timeSinceLastFrame > frameInterval;};


  std::string Haikai,KiBlast,MegBlast;
  CollisionStrategy* strategy;
  float frameInterval;
  float timeSinceLastFrame;
  mutable std::list<Bullet> bulletList; // BulletPool is a list of Bullet
  mutable std::list<Bullet> freeList;   // when a Bullet is out of range
  mutable std::list<ExplodingProjectile> Exploding;   // when a Bullet is out of range
private:
  friend class Player;
  friend class MultiSprite;
  BulletPool(const std::string& fn = "raybeam",const std::string& fn1 = "KiBlast",const std::string& fn2 = "MegBlast");
  BulletPool(const BulletPool&);	
  BulletPool& operator=(const BulletPool&);   // (Item 6)
};
#endif