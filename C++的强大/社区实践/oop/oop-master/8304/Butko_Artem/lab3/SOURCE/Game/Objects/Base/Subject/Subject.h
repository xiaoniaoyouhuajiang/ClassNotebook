//
// Created by Artem Butko on 15/05/2020.
//

#ifndef OOP_NEW_SUBJECT_H
#define OOP_NEW_SUBJECT_H

#include <vector>
#include "../Observer/IObserver.h"

/* Subject -- класс подписчиков. Нужен для подписки базы на юнитов.
 */

class Subject
{
public:
    void addFollower(IObserver* follower);
    void deleteFollower(IObserver* follower);
    void notice();

private:
    std::vector<IObserver*> followers;
};


#endif //OOP_NEW_SUBJECT_H
