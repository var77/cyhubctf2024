chal: main.c
	gcc -o chal -O0 main.c

solution.o: solution.c
	gcc -c -fPIC solution.c -o solution.o

libsolution.so:
	gcc solution.o -shared -o libsolution.so

solve: chal solution.o libsolution.so
	LD_PRELOAD=./libsolution.so ./chal
