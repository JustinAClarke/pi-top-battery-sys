all: simple battery lxpanel-plugin

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


lxpanel-plugin:
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC ./batt/batt.c -o battery.so `pkg-config --libs lxpanel`

install:
#	sudo cp battery.so /usr/lib/lxpanel/plugins/
	sudo cp battery.so /usr/lib/arm-linux-gnueabihf/lxpanel/plugins/
	sudo mkdir -p /opt/pi-top-battery-sys/
	sudo cp -R ./ /opt/pi-top-battery-sys/
	sudo cp pi-top-battery-sys.service /etc/systemd/system
	sudo cp pi-top-battery-sys.timer /etc/systemd/system
	sudo systemctl enable pi-top-battery-sys.timer
	sudo systemctl start pi-top-battery-sys.timer

uninstall:
#	sudo rm /usr/lib/lxpanel/plugins/battery.so
	sudo rm /usr/lib/arm-linux-gnueabihf/lxpanel/plugins/battery.so
	sudo systemctl stop pi-top-battery-sys.timer
	sudo systemctl disable pi-top-battery-sys.timer
	sudo rm /etc/systemd/system/pi-top-battery-sys.service
	sudo rm /etc/systemd/system/pi-top-battery-sys.timer
	rm -R /opt/pi-top-battery-sys
