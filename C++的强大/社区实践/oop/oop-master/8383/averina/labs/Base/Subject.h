#ifndef OOP_SUBJECT_H
#define OOP_SUBJECT_H


#include <vector>
#include "IObserver.h"

// Subject -- класс подписчиков. Нужен для подписки базы на юнитов.


class Subject
{
public:
    void addFollower(IObserver* follower);
//    void deleteFollower(IObserver* follower);
    void notice();

private:
    std::vector<IObserver*> followers; // список подписчиков
};




#endif //OOP_SUBJECT_H
