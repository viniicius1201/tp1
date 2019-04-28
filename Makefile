all:
	g++ -Wall -Werror -std=c++11 day.cpp -c -o day.o
	g++ -Wall -Werror -std=c++11 agenda.cpp -c -o agenda.o
	g++ -Wall -Werror -std=c++11 main.cpp -c -o main.o
	g++ -Wall -Werror -std=c++11 -o tp1 main.o day.o agenda.o
	rm *.o

run:
	./tp1

clean:
	rm *.o
