CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DSC
EXEC = cc3k+
MAINOBJS = character.o floor.o game.o main.o
ENEMYOBJS = enemy/dragon.o enemy/goblin.o enemy/merchant.o enemy/phoenix.o enemy/troll.o enemy/vampire.o enemy/werewolf.o
ITEMOBJS = item/barriersuit.o item/gold.o item/item.o item/potion.o
PLAYEROBJS = player/dwarf.o player/elves.o player/human.o player/orc.o player/player.o 
OBJECTS = ${MAINOBJS} ${ENEMYOBJS} ${ITEMOBJS} ${PLAYEROBJS}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
