#include "TrafficLight.h"


void TrafficLight::nextState() {


	switch (TrafficLight::state) {
	case stop:

		TrafficLight::state = readyGo;
		break;
	case readyGo:

		TrafficLight::state = go;
		break;
	case go:

		TrafficLight::state = readyStop;
		break;
	case readyStop:

		TrafficLight::state = stop;
		break;
	}
}

bool TrafficLight::isGo()
{
	return TrafficLight::state == go;
}

void TrafficLight::draw(HDC hdc) {

	int x = TrafficLight::x;
	int y = TrafficLight::y;


	RECT blackbox = { x,y, x + width, y + height };
	HBRUSH hb = CreateSolidBrush(black);
	// trenger ikke invalidate siden den tegnes ovenfor forrige trafficLight
	FillRect(hdc, &blackbox, hb);
	DeleteObject(hb);
	HGDIOBJ h = nullptr;

	trafficColor colors[3] = {};

	switch (TrafficLight::state) {
	case stop:
		colors[0] = red;
		colors[1] = gray;
		colors[2] = gray;
		break;
	case readyGo:
		colors[0] = red;
		colors[1] = yellow;
		colors[2] = gray;
		break;
	case go:
		colors[0] = gray;
		colors[1] = gray;
		colors[2] = green;
		break;
	case readyStop:
		colors[0] = gray;
		colors[1] = yellow;
		colors[2] = gray;
		break;
	}

	for (int i = 0; i < 3; i++) {
		hb = CreateSolidBrush(colors[i]);
		h = SelectObject(hdc, hb);

		int xS = x;
		int yS = y + (i * height / 3);
		int xE = x + width;
		int yE = y + width + (i * height / 3);

		Ellipse(hdc, xS, yS, xE, yE);

		// Destroy the brush
		SelectObject(hdc, h);
		DeleteObject(hb);
	}

}
