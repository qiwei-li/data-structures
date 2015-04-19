power.out : grid.o PowerMain.o  
	g++ -ansi -Wall -g -o power.out grid.o PowerMain.o  

grid.o : grid.cpp grid.h 
	g++ -ansi -Wall -g -c grid.cpp

PowerMain.o : PowerMain.cpp CPUTimer.h grid.h PowerMain.h 
	g++ -ansi -Wall -g -c PowerMain.cpp

clean : 
	rm -f power.out grid.o  PowerMain.o   
