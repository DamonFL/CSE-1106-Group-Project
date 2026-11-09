/*
 * GroupProject.c
 * 
 * Copyright 2026  <dfl1437@DamonLangford>
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
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

void displayLight(int ledLight){
	gpioInitialise();
	gpioSetMode(PIN, PI_OUTPUT);
	
	gpioWrite(PIN,ledLight);
	getchar();
	
	gpioTerminate();
}

void createGUI(double memoryUsage, double storageUsage, char statusWarning[], int ledLight, double threshold){
	//Data Checks
	if (memoryUsage >= threshold){
		strcpy(statusWarning, "WARNING");
		ledLight = 1;
	}
	if(storageUsage >= threshold){
		strcpy(statusWarning, "WARNING");
		ledLight = 1;
	}
	char light[] = "OFF";
	if (ledLight == 1){
		strcpy(light, "ON");
	}
	
	//Display Category then data
	printf("Memory Usage  Storage Usage  StatusWarning  LED Light\n");// category seperated by 2 spaces
	printf("-----------------------------------------------------\n");
	printf("%-14.2f%-14.2f%14s%8s\n", memoryUsage,storageUsage, statusWarning, light);
	displayLight(ledLight);
}

int main(int argc, char **argv)
{
	double warningThreshold = 80.0;
	double memoryUsage = 0.0;
	double storageUsage = 0.0;
	char statusWarning[] = "HEALTHY";
	int ledLight = 0;
	
	//Test Cases
	//Test 1: normal running	HEALTHY
	memoryUsage = 25.0;
	storageUsage = 45.6;

	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//Test 2: high memory usage, normal storage usage	WARNING
	memoryUsage = 100.0;
	storageUsage = 45.6;

	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//test 3: normal memory usage, high storage usage	WARNING
	memoryUsage = 25.0;
	storageUsage = 100.0;
	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//test 4: no memory usage, no storage usage		HEALTHY
	memoryUsage = 0.0;
	storageUsage = 0.0;
	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//test 5: high memory usage, high storage usage		WARNING
	memoryUsage = 100.0;
	storageUsage = 100.0;

	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//test 6: memory usage on threshold, normal storage usage	WARNING
	memoryUsage = 80.0;
	storageUsage = 45.6;

	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);
	//test 7: normal memory usage, storage usage on threshold	WARNING
	memoryUsage = 25.0;
	storageUsage = 80.0;

	createGUI(memoryUsage, storageUsage, statusWarning, ledLight, warningThreshold);

	return 0;
}

