CC=g++
CFLAGS=-std=c++17 -Wall -Werror -Wextra -g -pedantic
TEST_LIBS = -lgtest -lgtest_main
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
HEADERS = Model/calc_model.h

ifeq ($(OS), Linux)
#-lsubunit
	CHECKFLAGS=-lpthread -pthread -lrt -lm -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean install dist dvi gcov_report check_style leaks clean

rebuild: clean all

install: uninstall
	mkdir build
	cp Calculator.pro build
	cp -rf main.cpp build
	cp -rf qcustomplot.cpp build
	cp -rf qcustomplot.h build
	cp -rf ./View/*.cpp build
	cp -rf ./View/*.h build
	cp -rf ./View/*.ui build
	cp -rf ./Controller/*.cpp build
	cp -rf ./Controller/*.h build
	cp -rf ./Model/*.cpp build
	cp -rf ./Model/*.h build
	cd build && qmake Calculator.pro
	make -C build
	cd build && make clean

uninstall:
	rm -rf build
	make clean

dvi:
	open ./readme.txt

dist: install
	tar -cvf build/Сalculator.tar build
	gzip build/Сalculator.tar
	mv build/Сalculator.tar.gz ./

test: clean
	$(CC) ./Model/calc_model.cpp tests.cpp $(CFLAGS) -o tests.out $(TEST_LIBS) $(GCOVFLAGS)
	./tests.out


gcov_report: test
	gcov $(HEADERS)
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	open ./gcov_report/index.html
	rm -f *.gcno *.gcda *.info report.out *.gcov

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./View/*.cpp
	clang-format -i ./View/*.h
	clang-format -i ./Model/*.cpp
	clang-format -i ./Model/*.h
	clang-format -i ./Controller/*.cpp
	clang-format -i ./Controller/*.h
	clang-format -i main.cpp
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./View/*.cpp >> logfile.log
	clang-format -n ./View/*.h >> logfile.log
	clang-format -n ./Model/*.cpp >> logfile.log
	clang-format -n ./Model/*.h >> logfile.log
	clang-format -n ./Controller/*.cpp >> logfile.log
	clang-format -n ./Controller/*.h >> logfile.log
	clang-format -n main.cpp >> logfile.log
	rm -rf .clang-format

leaks: test
	CK_FORK=no leaks --atExit -- ./test.out >> logfile.log #leaks --atExit --
	make clean

valgrind:
	$(CC) $(CFLAGS)  *.c -o  test.out -lrt -lpthread -lm -lcheck $(CHECKFLAGS)
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test.out
	 make clean
	
clean:
	rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
		*.log \
		build

