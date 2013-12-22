#include <CostaButton.h>

CostaButton foot(A0, HIGH, true);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int event = foot.checkEvent();
	
	if (event != NONE_EVENT)
	{
		Serial.print("Event: ");
		Serial.print(event);
		Serial.print(", state:");
		Serial.print(foot.getState());
		Serial.print(", last state:");
		Serial.println(foot.getLastState());
	}
}