#include<iostream>
#include<iomanip>
#include<unistd.h>
#include "AnalogIn.h"
#include "GPIO.h"

using namespace exploringBB;
using namespace std;

float getResistance(int adc_value) {
	float cur_voltage = adc_value * (1.80f/4096.0f); 
	float resistance = (cur_voltage * 10000.0f) / (1.80f - cur_voltage);
	return resistance;
}

float getTemperature(int adc_value) {
	float cur_voltage = adc_value * (1.80f/4096.0f);
	float diff_degreesC = (cur_voltage - 0.75f)/0.01f;
	return (25.0f + diff_degreesC);
}


int main() {
	//Pushbutton
	GPIO inGPIO(46);
	inGPIO.setDirection(INPUT);
	int state = inGPIO.getValue(); //1 if not pushed, 0 if pushed

	//LED
	GPIO outGPIO(60);
	outGPIO.setDirection(OUTPUT);

	//Resistance
	AnalogIn Vr(6);

	//Temperature
	AnalogIn Vt(0);
	
	if (state == 0) {
		cout << "Pushbutton is pressed." << endl;
		cout << "Resistance: ";
		float resistance = getResistance(Vr.readADCsample());
		if (resistance > 999.999){
			cout << std::fixed << std::setprecision(2);
			cout << std::setw(5) << resistance/1000.0f << "K Ohms" << endl;
		}
		else {
			cout << std::fixed <<std::setprecision(0);
			cout << resistance << " Ohms" << endl;
		}
		outGPIO.setValue(HIGH);
		sleep(1);
		outGPIO.setValue(LOW);
		sleep(1);
		outGPIO.setValue(HIGH);
		sleep(1);
		outGPIO.setValue(LOW);
	}
	else if (state == 1) {
		cout << "Pushbutton is not pressed." << endl;
		cout << "Temperature: ";
		float temp = getTemperature(Vt.readADCsample());
		float fahr = 32 + ((temp * 9)/5);
		cout << temp << "C (" << fahr << "F)" << endl;
		outGPIO.setValue(HIGH);
		sleep(1);
		outGPIO.setValue(LOW);
	}
		


	return 0;
}
