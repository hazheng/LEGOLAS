//We need to set up the pins in bash with the pi!
#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>

using namespace std;

class testGPIO {
	int main() {
		int export(); //Exports the pin.
		int unexport(); //Unexports pin.
		int setdir(); //Sets pin directio(in/out).
		int setval(); //Sets the pin value.
		//I didn't return the pin value because it didn't seem important.
	}
}