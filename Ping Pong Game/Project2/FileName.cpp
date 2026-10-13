#include "raylib.h"
#pragma once

class AnalogClock {

public: 
		AnalogClock(int size, Vector2 position) :size(size), position(position) {};
		void Draw() const;
	

private:
		int size;
		Vector2 position;
	
};

Color Drak_Grey = { 45,45,45,255 };
Color Light_Grey = { 229,229,229,255 };

void AnalogClock::Draw() const
{
	DrawCircleV(position, size, Drak_Grey);

}
