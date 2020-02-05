#pragma once
#include <wtypes.h>
enum trafficColor { red = RGB(255, 0, 0), black = RGB(0, 0, 0), gray = RGB(100, 100, 100), yellow = RGB(255, 255, 0), green = RGB(0, 255, 0) };
enum trafficState { stop = 0, readyGo = 1, go = 2, readyStop = 3 };
enum trafficDirection {pn = 0, ps = 1, pe = 2, pw = 3 };
