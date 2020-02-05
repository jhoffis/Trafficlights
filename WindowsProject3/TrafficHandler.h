#pragma once
#include <wtypes.h>
#include "TrafficLight.h"
#include "traffic.h"
#include "Car.h"
#include <iostream> 
#include <queue> 

using namespace std;

class TrafficHandler
{
private:
	const static int tlAmount = 4;
	TrafficLight* tls[tlAmount];
	queue<Car>* carlane[tlAmount];
	int spawnpoints[tlAmount][2];
	int trafficLightLinePointXY[tlAmount];
	int spawnCounter = 0;
	int tlCounter = 0;

public:
	TrafficHandler() {
		for (int i = 0; i < TrafficHandler::tlAmount; i++) {
			carlane[i] = new queue<Car>();

		}

		int start = 80;
		int extent = 360;

		tls[0] = new TrafficLight(extent, extent, go);
		tls[1] = new TrafficLight(start * 2, start, go);
		tls[2] = new TrafficLight(start * 2, extent, stop);
		tls[3] = new TrafficLight(extent, start, stop);

		trafficLightLinePointXY[0] = extent;
		trafficLightLinePointXY[1] = start + TrafficLight::height;
		trafficLightLinePointXY[2] = start * 2 + TrafficLight::width;
		trafficLightLinePointXY[3] = extent;

		spawnpoints[0][0] = extent - start;
		spawnpoints[0][1] = extent * 2;

		spawnpoints[1][0] = extent - start - 30;
		spawnpoints[1][1] = 0;

		spawnpoints[2][0] = 0;
		spawnpoints[2][1] = extent - start;

		spawnpoints[3][0] = 600;
		spawnpoints[3][1] = extent - start - 30;


	}

	void tick();
	void render(HDC hdc, RECT rect);
	void invalidateLanes(HWND hWnd);
	void increaseChance(int type);
};