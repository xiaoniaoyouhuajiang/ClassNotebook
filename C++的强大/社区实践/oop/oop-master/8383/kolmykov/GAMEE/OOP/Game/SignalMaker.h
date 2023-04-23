#ifndef SIGNALMAKER_H
#define SIGNALMAKER_H
#include "Kind.h"
#include <QObject>


class SignalMaker : public QObject
{
    Q_OBJECT
public:
    SignalMaker();
    void makeStateChangeSignal(Kind kind);

signals:
    void stateChangeSignal(Kind kind);
};

#endif // SIGNALMAKER_H
