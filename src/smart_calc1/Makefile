CC = gcc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck

ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

TARGET = smart_calc1

install:       
	echo "Installation of $(TARGET).app:"
	mkdir -p ../build
	cd ./qt && qmake && make && make clean && rm -rf Makefile && mv calculator.app ../../build/$(TARGET).app
	echo "Installation completed! You can find app in the ../build/ folder!"

uninstall:
	rm -rf ../build
	echo "Uninstall completed!"
	
dist: install
	mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp -R . ../dist/src
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app
	@rm -rf ../dist/src
	echo "Archive creation completed successfully!"
	

test: calc.a
	$(CC) $(FLAGS) -c test.c
	$(CC) s21_math_test.o $(FLAGS) $(LFLAGS) -L. calc.a -o test

calc.a:
	$(CC) $(FLAGS) -c calc.c 
	ar rc calc.a calc.o 
	ranlib calc.a

add_coverage:
	$(eval FLAGS += --coverage)

gcov_report: clean add_coverage test
	-./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style_check:
	clang-format -n *.c *.h

style_fix:
	clang-format -i *.c *.h

clean: 
	rm -rf *.o *.a *.gcno *.gcda test test.info report

rebuild: clean all
