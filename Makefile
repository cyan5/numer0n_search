.PHONY: all
all: obj/main.o obj/func.o obj/call.o obj/cand.o obj/data.o obj/debug.o
# all: obj/main.o obj/func.o obj/call.o obj/cand.o obj/data.o obj/debug.o
	gcc -Wall -O2 obj/*.o
obj/main.o: main.c
	gcc -Wall -O2 -c -o obj/main.o main.c
obj/func.o: func.c
	gcc -Wall -O2 -c -o obj/func.o func.c
obj/call.o: call.c
	gcc -Wall -O2 -c -o obj/call.o call.c
obj/cand.o: cand.c
	gcc -Wall -O2 -c -o obj/cand.o cand.c
obj/data.o: data.c
	gcc -Wall -O2 -c -o obj/data.o data.c
obj/debug.o: debug.c
	gcc -Wall -O2 -c -o obj/debug.o debug.c

.PHONY: clean
clean:
	rm -f ./a.out obj/*.o
	@echo clean completed.

# depends header

# cand.o: 
call.o: symbol.h call.h
func.o: symbol.h func.h call.h
main.o: symbol.h func.h
data.o: symbol.h data.h
debug.o: symbol.h