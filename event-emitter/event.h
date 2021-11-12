#pragma once
#include <functional>
#include <vector>
#include <memory>

template <class T>
class _EventObserver {
public:
	std::function<void(T&)> f;
	_EventObserver(std::function<void(T)> f) {
		this->f = f;
	}
};

template <typename T>
class Event {
private:
	static std::vector<std::shared_ptr<_EventObserver<T>>>   subscribers;
	static std::vector<std::shared_ptr<_EventObserver<T>>> unsubscribers;
public:
	static void subscribe(std::shared_ptr<_EventObserver<T>> obv) {
		subscribers.push_back(obv);
	}
	static void unsubscribe(std::shared_ptr<_EventObserver<T>> obv) {
		unsubscribers.push_back(obv);
	}
	static void emit(T t) {
		for (const auto& obv : subscribers)
			if (std::find(unsubscribers.begin(), unsubscribers.end(), obv) == unsubscribers.end())
				obv->f(t);
		for (const auto& obv : unsubscribers)
			subscribers.erase(std::find(subscribers.begin(), subscribers.end(), obv));
		unsubscribers = {};
	}
	static void clear() {
		subscribers = {};
		unsubscribers = {};
	}
};

template <class T>
class EventObserver {
	void subscribe() {
		Event<T>::subscribe(observer);
	}
	void unsubscribe() {
		Event<T>::unsubscribe(observer);
		observer = nullptr;
	}
	std::shared_ptr<_EventObserver<T>> observer;
public:
	~EventObserver() {
		if (observer)
			unsubscribe();
	}
	void set(std::function<void(T)> f) {
		observer = std::make_shared<_EventObserver<T>>(f);
		subscribe();
	}
	void unset() {
		unsubscribe();
	}
	bool isSet() {
		return observer != nullptr;
	}
};
