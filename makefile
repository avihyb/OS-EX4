CC= g++
flags=-std=c++11 -O3
src= main.cpp Graph.cpp
GCOV_FLAGS= -fprofile-arcs -ftest-coverage -fPIC -O0
VALGRIND_FLAGS= --leak-check=full --track-origins=yes  -s
VERTICES= -v 5
EDGES= -e 6
SEED= -s 0

all: program valgrind gcov gprof

program: $(src)
	$(CC) $(flags) -o program $(src)

valgrind: program
	valgrind $(VALGRIND_FLAGS) ./program $(VERTICES) $(EDGES) $(SEED) > valgrind_report.txt 2>&1

gcov: 
	$(CC) $(flags) $(GCOV_FLAGS) -o program $(src)
	./program $(VERTICES) $(EDGES) $(SEED)
	gcovr --txt code_coverage_report.txt
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

gprof:
	$(CC) $(flags) -pg -o program $(src)
	./program $(VERTICES) $(EDGES) $(SEED)
	gprof program gmon.out > gprof_report.txt

clean:
	rm -f program valgrind_report.txt *.gcno *.gcda *.gcov code_coverage_report.txt coverage.info *.png gmon.out gprof_report.txt
	rm -rf out
