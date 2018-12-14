#include "player.h"
#include "gameData.h"
#include "imageFactory.h"

Player::~Player( ) { delete sound;}
void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;

		timeSinceLastFrame = 0;
	}
}

Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
observers(),
LoadPower(0),
Main( ImageFactory::getInstance().getImages(name+"/Standing") ),
  Walk_R( ImageFactory::getInstance().getImagesR(name+"/Walk") ),
  Walk_L( ImageFactory::getInstance().getImagesL(name+"/Walk") ),
Standing( ImageFactory::getInstance().getImages(name+"/Standing") ),
Fly_R(ImageFactory::getInstance().getImagesR(name+"/Fly")),
Fly_L(ImageFactory::getInstance().getImagesL(name+"/Fly")),
Fly_S(ImageFactory::getInstance().getImages(name+"/Fly_S")),
Kick_R(ImageFactory::getInstance().getImagesR(name+"/Kick")),
HKick_R(ImageFactory::getInstance().getImagesR(name+"/HKick")),
Punch_R	(ImageFactory::getInstance().getImagesR(name+"/Punch")),
HPunch_R(ImageFactory::getInstance().getImagesR(name+"/HPunch")),
Shoot_R(ImageFactory::getInstance().getImagesR(name+"/Shoot")),

 Kick_L(ImageFactory::getInstance().getImagesL(name+"/Kick")),
HKick_L(ImageFactory::getInstance().getImagesL(name+"/HKick")),
Punch_L(ImageFactory::getInstance().getImagesL(name+"/Punch")),
HPunch_L(ImageFactory::getInstance().getImagesL(name+"/HPunch")),
Shoot_L(ImageFactory::getInstance().getImagesL(name+"/Shoot")),
Defend_L(ImageFactory::getInstance().getImagesL(name+"/Defend")),
Defend_R(ImageFactory::getInstance().getImagesR(name+"/Defend")),
Die_L(ImageFactory::getInstance().getImagesL(name+"/Die")),
Die_R(ImageFactory::getInstance().getImagesR(name+"/Die")),
Revive_L(ImageFactory::getInstance().getImagesL(name+"/Revive")),
Revive_R(ImageFactory::getInstance().getImagesR(name+"/Revive")),
Mega_L(ImageFactory::getInstance().getImagesL(name+"/Mega")),
Mega_R(ImageFactory::getInstance().getImagesR(name+"/Mega")),
Name(name),
currentLookSide(RIGHT),
  currentFrame(0),
	numberOfFrames(Gamedata::getInstance().getXmlInt(name+"/frames")),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
	ylocation( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
last_velocity(getVelocityX()),
initialVelocity(getVelocity()),
currentAttack(NOTHING),
Fly(false),
OneLoop(false),
powerFire(false),
FireMode(false),
Defending(false),
Dying(false),Revive(false),GameOver(false),BlockControls(false),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
bullets( BulletPool::getInstance()  ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
FireCounter(0),
Lives(Gamedata::getInstance().getXmlInt(name+"/Lives/Value")),
Health(Gamedata::getInstance().getXmlInt(name+"/Health")),
SHealth(Gamedata::getInstance().getXmlInt(name+"/Health")),
sound( new SDLSoundPlayer(name))
{ 
setY(worldHeight-getScaledHeight());
	sound->play(0);
}

Player::Player(const Player& s) :
  Drawable(s), 
observers(s.observers),
LoadPower(s.LoadPower),
  Main(s.Main),
  Walk_R( s.Walk_R),
  Walk_L( s.Walk_L ),
  Standing( s.Standing ),
Fly_R(s.Fly_R),
Fly_L(s.Fly_L),
Fly_S(s.Fly_S),
Kick_R(s.Kick_R),
HKick_R(s.HKick_R),
Punch_R(s.Punch_R),
HPunch_R(s.HPunch_R),
Shoot_R(s.Shoot_R),
Kick_L(s.Kick_L),
HKick_L(s.HKick_L),
Punch_L(s.Punch_L),
HPunch_L(s.HPunch_L),
Shoot_L(s.Shoot_L),
Defend_L(s.Defend_L),
Defend_R(s.Defend_R),
Die_L(s.Die_L),
Die_R(s.Die_R),
Revive_L(s.Revive_L),
Revive_R(s.Revive_R),
Mega_L(s.Mega_L),
Mega_R(s.Mega_R),
  Name(s.Name),
currentLookSide(s.currentLookSide),
  currentFrame(s.currentFrame),
numberOfFrames(s.numberOfFrames),
  frameInterval( s.frameInterval ),
ylocation(s.ylocation),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
last_velocity(s.last_velocity),
initialVelocity(s.initialVelocity),
currentAttack(s.currentAttack),
Fly(s.Fly),
OneLoop(s.OneLoop),
powerFire(s.powerFire),
FireMode(s.FireMode),
Defending(s.Defending),
Dying(s.Dying),Revive(s.Revive),GameOver(s.GameOver),BlockControls(s.BlockControls),
  bulletName( s.bulletName ),
bullets( s.bullets ),
  minSpeed( s.minSpeed ),
FireCounter(s.FireCounter),
Lives(s.Lives),
Health(s.Health),
SHealth(s.SHealth),
sound(s.sound)
  { }

Player& Player::operator=(const Player& s) {
  Drawable::operator=(s);
	observers=(s.observers);
	LoadPower=(s.LoadPower);
  Main=(s.Main);
  Walk_R=( s.Walk_R);
  Walk_L=( s.Walk_L );
	Standing=( s.Standing );
	Fly_R=(s.Fly_R);
Fly_L=(s.Fly_L);
	Fly_S=(s.Fly_S);
	Kick_R=(s.Kick_R);
	HKick_R=(s.HKick_R),
	Punch_R=(s.Punch_R);
	HPunch_R=(s.HPunch_R);
	Shoot_R=(s.Shoot_R);
	Kick_L=(s.Kick_L);
HKick_L=(s.HKick_L);
Punch_L=(s.Punch_L);
HPunch_L=(s.HPunch_L);
Shoot_L=(s.Shoot_L);
	Defend_L=(s.Defend_L);
	Defend_R=(s.Defend_R);
	Die_L=(s.Die_L);
Die_R=(s.Die_R);
Revive_L=(s.Revive_L);
Revive_R=(s.Revive_R);
	Mega_L=(s.Mega_L);
	Mega_R=(s.Mega_R);
  Name = (s.Name);
currentLookSide=(s.currentLookSide);
  currentFrame = (s.currentFrame);
	numberOfFrames=(s.numberOfFrames);
  frameInterval = ( s.frameInterval );
	ylocation=(s.ylocation);
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
	last_velocity=(s.last_velocity);
	initialVelocity=(s.initialVelocity);
	currentAttack=(s.currentAttack),
	Fly=(s.Fly);
	OneLoop=(s.OneLoop);
	powerFire=(s.powerFire);
	FireMode=(s.FireMode);
	Defending=(s.Defending);
	Dying=(s.Dying);Revive=(s.Revive);GameOver=(s.GameOver);BlockControls=(s.BlockControls);
  bulletName=( s.bulletName );
  minSpeed=( s.minSpeed );
FireCounter=(s.FireCounter);
	Lives=(s.Lives);
	Health=(s.Health);
SHealth=(s.SHealth);
  return *this;
}


void Player::stop() { 
  if(Fly){setVelocity(Vector2f(0, 0) );}
	else{setVelocityX(0);}
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
		  currentLookSide=RIGHT;
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
		  currentLookSide=LEFT;
}

void Player::up()    { 
 if(Fly){
	if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }}
	else{
		setVelocityY(getVelocityY()==0? -200:getVelocityY() );  //Jump
	}
} 
void Player::down()  { 
	if(Fly){
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
	}//FLY End 
}


void Player::Player_Defend()  { 	
			currentFrame=0;
	 OneLoop=true;	
	Defending=true;
	  if(sidechecker()) {Main=Defend_R;}
	  else {Main=Defend_L;}
}

 void Player::SwitchToFly()  { 
		if(Fly){
			Fly=false;
			setVelocityY( initialVelocity[1]+initialVelocity[1]);
		}
	 else{
		Fly=true; OneLoop=true;					//Set Fly to True and on loop to true.
		setVelocityY(getVelocityY());
		Main=Fly_S;
	 }
	  }	
  void Player::SetImage_WalkRight()  { 
		currentFrame=0;
	  if(Fly){Main=Fly_R;}
	  	else{Main=Walk_R; }
	  currentLookSide=RIGHT;
	  }	
  void Player::SetImage_WalkLeft() { 
		currentFrame=0;
	  if(Fly){Main=Fly_L;}
		else{Main=Walk_L;}
	   currentLookSide=LEFT;
	  }
	  void Player::SetImage_standing() { 
			currentFrame=0;
			Main=Standing;
  }
 bool Player::sidechecker()
 {
	 if(currentLookSide == RIGHT) return true;
	 else return false;	
 }

//Combact
  void Player::Player_Kick() { 
	 		 OneLoop=true;	
			currentFrame=0;
	  if(sidechecker()) {Main=Kick_R;}
	  else {Main=Kick_L;}
	  currentAttack=KICK;
sound->play(1);
  }
void Player::Player_HKick() { 
	 		 OneLoop=true;	
			currentFrame=0;
	if(sidechecker()) {Main=HKick_R;}
	  else {Main=HKick_L;}
	 currentAttack=HKICK;
sound->play(1); 
 }
void Player::Player_Punch() { 
	 		 OneLoop=true;	
			currentFrame=0;
	if(sidechecker()) {Main=Punch_R;}
	  else {Main=Punch_L;}
	 currentAttack=PUNCH;
sound->play(2);  
}
void Player::Player_HPunch() { 
	 		 OneLoop=true;	
			currentFrame=0;
		if(sidechecker()) {Main=HPunch_R;}
	  else {Main=HPunch_L;}
	currentAttack=HPUNCH;
	sound->play(2);
  }
void Player::Player_Shoot() { 
	 		 OneLoop=true;	
			currentFrame=0;
		if(sidechecker()) {
			Main=Shoot_R;
		if(getThripleFire())FireCounter=3;
		else FireCounter=1;
		}
	  else {
		  Main=Shoot_L;	  
 		if(getThripleFire())FireCounter=3;
		else FireCounter=1;
		   }
  }

void Player::switch_walk()  { 
 
	if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }
	if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }
	
	
	if ( (getVelocityX()>0) & (last_velocity!=getVelocityX()) ) {
    		SetImage_WalkRight();
		last_velocity=getVelocityX();
  }
  if ( (getVelocityX()<0) & (last_velocity!=getVelocityX())) {
    SetImage_WalkLeft();
	  last_velocity=getVelocityX();
  }
	
	 if ( (getY() > worldHeight-getScaledHeight()) & (!Fly)) {
    setVelocityY( 0 );		 
  	}
	
	
	if((getY()<200) & (!Fly))
	{
		setVelocityY( fabs( getVelocityY() ) );
	}
		
	if((getVelocityX()==0) & (!Fly) & (!OneLoop) )
	{
			last_velocity=0;
		  	SetImage_standing();
	}
}


bool Player::collidedWith(Drawable* obj) const {
  return bullets.collidedWith( obj ,"Player");
}
void Player::draw() const { 
  Main[currentFrame]->draw(getX(),getY(), getScale());
	  bullets.draw();

	
	
	
	}

void Player::killSprite() { 
	auto it = observers.begin();
  while ( it != observers.end() ) {
	  
    if ( collidedWith(*it) ) {
      Drawable* doa = *it;
		powerShootLoad(20);
		if(doa->isDead())
		{
		doa->explode();
		}
		
    }
    else ++it;
  
  
  }
}

void Player::detach( Drawable* o ) {
  std::list<Drawable*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}
void Player::Player_Die() { 
			currentFrame=0;
	Dying=true;
	setVelocity(Vector2f(0, 0) );
	BlockControls=true;
		if(sidechecker()) {Main=Die_R;}
	  else {Main=Die_L;}
  }
  
void Player::Player_Revive() {
			currentFrame=0;
	Revive=true;
		if(sidechecker()) {Main=Revive_R;}
	  else {Main=Revive_L;}
  }

void Player::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
	
	
	 
	
	
	
	if((Health<=0) && !(BlockControls))    /////// DIE 
	{
	Player_Die();
	}
		if(!(BlockControls))
		{
	switch_walk();
		}
			bullets.update(ticks);
std::list<Drawable*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
	  
	 // std::cout<<(*ptr)->getName()<<std::endl;
    (*ptr)->setPlayerPos( getPosition() );
	  
    ++ptr;
  } 
	
	if((numberOfFrames-1==currentFrame) & (Revive))
	{
		  if(currentLookSide==RIGHT)	SetImage_WalkRight();	
		  if(currentLookSide==LEFT)		SetImage_WalkLeft();
		OneLoop=false;
		Revive=false;
		BlockControls=false;
	}
	if((Revive) && (Health<=SHealth))
	{
		Health=Health+50;
	}
		
	
	if((numberOfFrames-1==currentFrame) && (Dying))
	{
		Dying=false;
	if(Lives>0)
	{
	Lives--;
	sound->play(5);
		Player_Revive();
	}
		if(Lives==0)
		{
			sound->play(6);
			GameOver=true;
		}
	}
	else
	{
	if((OneLoop) & (numberOfFrames-1==currentFrame) & (Fly))
	{
		  if(currentLookSide==RIGHT)	SetImage_WalkRight();	
		  if(currentLookSide==LEFT)		SetImage_WalkLeft();
		OneLoop=false;
		Defending=false;
		currentAttack=NOTHING;
	}
	else if ((OneLoop) & (numberOfFrames-1==currentFrame))
	{
	 if(currentLookSide==RIGHT)	SetImage_WalkRight();	
		  if(currentLookSide==LEFT)		SetImage_WalkLeft();	
		OneLoop=false;
			Defending=false;
		currentAttack=NOTHING;
	}
		
	
		
		
	}

	
	 if (((int)round(numberOfFrames*0.75)==currentFrame) & (powerFire) & (BlockControls))
	{
		float x1 = getX()+getImage()->getWidth();
  float x2 = getX();
  
		float y = getY();
  // I'm not adding minSpeed to y velocity:
  bullets.Megshoot( Vector2f(sidechecker()?x1:x2, y), 
    Vector2f(sidechecker()?(minSpeed):-fabs(minSpeed), 0),"Player");
	resetPower();
		frameInterval=ylocation;
		powerFire=false;
		 BlockControls=false;
		 sound->play(8);
	}
	
	
	
	
	if((FireCounter>0) && (bullets.TimeChecked()) && (currentFrame%2==0)){
	 float x1 = getX()+getImage()->getWidth()/2;
  float x2 = getX()-getImage()->getWidth()/2;
  
		float y = getY()+(getImage()->getHeight()/2)/2;
  // I'm not adding minSpeed to y velocity:
  bullets.shoot( Vector2f(sidechecker()?x1:x2, y), 
    Vector2f(sidechecker()?(minSpeed*2):-fabs(minSpeed*2), 0),"Player");
	sound->play(9);
		FireCounter--;
	}
	if(!BlockControls)
	{
 stop();
	}
		}


void Player::powerShoot(){
	
	if(LoadPower>=SHealth)
	{
		currentFrame=0;
		if(sidechecker()) {Main=Mega_R;}
	  else {Main=Mega_L;}
	powerFire=true;
		OneLoop=true;
	 frameInterval=frameInterval*1.40;
	 BlockControls=true;
		Defending=true;
sound->play(7);
	}

}
