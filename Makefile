CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DSC
EXEC = cc3k+
OBJECTS = main.o floor.o game.o character.o player.o enemy.o human.o orc.o dwarf.o elves.o item.o potion.o gold.o barriersuit.o vampire.o werewolf.o dragon.o goblin.o troll.o phoenix.o merchant.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
