CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DSC
EXEC = cc3k+
MAINOBJS = main.o character.o floor.o game.o
ENEMYOBJS = enemies/enemy.o enemies/dragon.o enemies/goblin.o enemies/merchant.o enemies/phoenix.o enemies/troll.o enemies/vampire.o enemies/werewolf.o
ITEMOBJS = items/barriersuit.o items/gold.o items/item.o items/potion.o
PLAYEROBJS = players/dwarf.o players/elves.o players/human.o players/orc.o players/player.o 
OBJECTS = ${MAINOBJS} ${PLAYEROBJS} ${ENEMYOBJS} ${ITEMOBJS} 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
