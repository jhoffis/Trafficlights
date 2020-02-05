#pragma once
#include "TrafficLight.h"
#include "traffic.h"
#include <iostream> 
#include <queue> 

using namespace std;

class Car
{
private:
	TrafficLight* tl;
	trafficDirection direction;
	int x;
	int y;
	int width;
	int height;

	int trafficLightLinePointXY;

	bool isPassedTrafficLight(int p);
public:

	Car(trafficDirection direction, TrafficLight** tl, int trafficLightLinePointXY, int x, int y) {
		this->tl = *tl;
		this->direction = direction;
		this->x = x;
		this->y = y;
		this->width = 30;
		this->height = width / 2;
		this->trafficLightLinePointXY = trafficLightLinePointXY;
	}

	void draw(HDC hdc);
	void incrementDriving(int p);
	bool isFinished();
	int* getRearXYArray(int fillXY[]);
	int getPosition();
};