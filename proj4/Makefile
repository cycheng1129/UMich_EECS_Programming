proj4.exe: LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o project4.o
	g++ LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o project4.o -o proj4.exe

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -c LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h
	g++ -c SortedListClass.cpp -o SortedListClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h
	g++ -c FIFOQueueClass.cpp -o FIFOQueueClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h
	g++ -c LIFOStackClass.cpp -o LIFOStackClass.o

project4.o: project4.cpp
	g++ -c project4.cpp -o project4.o

clean:
	rm -rf LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o project4.o proj4.exe
