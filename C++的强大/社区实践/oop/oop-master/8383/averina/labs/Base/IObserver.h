
#ifndef OOP_IOBSERVER_H
#define OOP_IOBSERVER_H

class Subject;

#include "Subject.h"

/* IObserver -- интерфейс для отправки обновления состояния наблюдателю.
 */

class IObserver
{
public:
    virtual void update(Subject* subject) = 0;
};


#endif //OOP_IOBSERVER_H
