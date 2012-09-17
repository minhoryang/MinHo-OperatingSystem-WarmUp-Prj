build: main.o bitmap.o hash.o list.o
	gcc -o a.out bitmap.o hash.o list.o main.o

main.o:
	gcc -o main.o -c main.c

bitmap.o:
	gcc -o bitmap.o -c lib_hw1/bitmap.c

hash.o:
	gcc -o hash.o -c lib_hw1/hash.c

list.o:
	gcc -o list.o -c lib_hw1/list.c

clean:
	rm -rf os_hw1_tester/Score.txt
	rm -rf main.o bitmap.o hash.o list.o
	rm -rf a.out
