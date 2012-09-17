ARGS:= -g

build: bitmap.o hash.o list.o tokenize.o
	gcc $(ARGS) -o main.o -c main.c
	gcc $(ARGS) -o a.out bitmap.o hash.o list.o main.o tokenize.o

tokenize.o:
	gcc $(ARGS) -o tokenize.o -c tokenize.c

bitmap.o:
	gcc $(ARGS) -o bitmap.o -c lib_hw1/bitmap.c

hash.o:
	gcc $(ARGS) -o hash.o -c lib_hw1/hash.c

list.o:
	gcc $(ARGS) -o list.o -c lib_hw1/list.c

clean:
	rm -rf os_hw1_tester/Score.txt
	rm -rf main.o bitmap.o hash.o list.o tokenize.o
	rm -rf a.out
