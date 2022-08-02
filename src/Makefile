CC = gcc
CFLAG = -Wall -Wextra -Werror
BUILD = ../build/

all: install

build:
	cp SmartCalc.pro $(BUILD)
	cp *.cpp SmartCalc.c *.h *.ui *.icns $(BUILD)
	cd $(BUILD); qmake SmartCalc.pro
	make -C $(BUILD)

install: build
	open $(BUILD)SmartCalc.app
	make clean

uninstall:
	rm -rf $(BUILD)SmartCalc.app

dvi:
	open smartCalc_documentation.html
	
dist:
	rm -rf SmartCalc.tar.gz
	tar -czvf SmartCalc.tar.gz *
	mv SmartCalc.tar.gz $(BUILD)

smartCalc.a:
	$(CC) $(CFLAG) -c smartCalc.c
	@ar rcs smartCalc.a smartCalc.o

tests: smartCalc.a
	$(CC) $(CFLAG) -c smart_test.c -o test1
	$(CC) test1 smartCalc.a -lcheck -o test2
	./test2

gcov_report:
	$(CC) --coverage smart_test.c -o _test smartCalc.c -lcheck
	./_test
	lcov -t "_test" -o _test.info -c -d .
	genhtml -o report _test.info
	open ./report/index.html

check: tests
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	CK_FORK=no leaks --atExit -- ./test2

clean:
	@rm -rf *.o *.a *.gcda *.gcno *.info CPPLINT.cfg
	@rm -rf _test report test test1 test2
	@rm -rf ./$(BUILD)*.o ./$(BUILD)*.h ./$(BUILD)*.cpp ./$(BUILD)SmartCalc.pro
	@rm -rf ./$(BUILD)Makefile ./$(BUILD)*.c ./$(BUILD)*.ui ./$(BUILD)*.icns

rebuild: clean all
 