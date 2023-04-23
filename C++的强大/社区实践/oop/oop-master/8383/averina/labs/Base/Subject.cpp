
#include "Subject.h"


void Subject::addFollower(IObserver *follower)
{
    followers.push_back(follower);
}
//
//void Subject::deleteFollower(IObserver *follower)
//{
//    auto i = followers.begin();
//    while(i != followers.end())
//        if (*i == follower){
//            followers.erase(i);
//            return;
//        }
//}

void Subject::notice()
{
    for (IObserver* follower : followers)
        follower->update(this);
}