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
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <wiringPiI2C.h>

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

FILE *ueventFile;

int readVal(int loc){
    int res = 0;
    res = wiringPiI2CReadReg8(i2c_handle, loc);
    //int res = 0;
    if (loc == 0x0A) {	// convert to signed integer
//         if (res > 32767)
//             res -= 65536;
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

    char POWER_SUPPLY_STATUS[16];
    int POWER_SUPPLY_PRESENT = 0;
    char timeStr[32];

    sprintf(POWER_SUPPLY_STATUS,"Unknown Status");
    sprintf(timeStr,"Unknown Time");

    i2c_handle = wiringPiI2CSetup(0x0b);

    sleep(3);

    int perc = readVal(0x0d);

   // printf(readValChar(0x17));
    // sprintf(POWER_SUPPLY_NAME,readVal(0x18));
    // sprintf(POWER_SUPPLY_STATUS,readVal(0x18));
    // sprintf(POWER_SUPPLY_PRESENT,readVal(0x18));
    // sprintf(POWER_SUPPLY_TECHNOLOGY,readVal(0x18));





    int current = readVal(0x0A);

    if (current > 32767)                   // status is signed 16 bit word
        current -= 65536;

    if (current < 0)
        sprintf(POWER_SUPPLY_STATUS,"Discharging");
    else if (current > 0){
        sprintf(POWER_SUPPLY_STATUS,"Charging");
	POWER_SUPPLY_PRESENT=1;
    }
    else
        sprintf(POWER_SUPPLY_STATUS,"External Power");

    int time = 0;
    if (strcmp(POWER_SUPPLY_STATUS,"Charging") == 0)
      time = readVal(0x13);

    else if (strcmp(POWER_SUPPLY_STATUS,"Discharging") == 0)
      time = readVal(0x12);
    
    if ((time < 1) || (time > 960)) {
            time = -1;
        }
    if (time <= 90) {
        sprintf(timeStr, "%d min remaining", time);
    }
    else {
        sprintf(timeStr, "%.1f hours remaining", (float)time / 60.0);
    }

    printf("%s %d %s\n", POWER_SUPPLY_STATUS, perc, timeStr);
  
    char tmpStr[64];
    mkdir("/opt/pi-top-battery-sys/BAT0/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    ueventFile = fopen("/opt/pi-top-battery-sys/BAT0/uevent","w+");


    fprintf(ueventFile,"POWER_SUPPLY_NAME=BAT0\n");

    fprintf(ueventFile,"POWER_SUPPLY_STATUS=%s\n",POWER_SUPPLY_STATUS);
    fprintf(ueventFile,"POWER_SUPPLY_PRESENT=%i\n",POWER_SUPPLY_PRESENT);
    fprintf(ueventFile,"POWER_SUPPLY_TECHNOLOGY=Li-ion\n");
    fprintf(ueventFile,"POWER_SUPPLY_CYCLE_COUNT=%i\n",readVal(0x17));
    fprintf(ueventFile,"POWER_SUPPLY_VOLTAGE_MIN_DESIGN=%i\n",readVal(0x19));
    

    fprintf(ueventFile,"POWER_SUPPLY_VOLTAGE_NOW=%i\n",readVal(0x09));
    fprintf(ueventFile,"POWER_SUPPLY_POWER_NOW=%i\n",readVal(0x3F));
    fprintf(ueventFile,"POWER_SUPPLY_ENERGY_FULL_DESIGN=%i\n",readVal(0x18));
    fprintf(ueventFile,"POWER_SUPPLY_ENERGY_FULL=%i\n",readVal(0x10));
    fprintf(ueventFile,"POWER_SUPPLY_ENERGY_NOW=%i\n",readVal(0x0F));
    fprintf(ueventFile,"POWER_SUPPLY_CAPACITY=%i\n",readVal(0x0A));
    fprintf(ueventFile,"POWER_SUPPLY_MODEL_NAME=Pi-Top\n");
    fprintf(ueventFile,"POWER_SUPPLY_MANUFACTURER=Pi-Top\n");
    fprintf(ueventFile,"POWER_SUPPLY_SERIAL_NUMBER=Pi-Top\n");

    fflush(ueventFile);

//     sprintf(POWER_SUPPLY_CYCLE_COUNT,readValChar(0x17));
//     sprintf(POWER_SUPPLY_VOLTAGE_MIN_DESIGN,readValChar(0x19));
//     sprintf(POWER_SUPPLY_VOLTAGE_NOW,readValChar(0x09));
//     sprintf(POWER_SUPPLY_POWER_NOW,readValChar(0x3F));
//     sprintf(POWER_SUPPLY_ENERGY_FULL_DESIGN,readValChar(0x18));
//     sprintf(POWER_SUPPLY_ENERGY_FULL,readValChar(0x10));
//     sprintf(POWER_SUPPLY_ENERGY_NOW,readValChar(0x0F));
//     sprintf(POWER_SUPPLY_CAPACITY,readValChar(0x0A));
//     sprintf(POWER_SUPPLY_MODEL_NAME,"Pi-Top");
//     sprintf(POWER_SUPPLY_MANUFACTURER,"Pi-Top");
//     sprintf(POWER_SUPPLY_SERIAL_NUMBER,"");
   
    
    return 0;
}

