#include "EndStepMessage.h"



EndStepMessage::EndStepMessage()
{
}


EndStepMessage::~EndStepMessage()
{
}

std::string EndStepMessage::toString()
{
	std::ostringstream os;
	os << "End of the move\n";
	return os.str();
}
