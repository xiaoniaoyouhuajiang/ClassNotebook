#include "ellipse.h"

Ellipse::Ellipse() : Shape (),_OYRadius(1.0),_OXRadius(1.0){updateCoords();}

Ellipse::Ellipse(double x,double y,double OXRadius,double OYRadius, Color color, double angle) :
    Shape(x,y,color,angle),_OYRadius(OYRadius),_OXRadius(OXRadius){updateCoords();}

