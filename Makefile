CC:= gcc
FLAGS:= -W -Wall -g
TEST_DIR:= test/
TEST_NEEDS:= os_hw1_tester/* a.out Makefile
C_FILES:= main.c command.c tokenize.c lib_hw1/bitmap.c lib_hw1/hash.c lib_hw1/list.c 
OBJS:= main.o command.o tokenize.o bitmap.o hash.o list.o 

build: $(OBJS)
	gcc $(FLAGS) -o a.out $(OBJS)

$(OBJS): $(C_FILES) 
	$(CC) $(FLAGS) -c $(C_FILES)

test: build
	@mkdir $(TEST_DIR)
	@cp $(TEST_NEEDS) $(TEST_DIR)
	make -C $(TEST_DIR) test_run

test_run: hw1_tester.sh a.out
	./hw1_tester.sh ./a.out

test_clean:
	@rm -rf $(TEST_DIR)

clean: test_clean
	@rm -rf a.out $(OBJS)
