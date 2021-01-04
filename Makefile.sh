all: clean install run
clean:
	rm -rf main.out
	rm -rf main
	rm -rf main.out.dSYM
install: main.c
	gcc -g -ggdb main.c -o main.out
run: main.out
	./main.out


    





