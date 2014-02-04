#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "testGPIO.h"

using namespace std;

testGPIO::testGPIO() {
	this->pinnum = "1"; //Sets default pin to be at 1.
}
testGPIO::testGPIO(string pnum) {
	this->pinnum = pnum;
}
	int testGPIO::export() {
		string expstr = "/sys/class/gpio/export";
		ofstream expgpio(expstr.c_str()); //Opens gpio export file in raspberry pi.
		if(expgpio < 0) {
			cout << "EXPORTING WAS A FAIL."<< endl;
			return -1;
		}
		expgpio << this->pinnum; //Writes GPIO number.
		expgpio.close();
		return 0;
	}
	int testGPIO::unexport() {
		string unexpstr = "/sys/class/gpio/export";
		ofstream unexpgpio(unexpstr.c_str()); //Opens gpio export file in raspberry pi.
		if(unexpgpio < 0) {
			cout << "UNEXPORTING WAS A FAIL."<< endl;
			return -1;
		}
		unexpgpio << this->pinnum; //Writes GPIO number.
		unexpgpio.close();
		return 0;
	}
	int testGPIO::setdir(string dir) {
		string dirstr = "/sys/class/gpio/gpio" + this->pinnum + "/direction" ;
		ofstream dirgpio(dirstr.c_str()); //Opens gpio export file in raspberry pi.
		if(dirgpio < 0) {
			cout << "FINDING DIRECTION WAS A FAIL."<< endl;
			return -1;
		}
		dirgpio << dir //Writes GPIO number.
		dirgpio.close();
		return 0;
	}
	int testGPIO::setval(string val) {
		string valstr = "/sys/class/gpio/gpio" + this->pinnum + "/value" ;
		ofstream valgpio(valstr.c_str()); //Opens gpio export file in raspberry pi.
		if(valgpio < 0) {
			cout << "SETTING VALUE WAS A FAIL."<< endl;
			return -1;
		}
		valgpio << val //Writes GPIO number.
		valgpio.close();
		return 0;
	}
	