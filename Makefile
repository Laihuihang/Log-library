Log : LogTimeStamp.o LogBuffer.o main.o LogStream.o
	g++ -g LogTimeStamp.o LogBuffer.o main.o LogStream.o -o Log

LogTimeStamp.o : LogTimeStamp.h LogTimeStamp.cpp
	g++ -g -c LogTimeStamp.cpp -o LogTimeStamp.o

LogBuffer.o : LogBuffer.h LogBuffer.cpp
	g++ -g -c LogBuffer.cpp -o LogBuffer.o

main.o : main.cpp
	g++ -g -c main.cpp -o main.o

LogStream.o : LogStream.h LogStream.cpp
	g++ -g -c LogStream.cpp -o LogStream.o


.PHONY: clean
clean :	
	rm *.o Log

