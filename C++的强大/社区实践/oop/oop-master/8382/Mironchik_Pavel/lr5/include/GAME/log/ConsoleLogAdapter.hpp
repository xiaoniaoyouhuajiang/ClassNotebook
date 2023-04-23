#pragma once

#include <iostream>

#include <GAME/log/LogAdapter.hpp>


class ConsoleLogAdapter : public LogAdapter {
public:
	virtual std::ostream& ostream() override;
};