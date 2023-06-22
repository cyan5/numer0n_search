.PHONY: all
all: main.o func.o call.o cand.o data.o debug.o
	gcc -Wall -O2 obj/*.o
main.o: main.c
	gcc -Wall -O2 -c -o obj/main.o main.c
func.o: func.c
	gcc -Wall -O2 -c -o obj/func.o func.c
call.o: call.c
	gcc -Wall -O2 -c -o obj/call.o call.c
cand.o: cand.c
	gcc -Wall -O2 -c -o obj/cand.o cand.c
data.o: data.c
	gcc -Wall -O2 -c -o obj/data.o data.c
debug.o: debug.c
	gcc -Wall -O2 -c -o obj/debug.o debug.c

.PHONY: clean
clean:
	rm -rf ./a.out obj/*.o
	@echo clean completed.

# depends header

# cand.o: 
call.o: symbol.h call.h
func.o: symbol.h func.h call.h
main.o: symbol.h func.h
data.o: symbol.h data.h
debug.o: symbol.h