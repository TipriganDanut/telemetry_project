#pragma once
#include "TelemetryData.hpp"

class IObserver;

class ISubject {
public:
	virtual ~ISubject() = default;

	virtual void attach(class IObserver* observer) = 0;
	virtual void detach(class IObserver* observer) = 0;
	virtual void notify(const TelemetryData& data) = 0;
};