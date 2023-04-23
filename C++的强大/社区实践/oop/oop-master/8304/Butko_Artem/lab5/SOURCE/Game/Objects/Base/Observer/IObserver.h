//
// Created by Artem Butko on 15/05/2020.
//

#ifndef OOP_NEW_IOBSERVER_H
#define OOP_NEW_IOBSERVER_H

class Subject;

/* IObserver -- интерфейс для отправки обновления состояния наблюдателю.
 */

class IObserver
{
public:
    virtual void update(Subject* subject) = 0;
};


#endif //OOP_NEW_IOBSERVER_H
