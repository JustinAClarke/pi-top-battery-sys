/**
*    Writes info from the pi-top battery to /sys/class/power_supply/BAT0/uevent
*    Copyright (C) 2017 Justin Fuhrmeister-Clarke justin@fuhrmeister-clarke.com
*
*    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General      Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**/

#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <iostream>

//#include <stdio>
//#include <fstream>
//#include <wiringPiI2C.h>

//format %status %percentage %remaining

/**
POWER_SUPPLY_NAME=BAT0  
POWER_SUPPLY_STATUS=Discharging  
POWER_SUPPLY_PRESENT=1  
POWER_SUPPLY_TECHNOLOGY=Li-ion  
POWER_SUPPLY_CYCLE_COUNT=481  
POWER_SUPPLY_VOLTAGE_MIN_DESIGN=7400000  
POWER_SUPPLY_VOLTAGE_NOW=7400000  
POWER_SUPPLY_POWER_NOW=9361000  
POWER_SUPPLY_ENERGY_FULL_DESIGN=48248000  
POWER_SUPPLY_ENERGY_FULL=40877000  
POWER_SUPPLY_ENERGY_NOW=20712000  
POWER_SUPPLY_CAPACITY=50  
POWER_SUPPLY_MODEL_NAME=UX32-65  
POWER_SUPPLY_MANUFACTURER=ASUSTeK  
POWER_SUPPLY_SERIAL_NUMBER=   
**/

int i2c_handle;
char POWER_SUPPLY_NAME[16];
char POWER_SUPPLY_STATUS[16];
char POWER_SUPPLY_PRESENT[16];
char POWER_SUPPLY_TECHNOLOGY[16];
char POWER_SUPPLY_CYCLE_COUNT[16];
char POWER_SUPPLY_VOLTAGE_MIN_DESIGN[16];
char POWER_SUPPLY_VOLTAGE_NOW[16];
char POWER_SUPPLY_POWER_NOW[16];
char POWER_SUPPLY_ENERGY_FULL_DESIGN[16];
char POWER_SUPPLY_ENERGY_FULL[16];
char POWER_SUPPLY_ENERGY_NOW[16];
char POWER_SUPPLY_CAPACITY[16];
char POWER_SUPPLY_MODEL_NAME[16];
char POWER_SUPPLY_MANUFACTURER[16];
char POWER_SUPPLY_SERIAL_NUMBER[16];


int readVal(int loc){
    //int res = wiringPiI2CReadReg8(i2c_handle, loc);
    int res = 0;
    if (loc == 0x0A) {	// convert to signed integer
        if (res > 32767)
            res -= 65536;
    }
    return res;
}

char* readValChar(int loc){
    
    char *val;
    int tmp;
    tmp = readVal(loc);

    sprintf(val,"%d",tmp);
    return val;
}

int writeFile(void){
    std::ofstream uevent;

    uevent.open("uevent");
    //uevent.open("/sys/class/power_supply/BAT0/uevent");
    
    //uevent << "POWER_SUPPLY_NAME=BAT0  \nPOWER_SUPPLY_STATUS=Discharging  \nPOWER_SUPPLY_PRESENT=1  \nPOWER_SUPPLY_TECHNOLOGY=Li-ion  \nPOWER_SUPPLY_CYCLE_COUNT=481  \nPOWER_SUPPLY_VOLTAGE_MIN_DESIGN=7400000  \nPOWER_SUPPLY_VOLTAGE_NOW=7400000  \nPOWER_SUPPLY_POWER_NOW=9361000  \nPOWER_SUPPLY_ENERGY_FULL_DESIGN=48248000  \nPOWER_SUPPLY_ENERGY_FULL=40877000  \nPOWER_SUPPLY_ENERGY_NOW=20712000  \nPOWER_SUPPLY_CAPACITY=50  \nPOWER_SUPPLY_MODEL_NAME=UX32-65  \nPOWER_SUPPLY_MANUFACTURER=ASUSTeK  \nPOWER_SUPPLY_SERIAL_NUMBER=   \n";
    
    uevent << "POWER_SUPPLY_NAME=";
    uevent << POWER_SUPPLY_NAME;
    uevent << "\n";
    uevent << "POWER_SUPPLY_STATUS=";
    uevent << POWER_SUPPLY_STATUS;
    uevent << "\n";
    uevent << "POWER_SUPPLY_PRESENT=";
    uevent << POWER_SUPPLY_PRESENT;
    uevent << "\n";
    uevent << "POWER_SUPPLY_TECHNOLOGY=ion  ";
    uevent << POWER_SUPPLY_TECHNOLOGY;
    uevent << "\n";
    uevent << "POWER_SUPPLY_CYCLE_COUNT=";
    uevent << POWER_SUPPLY_CYCLE_COUNT;
    uevent << "\n";
    uevent << "POWER_SUPPLY_VOLTAGE_MIN_DESIGN=";
    uevent << POWER_SUPPLY_VOLTAGE_MIN_DESIGN;
    uevent << "\n";
    uevent << "POWER_SUPPLY_VOLTAGE_NOW=";
    uevent << POWER_SUPPLY_VOLTAGE_NOW;
    uevent << "\n";
    uevent << "POWER_SUPPLY_POWER_NOW=";
    uevent << POWER_SUPPLY_POWER_NOW;
    uevent << "\n";
    uevent << "POWER_SUPPLY_ENERGY_FULL_DESIGN=";
    uevent << POWER_SUPPLY_ENERGY_FULL_DESIGN;
    uevent << "\n";
    uevent << "POWER_SUPPLY_ENERGY_FULL=";
    uevent << POWER_SUPPLY_ENERGY_FULL;
    uevent << "\n";
    uevent << "POWER_SUPPLY_ENERGY_NOW=";
    uevent << POWER_SUPPLY_ENERGY_NOW;
    uevent << "\n";
    uevent << "POWER_SUPPLY_CAPACITY=";
    uevent << POWER_SUPPLY_CAPACITY;
    uevent << "\n";
    uevent << "POWER_SUPPLY_MODEL_NAME=";
    uevent << POWER_SUPPLY_MODEL_NAME;
    uevent << "\n";
    uevent << "POWER_SUPPLY_MANUFACTURER=";
    uevent << POWER_SUPPLY_MANUFACTURER;
    uevent << "\n";
    uevent << "POWER_SUPPLY_SERIAL_NUMBER=";
    uevent << POWER_SUPPLY_SERIAL_NUMBER;
    uevent << "\n";

    
    uevent.close();
}

int main(int argc, char **argv)
{


    sprintf(POWER_SUPPLY_NAME,"BAT0");
    sprintf(POWER_SUPPLY_STATUS,"test");
    sprintf(POWER_SUPPLY_PRESENT,"test");
    sprintf(POWER_SUPPLY_TECHNOLOGY,"Li-Po");
    // sprintf(POWER_SUPPLY_CYCLE_COUNT,"test");
    // sprintf(POWER_SUPPLY_VOLTAGE_MIN_DESIGN,"test");
    // sprintf(POWER_SUPPLY_VOLTAGE_NOW,"test");
    // sprintf(POWER_SUPPLY_POWER_NOW,"test");
    // sprintf(POWER_SUPPLY_ENERGY_FULL_DESIGN,"test");
    // sprintf(POWER_SUPPLY_ENERGY_FULL,"test");
    // sprintf(POWER_SUPPLY_ENERGY_NOW,"test");
    // sprintf(POWER_SUPPLY_CAPACITY,"test");
    // sprintf(POWER_SUPPLY_MODEL_NAME,"test");
    // sprintf(POWER_SUPPLY_MANUFACTURER,"test");
    // sprintf(POWER_SUPPLY_SERIAL_NUMBER,"test");
    
    char POWER_SUPPLY_STATUS[16];
    char timeStr[32];

    sprintf(POWER_SUPPLY_STATUS,"Unknown Status");
    sprintf(timeStr,"Unknown Time");

    //i2c_handle = wiringPiI2CSetup(0x0b);

    //sleep(5);

    int perc = readVal(0x0d);

    // sprintf(POWER_SUPPLY_NAME,readVal(0x18));
    // sprintf(POWER_SUPPLY_STATUS,readVal(0x18));
    // sprintf(POWER_SUPPLY_PRESENT,readVal(0x18));
    // sprintf(POWER_SUPPLY_TECHNOLOGY,readVal(0x18));
    sprintf(POWER_SUPPLY_CYCLE_COUNT,"%s",readValChar(0x17));
    sprintf(POWER_SUPPLY_VOLTAGE_MIN_DESIGN,"%s",readValChar(0x19));
    sprintf(POWER_SUPPLY_VOLTAGE_NOW,"%s",readValChar(0x09));
    sprintf(POWER_SUPPLY_POWER_NOW,"%s",readValChar(0x3F));
    sprintf(POWER_SUPPLY_ENERGY_FULL_DESIGN,"%s",readValChar(0x18));
    sprintf(POWER_SUPPLY_ENERGY_FULL,"%s",readValChar(0x10));
    sprintf(POWER_SUPPLY_ENERGY_NOW,"%s",readValChar(0x0F));
    sprintf(POWER_SUPPLY_CAPACITY,"%s",readValChar(0x0A));
    sprintf(POWER_SUPPLY_MODEL_NAME,"Pi-Top");
    sprintf(POWER_SUPPLY_MANUFACTURER,"Pi-Top");
    sprintf(POWER_SUPPLY_SERIAL_NUMBER,"");


    int time = readVal(0x12);
    if ((time < 1) || (time > 960)) {
            time = -1;
        }
    if (time <= 90) {
        sprintf(timeStr, "%d min remaining", time);
    }
    else {
        sprintf(timeStr, "%.1f hours remaining", (float)time / 60.0);
    }

    int current = readVal(0x0A);

    if (current > 32767)                   // status is signed 16 bit word
        current -= 65536;

    if (current < 0)
        sprintf(POWER_SUPPLY_STATUS,"Discharging");
    else if (current > 0)
        sprintf(POWER_SUPPLY_STATUS,"Charging");
        else
        sprintf(POWER_SUPPLY_STATUS,"External Power");



    printf("%s %d %s\n", POWER_SUPPLY_STATUS, perc, timeStr);

    writeFile();
    
    return 0;
}

