CC = g++
flags = -pthread
SRC = myMutex.cpp myMutexLock.cpp

all: mainwithlock mainwithoutlock

mainwithlock: mainwithlock.cpp $(SRC)
	$(CC) mainwithlock.cpp $(SRC) -o mainwithlock $(flags)
	./mainwithlock > results_comparison.txt 2>&1

mainwithoutlock: mainwithoutlock.cpp $(SRC)
	$(CC) mainwithoutlock.cpp $(SRC) -o mainwithoutlock $(flags)
	./mainwithoutlock >> results_comparison.txt 2>&1

clean:
	rm -f mainwithlock mainwithoutlock *.txt
