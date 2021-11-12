#include "event.h"
#include "eventTypes.h"

std::vector<std::shared_ptr<_EventObserver<MouseLeftClick>>> Event<MouseLeftClick>::subscribers = {};
std::vector<std::shared_ptr<_EventObserver<MouseLeftClick>>> Event<MouseLeftClick>::unsubscribers = {};
