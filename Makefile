build: main.cpp
	g++ main.cpp -o main

run: main
	./main

clean: main
	rm main
