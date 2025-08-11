bms:
	g++ bms.cpp -o bms
	./bms < input.txt

dfs:
	g++ dfs.cpp -o dfs
	./dfs < input.txt

bfs:
	g++ bfs.cpp -o bfs
	./bfs < input.txt

bfs+dfs:
	g++ bfs+dfs.cpp -o bfs+dfs
	./bfs+dfs < input.txt

dfs+h:
	g++ dfs+h.cpp -o dfs+h
	./dfs+h < input.txt

bfs+h:
	g++ bfs+h.cpp -o bfs+h
	./bfs+h < input.txt

hc:
	g++ hc.cpp -o hc
	./hc < inputbnb.txt

hc+h:
	g++ hc+h.cpp -o hc+h
	./hc+h < input.txt

bs:
	g++ bs.cpp -o bs
	./bs < input_bs.txt

bs+h:
	g++ bs+h.cpp -o bs+h
	./bs+h < input_bs.txt

oracle:
	g++ oracle.cpp -o oracle
	./oracle < input.txt

bnb:
	g++ bnb.cpp -o bnb
	./bnb < input.txt

bnb+c+h:
	g++ bnb+c+h.cpp -o bnb+c+h
	./bnb+c+h < inputbnb.txt

bnb+h:
	g++ bnb+h.cpp -o bnb+h
	./bnb+h < inputbnb+h.txt

Astar:
	g++ Astar.cpp -o Astar
	./Astar < inputa.txt

clean:
	rm -f ./bms
	rm -f ./dfs
	rm -f ./bfs
	rm -f ./bfs+dfs
	rm -f ./dfs+h
	rm -f ./bfs+h
	rm -f ./hc
	rm -f ./hc+h
	rm -f ./bs
	rm -f ./bs+h
	rm -f ./oracle
	rm -f ./bnb
	rm -f ./bnb+c+h
	rm -f ./bnb+h
	rm -f ./Astar