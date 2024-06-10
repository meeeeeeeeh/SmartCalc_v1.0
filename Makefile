CC = gcc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck

ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

install:
	mkdir ./build
	cd ./build && qmake ../smart_calc1 && make
	
uninstall:
	rm -rf ./build

dist: install
	mkdir -p ./dist
	@cp -R ./build/smart_calc1.app ./dist
	@cp -R . ./dist/src
	@cd ./dist && tar cvzf smart_calc1.tgz *
	@cd ./dist && rm -rf smart_calc1.app
	@rm -rf ./dist/src
	

dvi:
	doxygen smart_calc1/dvi_config
	open html/index.html

test: calc.a
	$(CC) $(FLAGS) -c smart_calc1/test.c
	$(CC) test.o $(FLAGS) $(LFLAGS) -L. calc.a -o test
	-./test

calc.a:
	$(CC) $(FLAGS) -c smart_calc1/calc.c 
	ar rc calc.a calc.o 
	ranlib calc.a

add_coverage:
	$(eval FLAGS += --coverage)

gcov_report: clean add_coverage test
	-./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean: 
	rm -rf *.o *.a *.gcno *.gcda test test.info report html 
	
rebuild: clean all
