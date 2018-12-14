CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl2-config --cflags` -g -W -Wall -Werror -std=c++11 -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lexpat -lSDL2_ttf -lSDL2_image -lSDL2_mixer

OBJS = \
  renderContext.o \
	ioMod.o \
	parseXML.o \
	gameData.o \
	viewport.o \
	world.o \
	collisionStrategy.o\
	healthBar.o\
	bulletsprite.o \
	sprite.o \
	npc_sound.o\
	multisprite.o \
	chunk.o \
	menu_multisprite.o\
	explodingprojectile.o\
	explodingSprite.o\
    sprite_box.o\
	spriteSheet.o \
	image.o \
	HUD.o\
	sound.o\
	menu.o\
	menuEngine.o\
	bullet.o \
	bulletPool.o \
	imageFactory.o \
	frameGenerator.o \
	player_sound.o\
    player.o\
	vector2f.o \
	clock.o \
	engine.o \
	main.o
EXEC = run

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf frames/*.bmp
