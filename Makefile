CC:= gcc
FLAGS:= -W -Wall -g
TEST_DIR:= test/
TEST_NEEDS:= os_hw1_tester/* testlib Makefile
C_FILES:= main.c input_handler.c tokenize.c basic_handler.c my_funcs.c lib_hw1/bitmap.c lib_hw1/hash.c lib_hw1/list.c 
OBJS:= main.o input_handler.o tokenize.o basic_handler.o my_funcs.o bitmap.o hash.o list.o 

build: $(OBJS)
	gcc $(FLAGS) -o testlib $(OBJS)

$(OBJS): $(C_FILES) 
	$(CC) $(FLAGS) -c $(C_FILES)

test: build
	@mkdir $(TEST_DIR)
	@cp $(TEST_NEEDS) $(TEST_DIR)
	make -C $(TEST_DIR) test_run

test_run: hw1_tester.sh testlib
	./hw1_tester.sh ./testlib

test_clean:
	@rm -rf $(TEST_DIR)

clean: test_clean
	@rm -rf testlib $(OBJS)
