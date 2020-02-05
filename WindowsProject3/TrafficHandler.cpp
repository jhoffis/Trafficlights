#include "TrafficHandler.h"

int chance = 50;

void TrafficHandler::tick() {
	// update tick count and update what is necessary as such. Have a boolean at all types that says whether or not they need to be repainted.

	TrafficHandler::spawnCounter++;
	TrafficHandler::tlCounter++;

	if (TrafficHandler::spawnCounter >= 15) {
		// legg til bil i en tilfeldig lane.

		int chosen = rand() % 100;
		int direction = rand() % (TrafficHandler::tlAmount / 2);
		if (chosen < chance) {
			//pw and pe
			direction += 2;
		}

		Car* car = new Car(trafficDirection(direction),
			&tls[direction],
			TrafficHandler::trafficLightLinePointXY[direction],
			spawnpoints[direction][0],
			spawnpoints[direction][1]);

		carlane[direction]->push(*car);

		TrafficHandler::spawnCounter = 0;
	}

	if (TrafficHandler::tlCounter > 30) {
		// oppdater trafikklys
		for (int i = 0; i < TrafficHandler::tlAmount; i++) {
			tls[i]->nextState();
		}
		TrafficHandler::tlCounter = 0;
	}

	for (queue<Car>* lane : carlane) {

		int i = 0;
		int size = lane->size();
		Car* frontCar = nullptr;

		bool updateNext = false;
		int p = -1;
		//Kjør alle biler
		while (i < size) {

			frontCar = &(lane)->front();
			frontCar->incrementDriving(p);
			p = frontCar->getPosition();

			lane->pop();
			lane->push(*frontCar);

			i++;
		}

		//Fjern biler som er ferdig
		if (size > 0) {
			frontCar = &lane->front();

			if (frontCar->isFinished()) {
				lane->pop();
			}
		}
	}

}

void TrafficHandler::render(HDC hdc, RECT rect) {
	// render traffic lights if needed
	for (int i = 0; i < TrafficHandler::tlAmount; i++) {
		//tegn alle lanes
		//int width = 300;
		//int height = 60;

		//int x = 000;
		//int y = 50;

		//RECT lane = { x,y, x + width, y + height };
		//HBRUSH hb = CreateSolidBrush(gray);
		//// trenger ikke invalidate siden den tegnes ovenfor forrige trafficLight
		//FillRect(hdc, &lane, hb);
		//DeleteObject(hb);

		/*Rectangle(hdc, x, y,
			width, height);*/

			//tegn alle trafikklys
		tls[i]->draw(hdc);

		//Tegn alle biler
		queue<Car>* carslane = carlane[i];
		int cars = 0;
		int size = carslane->size();
		Car* frontCar = nullptr;

		while (cars < size) {

			frontCar = &(carslane)->front();
			frontCar->draw(hdc);

			carslane->pop();
			carslane->push(*frontCar);

			cars++;
		}

	}

	//Render lanes with cars. Assumed to always be necessary.
}

void TrafficHandler::invalidateLanes(HWND hWnd) {

}

void TrafficHandler::increaseChance(int type)
{
	if (type == 0)
		chance += 5;
	else
		chance -= 5;
	if (chance < 0)
		chance = 0;
	if (chance > 100)
		chance = 100;
}
