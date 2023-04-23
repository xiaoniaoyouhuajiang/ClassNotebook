#include "SignalMaker.h"

SignalMaker::SignalMaker()
{

}


void SignalMaker::makeStateChangeSignal(Kind kind) {
    emit stateChangeSignal(kind);
}
