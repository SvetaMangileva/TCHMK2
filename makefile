all:
	g++ -c ClassLN.cpp tchmk.cpp -fPIC
	g++ -shared -o ClassLN.so ClassLN.o tchmk.o
	g++ main.cpp ClassLN.so -I. -Wl,-rpath,. -L. -o 2lab -w
	rm -rf *.o
