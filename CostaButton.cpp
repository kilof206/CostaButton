#include "CostaButton.h"

CostaButton::CostaButton(int v_pin, int v_normalValue, boolean v_pullUp)
{
	pin = v_pin;
	pinMode(pin, INPUT);
	
	if (v_pullUp)
		digitalWrite(pin, HIGH);

	normalValue = v_normalValue;

	debouceDelay = 20;
	holdDelay = 1000;
	holdedDelay = 200;
	
	lastTempValue = normalValue;
	changeTempValueTime = 0;
	
	lastValue = normalValue;
	value = normalValue;
	
	lastState = OFF;
	state = OFF;
	
	holdStartTime = 0;
}

int CostaButton::checkEvent()
{
	int result = NONE_EVENT;
	
	int tempValue = digitalRead(pin);
	
	if (tempValue != lastTempValue)
		changeTempValueTime = millis();
	
	lastTempValue = tempValue;
	
	if ((millis() - changeTempValueTime) > debouceDelay) 
	{
		// Jakikolwiek by to nie był stan, jest on dłużej niż czas opóźnienia 
		// migotania, więc jest to faktyczny bieżący stan przycisku.
		value = tempValue;
	}
	
	if (lastValue != value)
	{
		lastValue = value;
		lastState = state;
		
		if (value == normalValue)
		{
			state = OFF;
			result = RELEASED_EVENT;
		}
		else
		{
			state = ON;
			result = PRESSED_EVENT;
			
			holdStartTime = millis();
		}
	}
	
	// Sprawdzenie przytrzymania przycisku (HOLD)
	if (state == ON && (millis() - holdStartTime) > holdDelay)
	{
		lastState = state;

		state = HOLD;

		holdStartTime = millis();

		result = HOLD_EVENT;
	}
	// Sprawdzenie dalszego przytrzymania przycisku (tzw. HOLDED)
	else if (state == HOLD && (millis() - holdStartTime) > holdedDelay)
	{
		// Zerujemy licznik HOLD, aby wykryć jeszcze dłuższe przytrzymanie przycisku (tzw. HOLDED)
		holdStartTime = millis();

		// Ustawienie zdarzenia przycisku (do obsłużenia w części logicznej)
		result = HOLDED_EVENT;
	}
	
	return result;
}

int CostaButton::getState()
{
	return state;
}

int CostaButton::getLastState()
{
	return lastState;
}

void CostaButton::setDebounceDelay(unsigned long v_debouceDelay)
{
	debouceDelay = v_debouceDelay;
}

void CostaButton::setHoldDelay(unsigned long v_HoldDelay)
{
	holdDelay = v_HoldDelay;
}

void CostaButton::setHoldedDelay(unsigned long v_HoldedDelay)
{
	holdedDelay = v_HoldedDelay;
}
