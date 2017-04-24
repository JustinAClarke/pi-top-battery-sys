# what flags you want to pass to the C compiler & linker
CFLAGS = -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC
LDFLAGS = `pkg-config --libs lxpanel`

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = battery
battery_SOURCES = batt.c  batt_sys.c  batt_sys.h  dbg.h
