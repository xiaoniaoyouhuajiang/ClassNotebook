#ifndef drawingInterface_hpp
#define drawingInterface_hpp

#include <stdio.h>

class DrawingInterface
{
public:
    virtual ~DrawingInterface() = default;

    virtual char draw() const = 0;
};

#endif /* drawingInterface_hpp */
