#include "Car.h"


void Car::draw(HDC hdc) {

	int x = Car::x;
	int y = Car::y;

	int eX = 0;
	int eY = 0;

	COLORREF color = NULL;

	switch (direction) {
	case pn:
		color = gray;
	case ps:
		if (color == NULL)
			color = red;
		eX = x + height;
		eY = y + width;
		break;
	case pe:
		color = green;
	case pw:
		if (color == NULL)
			color = black;
		eX = x + width;
		eY = y + height;
		break;
	}

	RECT blackbox = { x,y, eX, eY };



	HBRUSH hb = CreateSolidBrush(color);
	// trenger ikke invalidate siden den tegnes ovenfor forrige trafficLight

	FillRect(hdc, &blackbox, hb);
	DeleteObject(hb);

}

void Car::incrementDriving(int p)
{
	int speed = 4;
	TrafficLight tl = *Car::tl;

	int c = getPosition();

	//First check if position is before middle square.
	if (tl.isGo() ||
		isPassedTrafficLight(p))
	{
		//Drive
		switch (direction) {
		case pn: {
			y -= speed;
			break;
		}
		case ps: {
			y += speed;
			break;
		}
		case pe: {
			x += speed;
			break;
		}
		case pw: {
			x -= speed;
			break;
		}
		}

	}


}

bool Car::isPassedTrafficLight(int p) {
	bool res = false;

	int c = getPosition();

	int margin = 12;

	switch (direction) {
	case pw:
	case pn:
		if ((c > this->trafficLightLinePointXY || c < (this->trafficLightLinePointXY - margin))
			&& (c > (p + 50) || p == -1))
			res = true;
		break;
	case pe:
	case ps:
		if ((c < this->trafficLightLinePointXY || c >(this->trafficLightLinePointXY + margin))
			&& (c < (p - 50) || p == -1))
			res = true;
		break;
	}

	return res;
}

bool Car::isFinished()
{
	bool res = false;

	int car = this->getPosition();

	switch (direction) {
	case pn: {
		if (car > 1000)
			res = true;
		break;
	}
	case ps: {
		if (car < 0)
			res = true;
		break;
	}
	case pe: {
		if (car > 1000)
			res = true;
		break;
	}
	case pw: {
		if (car < 0)
			res = true;
		break;
	}
	}

	return res;
}

int* Car::getRearXYArray(int fillXY[])
{
	int* xy = fillXY;

	switch (direction) {
	case pn:
		xy[0] = x + height;
		xy[1] = y + width;
		break;
	case ps:
	case pe:
		xy[0] = x;
		xy[1] = y;
		break;
	case pw:
		xy[0] = x + width;
		xy[1] = y + height;
		break;
	}

	return fillXY;
}

int Car::getPosition() {
	int indexx = 0;
	switch (this->direction) {
	case pn:
	case ps:
		indexx = 1;
		break;
	}

	int xy[2];
	this->getRearXYArray(xy);
	return xy[indexx];
}