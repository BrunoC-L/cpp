#include <iostream>
#include "event.h"

struct MouseLeftClickEventData {
	int x;
	int y;
	bool shiftKeyPressed;
};
using MouseLeftClickEvent = Event<MouseLeftClickEventData>;

int main() {
	std::cout << std::boolalpha;
	auto print = [](const MouseLeftClickEvent::Data& e) {std::cout << "x: " << e.x << ", y: " << e.y << ", shift: " << e.shiftKeyPressed << std::endl;  };
	MouseLeftClickEvent::Observer observer1;
	observer1.set(print);
	EVENT(MouseLeftClickEvent, 1, 1, true).emit();// calls observer1

	// unsubscription is automatic when the object is deleted!
	{
		MouseLeftClickEvent::Observer observer2(print);
		EVENT(MouseLeftClickEvent, 2, 2, false).emit(); // calls observer 1 & 2
	}
	observer1.unset(); // otherwise you can manually unset

	EVENT(MouseLeftClickEvent, 3, 3, false).emit(); // calls nothing

}
