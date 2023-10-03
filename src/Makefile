CC =gcc -g -Wall -Werror -Wextra -std=c11 -D_GNU_SOURSE
OS = $(shell uname -s)
ifeq ($(OS), Linux)
UBU =  -lm -lpthread -lrt -lsubunit
else
UBU = 
endif

all: test gcov_report dvi install clean

install:
	mkdir build
	cd build && qmake ../New_hope.pro && make
	cd build && cp -r New_hope.app ~/Desktop
	rm -drf build


uninstall:
	rm -rf ~/Desktop/New_hope.app

dist: install
	tar -czf New_hope.tar.gz ~/Desktop/New_hope.app
	rm -rf ~/Desktop/New_hope.app

dvi: 
	open README.md

test:
	$(CC) -lcheck $(UBU) test.c parcer.c  -o test.out
	./test.out

gcov_report:
	$(CC) --coverage parcer.c -lcheck $(UBU) test.c -o test.out
	./test.out
	lcov -t "my_test" -c -d ./ --output-file ./test.info
	genhtml -o report test.info
	rm -rf *.gcda *.gch *.gcno *.out *.o *.out
	open report/index.html

clean:
	rm -rf *.o *.a *.out *.info report test.out.dSYM *.gcno

style:
	clang-format -i --style=Google *.c *.h  *.cpp
	clang-format -n --style=Google *.c *.h  *.cpp

leaks :
	leaks -atExit -- ./test.out