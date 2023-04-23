//
//  Point.h
//  WORKPLEASE
//
//  Created by user on 30.03.17.
//  Copyright © 2017 user. All rights reserved.
//

#ifndef Point_h
#define Point_h
class Point
{
public:
    double X,Y;
    Point();
    Point(double xx, double yy);
    double distance(const Point &other) const;
    void rotate(double angle);
};

#endif /* Point_h */
