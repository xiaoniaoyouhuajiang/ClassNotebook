#include <GAME/log/ConsoleLogAdapter.hpp>

std::ostream& ConsoleLogAdapter::ostream() {
	return std::cout;
}