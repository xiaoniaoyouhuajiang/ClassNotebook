#pragma once

class Point;
class IUnit;


class RouteHandler
{
public:
    bool handle(IUnit* unit, Point point, bool toTheEnd);
};
