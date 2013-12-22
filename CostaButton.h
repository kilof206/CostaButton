#ifndef CostaButton_h
#define CostaButton_h

#include "arduino.h"

// Button states
#define OFF 0
#define ON 1
#define HOLD 2

// Button events
#define NONE_EVENT 0
#define PRESSED_EVENT 1
#define RELEASED_EVENT 2
#define HOLD_EVENT 3
#define HOLDED_EVENT 4


class CostaButton
{
	public:
		CostaButton(int v_pin);
		
		int checkEvent();
		int getState();
		int getLastState();
		
		void setDebounceDelay(unsigned long v_debouceDelay);
		void setHoldDelay(unsigned long v_HoldDelay);
		void setHoldedDelay(unsigned long v_HoldedDelay);

	private:
		int pin;
		int debouceDelay;
		int holdDelay;
		int holdedDelay;
		
		int lastTempValue;
		unsigned long changeTempValueTime;
		
		int lastValue;
		int value;
		
		int lastState;
		int state;
		
		unsigned long holdStartTime;
};

#endif
