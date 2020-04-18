#ifndef MBASELISTENER_HPP
#define MBASELISTENER_HPP

#include "MBaseObject.hpp"
#include <map>
#include <list>

template <typename EventsList, typename ...CallbackArgs>
class MBaseListener  : 
	public MBaseObject {
public:
	using MFuncType = void(CallbackArgs... e);
	using MFuncPtr = MFuncType*;
	using EventsListType = EventsList;
private:
	std::map<EventsListType, std::list<MFuncPtr>> events;
public:
	template <EventsListType index>
	void on(MFuncPtr callback) noexcept {
		this->events[index].push_back(callback);
	}

	template<EventsListType index>
	void exec(CallbackArgs... args) noexcept {
		for (const auto& e : this->events[index])
			e(args...);
	}
	
	template <EventsListType index>
	void clear() noexcept {
		this->events[index].clear();
	}

	virtual const char* toString() const noexcept { return "BaseListener"; }

	virtual ~MBaseListener() noexcept = default;
protected:
	MBaseListener() noexcept {}
};

//sample
/*
struct MyEvent {
	int i;
	char c;
	bool b;
};

enum EventsList {
	onFirst, onSecond, onThird
};

class MyListener : public MBaseListener<EventsList, MyEvent> {
public:
	MyListener() {}

	~MyListener() = default;
};

class SomeClass {
	MyEvent event;
	MyListener listener;
public:
	SomeClass() :
		event( { 100, 'A', true } ) { }

	~SomeClass() = default;

	void first() {
		printf("First\t");
		this->event.i = 200;
		this->listener.exec<EventsList::onFirst>(event);
	}

	void second() {
		printf("Second\t");
		this->event.c = 'B';
		listener.exec<EventsList::onSecond>(event);
	}

	void third() {
		printf("Third\t");
		this->event.b = false;
		listener.exec<EventsList::onThird>(event);
	}

	MyListener& getListener() { return this->listener; }
};

void test() {
	SomeClass someClass;

	someClass.getListener().on
		<EventsList::onFirst>
		([](MyEvent e) {
			printf("onFirst: %d\t%d\t%d", e.i, e.c, e.b);
		});

	someClass.first();
	someClass.second();
	someClass.third();
}
*/
#endif //!MBASELISTENER_HPP