CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -L/opt/X11/lib -lX11 -I/opt/X11/include
EXEC = tetris
OBJECTS = main.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o cblock.o subject.o observer.o tile.o board.o textdisplay.o commandinterpreter.o blockpart.o AbsLevel.o LevelZero.o LevelOne.o LevelTwo.o LevelThree.o LevelFour.o AbsBoard.o decorator.o blind.o force.o heavy.o window.o graphics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS} 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/opt/X11/lib -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
