all: simple battery

debug-all: simple-debug battery-debug

debug: simple-debug battery-debug

simple: battery_simple.cpp
	g++ -o battery_simple battery_simple.cpp -lwiringPi
	
battery: battery.cpp
	g++ -o battery battery.cpp -lwiringPi

simple-debug: battery_simple.cpp
	g++ -o battery_simple battery_simple.cpp -lwiringPi -g
	
battery-debug: battery.cpp
	g++ -o battery battery.cpp -lwiringPi -g
