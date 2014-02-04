//We need to set up the pins in bash with the pi!
#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>

using namespace std;

class testGPIO {
	int main() {
		int export(); //Exports the pin.
		int unexport(); //Unexports pin.
		//I didn't set the pin Direction because that didn't seem like something we needed to do.
		int setval(); //Sets the pin value.
		//I also didn't return the value because it didn't seem important.
	}
}