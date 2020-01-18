proj5.exe: EventClass.o RestaurantSimulationClass.o random.o project5.o
	g++ EventClass.o RestaurantSimulationClass.o random.o project5.o -o proj5.exe

project5.o: project5.cpp
	g++ -c project5.cpp -o project5.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -c EventClass.cpp -o EventClass.o

RestaurantSimulationClass.o: RestaurantSimulationClass.cpp RestaurantSimulationClass.h
	g++ -c RestaurantSimulationClass.cpp -o RestaurantSimulationClass.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

clean:
	rm -rf EventClass.o RestaurantSimulationClass.o random.o project5.o proj5.exe
