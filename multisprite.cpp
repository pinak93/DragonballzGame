#include "multisprite.h"
#include "gameData.h"
#include "explodingSprite.h"
#include "renderContext.h"
#include "viewport.h"
#include "player.h"

MultiSprite::~MultiSprite( ) { if (explosion) {delete explosion;} 
							 delete sound;
							 }
void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	timetrail += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
	
}

MultiSprite::MultiSprite( const std::string& name,const Vector2f position, const int width, const int height) :
  Drawable(Gamedata::getInstance().getXmlStr(name+"/Name"), 
           Vector2f(Gamedata::getInstance().getXmlInt("world/width"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
renderer(RenderContext::getInstance().getRenderer()),
Main_Walk( ImageFactory::getInstance().getImagesL(name+"/Fly") ),
  Walk_R( ImageFactory::getInstance().getImagesR(name+"/Walk") ),
  Walk_L( ImageFactory::getInstance().getImagesL(name+"/Walk") ),
  fly_R( ImageFactory::getInstance().getImagesR(name+"/Fly") ),
  fly_L( ImageFactory::getInstance().getImagesL(name+"/Fly") ),
Defend_L(ImageFactory::getInstance().getImagesL(name+"/Defend")),
Defend_R(ImageFactory::getInstance().getImagesR(name+"/Defend")),
shoot_L(ImageFactory::getInstance().getImagesL(name+"/Shoot")),
shoot_R(ImageFactory::getInstance().getImagesR(name+"/Shoot")),
Fall_L(ImageFactory::getInstance().getImagesL(name+"/Fall")),
Fall_R(ImageFactory::getInstance().getImagesR(name+"/Fall")),
Health(Gamedata::getInstance().getXmlInt(name+"/Health")),
SHealth(Gamedata::getInstance().getXmlInt(name+"/Health")),
LastV(0),
  Name(Gamedata::getInstance().getXmlStr(name+"/Name")),
TagName(name),
  currentFrame(0),
	numberOfFrames(Gamedata::getInstance().getXmlInt(name+"/frames")),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
timetrail(0),
Keepdistance(Gamedata::getInstance().getXmlInt(name+"/Distance")),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
FlyMode(false),
OneLoop(false),
FlyVelocity(Gamedata::getInstance().getXmlInt(name+"/FlyVelocity")),
WalkVelocity(Gamedata::getInstance().getXmlInt(name+"/WalkVelocity")),
StartY(Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
FireTime(Gamedata::getInstance().getXmlInt(name+"/FireInterval")),
Playerposition(position),
PlayerW(width), 
PlayerH(height),
explosion(nullptr),
Exploding(false),
fire(false),
 bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
bullets( BulletPool::getInstance()  ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
Defending(false),
Fall(false),
sound(new SDLSoundNpc(name) )
{
sound->play(0);

}

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
renderer(s.renderer),
  Main_Walk(s.Main_Walk),
  Walk_R( s.Walk_R),
  Walk_L( s.Walk_L ),
fly_R(s.fly_R),
fly_L(s.fly_L),
Defend_L(s.Defend_L),
Defend_R(s.Defend_R),
	shoot_L(s.shoot_L),
	shoot_R(s.shoot_R),
Fall_L(s.Fall_L),
Fall_R(s.Fall_R),
Health(s.Health),
SHealth(s.SHealth),
LastV(s.LastV),
  Name(s.Name),
TagName(s.TagName),
  currentFrame(s.currentFrame),
numberOfFrames(s.numberOfFrames),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
timetrail(s.timetrail),
Keepdistance(s.Keepdistance),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
FlyMode(s.FlyMode),
OneLoop(s.OneLoop),
FlyVelocity(s.FlyVelocity),
WalkVelocity(s.WalkVelocity),
StartY(s.StartY),
FireTime(s.FireTime),
Playerposition(s.Playerposition),
PlayerW(s.PlayerW), 
PlayerH(s.PlayerH),
explosion(s.explosion),
Exploding(s.Exploding),
fire(s.fire),
  bulletName( s.bulletName ),
bullets( s.bullets ),
  minSpeed( s.minSpeed ),
Defending(s.Defending),
Fall(s.Fall),
sound(s.sound)
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
   Drawable::operator=(s);
	renderer=(s.renderer);
  Main_Walk=(s.Main_Walk);
  Walk_R=( s.Walk_R);
  Walk_L=( s.Walk_L );
	fly_R=(s.fly_R);
fly_L=(s.fly_L);
	Defend_L=(s.Defend_L);
	Defend_R=(s.Defend_R);
	shoot_L=(s.shoot_L);
	shoot_R=(s.shoot_R);
	Fall_L=(s.Fall_L);
Fall_R=(s.Fall_R);
	Health=(s.Health);
	SHealth=(s.SHealth);
	LastV=(s.LastV);
  Name = (s.Name);
	TagName=(s.TagName);
  currentFrame = (s.currentFrame);
	numberOfFrames=(s.numberOfFrames);
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
	timetrail = (s.timetrail);
	Keepdistance = (s.Keepdistance);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
	FlyMode = (s.FlyMode);
	OneLoop=(s.OneLoop);
	FlyVelocity = (s.FlyVelocity);
	WalkVelocity = (s.WalkVelocity);
	StartY=(s.StartY);
	FireTime=(s.FireTime);
	Playerposition = (s.Playerposition);
	PlayerW=(s.PlayerW);
PlayerH=(s.PlayerH);
	explosion=(s.explosion);
	Exploding=(s.Exploding);
	fire=(s.fire);
  bulletName=( s.bulletName );
  minSpeed=( s.minSpeed );
	Defending=(s.Defending);
	Fall=(s.Fall);
  return *this;
}


 bool MultiSprite::sidechecker()
 {
if(getVelocityX()==0){
		 if(LastV>0) return true;
	 else return false;	
}
	else{
	 if(getVelocityX()>0) return true;
	 else return false;	
	}
 
 
 }


void MultiSprite::draw() const { 
	
	  if ( explosion ) explosion->draw();
	  else {Main_Walk[currentFrame]->draw(getX(), getY(), getScale());
		   HealthBar(getX()- Viewport::getInstance().getX(), getY()-Viewport::getInstance().getY());
		   }
}
float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}


void MultiSprite::Flyoff(float x,float x1) {
	if(x1>x)
	{
		setVelocityX( -fabs( FlyVelocity ) );
		setVelocityY( -fabs( FlyVelocity ) );
		 Main_Walk=fly_L;
		if ( getY() < 0) {
    setVelocityY( fabs( FlyVelocity ) );     }
		
		 if ( getX() < 0) {
	  setVelocityX( fabs( FlyVelocity ) );
	   Main_Walk=Walk_R;                    }
	}
	else
	{
		setVelocityX( fabs( FlyVelocity ) );
		setVelocityY( -fabs( FlyVelocity ) );
		 Main_Walk=fly_R;
				if ( getY() < 0) {
			setVelocityY( fabs( FlyVelocity ) );
		  }
		
		if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( FlyVelocity ) );
     Main_Walk=Walk_L; }
	}
	
}
void MultiSprite::explode() {
  if ( !explosion ) {
	  sound->play(3);
    Sprite 
    sprite(getTag(), getPosition(), getVelocity(), Main_Walk[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}



void MultiSprite::HealthBar(int x,int y) const {
   // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
	 SDL_SetRenderDrawColor( 
    renderer, 255,255,255,100 );
	 SDL_Rect barRect={x,y,(int)SHealth,15};
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // Set the health bar background color:
 
  // Draw the  background
  SDL_RenderFillRect( renderer, &barRect );

  SDL_SetRenderDrawColor( 
    renderer,  255,0,0,255 );
  SDL_Rect healthRect = {x, y, (int)Health, 15};
  SDL_RenderFillRect( renderer, &healthRect );

  // Set the  color for the health bar outline:
  SDL_SetRenderDrawColor( 
    renderer, 0,0,0,255);
  SDL_RenderDrawRect( renderer, &barRect );
}

void MultiSprite::update(Uint32 ticks) { 

	 if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
		Exploding=true;
    }
    return;
  }
	else
	{
		HealthBar(getX()- Viewport::getInstance().getX(), getY()-Viewport::getInstance().getY());
	}
	
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

	
  if ( getY() < 0) {
    setVelocityY( fabs( FlyVelocity ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( FlyVelocity ) );
  }
	
   if ( (getX() < 0) & (getVelocityY()==0)) {
	  setVelocityX( fabs( WalkVelocity ) );
	   Main_Walk=Walk_R;
}
  if ( (getX() > worldWidth-getScaledWidth()) & (getVelocityY()==0)) {
    setVelocityX( -fabs( WalkVelocity ) );
     Main_Walk=Walk_L; 
  } // WALK ONLY IF NOT FLYING 
	
	
	
	  if ( (getX() < 0) & (getVelocityY()!=0)) {
	  setVelocityX( fabs( WalkVelocity ) );
	   Main_Walk=fly_R;
}
  if ( (getX() > worldWidth-getScaledWidth()) & (getVelocityY()!=0)) {
    setVelocityX( -fabs( WalkVelocity ) );
     Main_Walk=fly_L; 
  }// IF FLYING DON"T WALK 
	
	
	if ( (getY()>StartY)& (getVelocityY()!=0)) {
    setVelocityY(0);
	if(getVelocityX()>0)
	{
		Main_Walk=Walk_R;
	}
	else
	{
		Main_Walk=Walk_L;
	}
  }// WALK ONLY IF NOT FLYING 
	
			
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= Playerposition[0]+PlayerW/2;
  float ey= Playerposition[1]+PlayerH/2;
  float dist = ::distance( x, y, ex, ey );
	
	
if((OneLoop) && (numberOfFrames-1==currentFrame))
{
	completedDefending();
	AI(dist,x,ex);
OneLoop=false;
}
	
	if((OneLoop) && (fire))
{
	Fire();
}
	
	
	Shoot(dist);

}
bool MultiSprite::collidedWith(Drawable* obj) const {
  return bullets.collidedWith( obj ,"Enimies");
}
void MultiSprite::Shoot(float dist){
	
	  float y= getY()+getImage()->getHeight()/2;
		float LowerLimit =getY();
	float HigherLimit =(getY()+(getImage()->getHeight()));
	float playerhigerlimit=Playerposition[1]+PlayerH;
	if(!fire){
	if(timetrail>=FireTime){
	if((dist < (Keepdistance*3)) && (dist >(Keepdistance))) 
  {
		
	if((sidechecker()) && (Playerposition[0]>getX())) //This checks if the side they are looking and the player is on the sameside
	{
		
		if((HigherLimit>Playerposition[1]) || (LowerLimit<Playerposition[1]))
		{



			if(y>Playerposition[1] || y<playerhigerlimit)
			{
				fire=true;OneLoop=true;
			 		LastV=getVelocityX();setVelocityX(0);
	if(sidechecker()) {Main_Walk=shoot_R;}
	  else {Main_Walk=shoot_L;}
			}
		}
		
	}
		
	 if(!(sidechecker()) && (Playerposition[0]<getX()))//This checks if the side they are looking and the player is on the sameside
	{
		if((HigherLimit>Playerposition[1]) || (LowerLimit<Playerposition[1]))
		{
		if(y>Playerposition[1] || y<playerhigerlimit)
			{
				fire=true;OneLoop=true;
			 				LastV=getVelocityX();setVelocityX(0);
	if(sidechecker()) {Main_Walk=shoot_R;}
	  else {Main_Walk=shoot_L;}
			}
		}	 
	}
	}}}//end Shoot AI
	
}

void MultiSprite::AI(float dist, float x, float ex){

  if( dist < Keepdistance) 
	  {   
	  Flyoff(x,ex);  
  }		
	

}	//END AI
	

void MultiSprite::Falling() 
{
LastV=getVelocityX();
	if(LastV>0)setVelocityX(-fabs(LastV*0.50));
		else setVelocityX(fabs(LastV*0.50));
	Fall=true;
	OneLoop=true;
	currentFrame=0;
	if(sidechecker()) {Main_Walk=Fall_L;}
	  else {Main_Walk=Fall_R;}
	sound->play(1);
}

void MultiSprite::completedDefending()
{
if(Defending || fire){
setVelocityX(WalkVelocity);
	if(getVelocityX()>0)
	{
		Main_Walk=Walk_R;
	}
	else
	{
		Main_Walk=Walk_L;
	}
	
		Defending=false; 
	fire=false;
}
	if(Fall)
{
		if(LastV>0)setVelocityX(-fabs(WalkVelocity));
		else setVelocityX(fabs(WalkVelocity));
		
		LastV=0;
		if(getVelocityX()>0)
	{
		Main_Walk=Walk_R;
	}
	else
	{
		Main_Walk=Walk_L;
	}
			Fall=false;
}
	
	

	
}

void MultiSprite::Fire() {
	
		 float x1 = getX()+getImage()->getWidth()/2;
  float x2 = getX()-getImage()->getWidth()/2;
  
		float y1 = getY()+(getImage()->getHeight()/2)/2;
  // I'm not adding minSpeed to y velocity:
  bullets.shoot( Vector2f(sidechecker()?x1:x2, y1), 
    Vector2f(sidechecker()?(minSpeed*2):-fabs(minSpeed*2), 0),"Enimies");
	timetrail=0;
	sound->play(2);
}

bool MultiSprite::shouldDefend(const int LocX)
{
			int randNum = rand()%(2-0 + 1) + 0;
		
		switch(randNum) {
			case 1 : 
			if(LocX>getX())
		  Main_Walk=Defend_R;
			if(LocX<getX())
		  Main_Walk=Defend_L;
				Defending=true;    
				  OneLoop=true;
				if(LastV==0)
				{
				LastV=getVelocityX();
				}
			setVelocity(Vector2f(0, 0) );
					return true	;
				
				 break;
			case 2 : return false;
				 break;

		
		}
	return false;
		
}


