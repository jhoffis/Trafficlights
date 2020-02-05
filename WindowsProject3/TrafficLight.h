#pragma once
#include <wtypes.h>
#include "traffic.h"

class TrafficLight
{
    
private:
    int x, y;
    int state;

public:

    static const int width = 30;
    static const int height = 3 * width + width / 5;

    TrafficLight() {
        x = 0;
        y = 0;
        state = stop;
    }
    TrafficLight(int posX, int posY, trafficState startState) {
        x = posX;
        y = posY;
        state = startState;
    }
    void draw(HDC hdc);
    void nextState();
    bool isGo();
};
