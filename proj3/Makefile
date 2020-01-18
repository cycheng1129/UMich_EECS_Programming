project3.exe: isOutOfPixel.o mainMenu.o drawRect.o annoPattern.o insertion.o cinInt.o ColorClass.o ColorImageClass.o project3.o
	g++ isOutOfPixel.o mainMenu.o drawRect.o annoPattern.o insertion.o cinInt.o ColorClass.o ColorImageClass.o project3.o -o proj3.exe

project3.o: project3.cpp
	g++ -c project3.cpp -o project3.o

isOutOfPixel.o: isOutOfPixel.cpp isOutOfPixel.h
	g++ -c isOutOfPixel.cpp -o isOutOfPixel.o

mainMenu.o: mainMenu.cpp mainMenu.h
	g++ -c mainMenu.cpp -o mainMenu.o

drawRect.o: drawRect.cpp drawRect.h
	g++ -c drawRect.cpp -o drawRect.o
	
annoPattern.o: annoPattern.cpp annoPattern.h
	g++ -c annoPattern.cpp -o annoPattern.o

insertion.o: insertion.cpp insertion.h
	g++ -c insertion.cpp -o insertion.o

cinInt.o: cinInt.cpp cinInt.h
	g++ -c cinInt.cpp -o cinInt.o

ColorClass.o: ColorClass.cpp ColorClass.h
	g++ -c ColorClass.cpp -o ColorClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

clean:
	rm -rf isOutOfPixel.o mainMenu.o drawRect.o annoPattern.o insertion.o cinInt.o ColorClass.o ColorImageClass.o project3.o proj3.exe