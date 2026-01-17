#pragma once
#include "TelemetryData.hpp"

class IObserver {
	public:

	virtual ~IObserver() = default;

	virtual void update(const TelemetryData& data) = 0;
};