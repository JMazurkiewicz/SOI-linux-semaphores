all:
	gcc src/*.c -I include -pthread -lrt

clean:
	rm *.o *.out
