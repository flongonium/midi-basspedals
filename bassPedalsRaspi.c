/*
 * bassPedalsRaspi.c
 * 
 * Copyright 2020  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <wiringPi.h>
#define DEBOUNCE 1500


const int keyVelocity = 127;

struct key {
    int pin;
    int midiKey;
    int debounce;
    int keySent;
    };
    
/* THESE PINS REPRESENT THE PHYSICAL LAYOUT --> gpio readall
struct key keys[] =
{
    {40, 24, 0, 0}
    ,{38, 23, 0, 0}
    ,{37, 22, 0, 0}
    ,{36, 21, 0, 0}
    ,{35, 20, 0, 0}
    ,{33, 19, 0, 0}
    ,{32, 18, 0, 0}
    ,{31, 17, 0, 0}
    ,{29, 16, 0, 0}
    ,{26, 15, 0, 0}
    ,{24, 14, 0, 0}
    ,{23, 13, 0, 0}
    ,{22, 12, 0, 0}
    ,{0, 0, 0, 0}
    };
*/

/* THESE PINS REPRESENT THE wiringPi LAYOUT --> gpio readall */
struct key keys[] =
{
    {29, 24, 0, 0}
    ,{28, 23, 0, 0}
    ,{27, 22, 0, 0}
    ,{26, 21, 0, 0}
    ,{25, 20, 0, 0}
    ,{24, 19, 0, 0}
    ,{23, 18, 0, 0}
    ,{22, 17, 0, 0}
    ,{21, 16, 0, 0}
    ,{6, 15, 0, 0}
    ,{5, 14, 0, 0}
    ,{4, 13, 0, 0}
    ,{1, 12, 0, 0}
    ,{0, 0, 0, 0}
    };

void keySetup() {    
    for(int i=0; keys[i].pin !=0; ++i) {
	pinMode(keys[i].pin, INPUT);
	}
    }

void keyEvents() {
//    int byte1;
//    int byte2;
//    int byte3;
    FILE * fp;
    int value;
    
    for(int i=0; keys[i].pin != 0; ++i) {
	value = digitalRead(keys[i].pin);
	
	if(keys[i].debounce == 0) {					// Key has been off
	    if(value == HIGH) {						// Key is now on
		//SEND NOTE ON TO VIRTUAL USB
		fp = fopen("data_output_test.txt", "a+");
		fprintf(fp, "action 1 %d \n", i);
		fclose(fp); 
		
		keys[i].keySent = keys[i].midiKey; 			// + keyOffset;
		keys[i].debounce = DEBOUNCE;
		}
		else {							// Key has been on
		    if(value == LOW) {					// Key has gone off
			if(--keys[i].debounce == 0) {
			    //SEND NOTE OFF TO VIRTUAL USB
			    fp = fopen("data_output_test.txt", "a+");
			    fprintf(fp, "action 2 %d \n", i);
			    fclose(fp);
			    }
			    else {					// Key has not gone off
				keys[i].debounce = DEBOUNCE;
				}
			}
		    }
	    }
	}
    }

int main() {
    wiringPiSetup();
    
    keySetup();
    
    while(1) {
	keyEvents();
	}
    return(0);
    }
