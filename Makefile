.PHONY: all
all: main.o func.o call.o cand.o
	gcc -Wall -O2 main.o func.o call.o cand.o
main.o: main.c
	gcc -Wall -O2 -c -o main.o main.c
func.o: func.c
	gcc -Wall -O2 -c -o func.o func.c
call.o: call.c
	gcc -Wall -O2 -c -o call.o call.c
cand.o: cand.c
	gcc -Wall -O2 -c -o cand.o cand.c

.PHONY: clean
clean:
	rm -rf ./a.out main.o func.o call.o cand.o
	@echo clean completed.

# depends header

# cand.o: 
call.o: symbol.h call.h
func.o: symbol.h func.h call.h
main.o: symbol.h func.h