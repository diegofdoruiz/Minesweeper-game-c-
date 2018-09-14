all: Minesweeper TestLogic

Minesweeper: Minesweeper.o Interfaz.o Logic.o
			 #g++ Minesweeper.cpp Interfaz.cpp Logic.cpp -o minesweeper
			 g++ -std=c++11 Minesweeper.cpp Interfaz.cpp Logic.cpp -o minesweeper

TestLogic: TestLogic.o Interfaz.o Logic.o
		   #g++ TestLogic.cpp Interfaz.cpp Logic.cpp -o testlogic
		    g++ -std=c++11 TestLogic.cpp Interfaz.cpp Logic.cpp -o testlogic
			 
TestLogic.o: TestLogic.cpp
		     #g++ -c TestLogic.cpp
		     g++ -std=c++11 -c TestLogic.cpp

Minesweeper.o: Minesweeper.cpp
			   #g++ -c Minesweeper.cpp
			   g++ -std=c++11 -c Minesweeper.cpp

Interfaz.o: Interfaz.cpp
			#g++ -c Interfaz.cpp
			g++ -std=c++11 -c Interfaz.cpp

Logic.o: Logic.cpp
		 #g++ -c Logic.cpp
		 g++ -std=c++11 -c Logic.cpp

clean: 
		rm -rf *o TestLogic Minesweeper