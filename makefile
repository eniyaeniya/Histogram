CC = g++

all: singleThreadHistogram multiThreadHistogram

singleThreadHistogram: singleThreadHistogram.cpp
	$(CC) -o singleThreadHistogram singleThreadHistogram.cpp

multiThreadHistogram: multiThreadHistogram.cpp
	$(CC) -pthread -o multiThreadHistogram multiThreadHistogram.cpp

clean:
	rm -f singleThreadHistogram multiThreadHistogram
