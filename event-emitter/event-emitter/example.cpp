#include <iostream>
#include "event.h"
#include "eventTypes.h"

int main() {
	EventObserver<MouseLeftClick> f;
	f.set([](MouseLeftClick e) {std::cout << "x: " << e.x << ", y: " << e.y << ", shift: " << e.shiftKeyPressed << std::endl;  });
	Event<MouseLeftClick>::emit({ 1, 2, true });
	Event<MouseLeftClick>::emit({ 4, 5, false });
	f.unset();
	Event<MouseLeftClick>::emit({ 1, 2, true });
}
