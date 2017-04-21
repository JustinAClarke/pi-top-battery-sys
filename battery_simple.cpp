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
#include <wiringPiI2C.h>

//format %status %percentage %remaining

/**
POWER_SUPPLY_NAME=BAT0  
statusStr=Discharging  
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

void printNice(char val[32])
{
  printf("\n%s\n",val);
}

int readVal(int loc){
    int res = wiringPiI2CReadReg8(i2c_handle, loc);
//     int res = 0;
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

int main(int argc, char **argv)
{
    char statusStr[16];
    char timeStr[32];

    sprintf(statusStr,"Unknown Status");
    sprintf(timeStr,"Unknown Time");

    i2c_handle = wiringPiI2CSetup(0x0b);

    sleep(3);

    int perc = readVal(0x0d);

    //printf(readValChar(0x17));
    //printf("\n");

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
        sprintf(statusStr,"Discharging");
    else if (current > 0)
        sprintf(statusStr,"Charging");
        else
        sprintf(statusStr,"External Power");



    printf("%s: %d %s\n", statusStr, perc, timeStr);

    
    return 0;
}

