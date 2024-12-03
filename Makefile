CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -lncurses -g
C_FILES = brick_game/tetris.c gui/cli.c brick_game/helpers.c brick_game/fsm/fsm.c
H_FILES = brick_game/tetris.h brick_game/test/test.h
TEST_FILES = brick_game/test/*.c
BUILD_PATH = brick_game/tetris/build/Manual_Build

ifeq ($(shell uname), Linux)
	CHECKFLAGS= -lcheck -lm -lpthread -lrt -lsubunit
	LAUNCHFLAGS=LIBGL_ALWAYS_SOFTWARE=1 
else
	CHECKFLAGS=-lcheck -lm -lpthread
	EXTENDED_PATH=/3d_viewer.app/Contents/MacOS
endif

install:
	gcc -Wall -Werror -Wextra brick_game/tetris.c brick_game/main.c brick_game/fsm/fsm.c brick_game/helpers.c gui/cli.c -lncurses && ./a.out

uninstall: clean
	rm -rf a.out

dvi:
	open brick_game/doc.md

dist:
	mkdir tetris_archive
	cp -a brick_game tetris_archive
	cp -a brick_game/fsm tetris_archive
	cp -a gui tetris_archive
	cp -a brick_game/main.c tetris_archive
	cp -a Makefile tetris_archive
	tar -czf tetris_archive.tar.gz tetris_archive
	rm -rf tetris_archive

test: clean $(TEST_FILES) ${C_FILES}
	@$(CC) $(CFLAGS)  brick_game/tetris.c brick_game/helpers.c brick_game/test/test.c brick_game/test/test_function.c $(CHECKFLAGS) -o tests
	@./tests

gcov_report: clean $(TEST_FILES) ${C_FILES}
	@$(CC) $(CFLAGS) --coverage brick_game/tetris.c brick_game/helpers.c brick_game/test/test.c brick_game/test/test_function.c -o gcov_report $(CHECKFLAGS)
	@./gcov_report
	@lcov -t "./gcov_report" -o gcov_report.info --no-external -c -d .
	@genhtml -o rpn_report gcov_report.info
ifeq ($(shell uname), Darwin)
	open ./rpn_report/index.html
endif

style: clean
	clang-format -style=Google -n $(C_FILES) brick_game/main.c $(H_FILES) $(TEST_FILES)

clang:
	clang-format -style=Google -i $(C_FILES) brick_game/main.c $(H_FILES) $(TEST_FILES)

valgrind: tests
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind_report.txt ./tests

clean:
	rm -rf *.o *.a report *.gcno *.gcda *.info *.txt gcov_report rpn_report valgrind_report.txt dist.tar.gz tests tests.dSYM gcov_report.dSYM a.out tetris_archive.tar.gz tetris_archive
