#include "trapeze.hpp"

Trapeze::Trapeze(Color color, Point V1, Point V2, Point V3, Point V4) : Shape(color, V1, V2, V3, V4) {
    double angle12, angle34;
    angle12 = asin((v2.y - v1.y) / v2.distance(v1));
    if(v2.x - v1.x < eps)
	angle12 = M_PI - angle12;
    angle34 = asin((v4.y - v3.y) / v4.distance(v3));
    if(v4.x - v3.x < eps)
	angle34 = M_PI - angle34;
    if(std::abs(angle12 - angle34) > eps){
	if(std::abs(std::abs(angle12 - angle34) - M_PI) > eps){
	    double angle13, angle24;
	    angle13 = asin((v3.y - v1.y) / v3.distance(v1));
	    if(v3.x - v1.x < eps)
		angle13 = M_PI - angle13;
	    angle24 = asin((v4.y - v2.y) / v4.distance(v2));
	    if(v4.x - v2.x < eps)
		angle24 = M_PI - angle24;
	    if(std::abs(angle13 - angle24) < eps){
		std::swap(v2, v3);
		angle12 = angle13;
	    }
	    else if(std::abs(std::abs(angle13 - angle24) - M_PI) < eps) { 
		std::swap(v2, v3);
		std::swap(v3, v4);
		angle12 = angle13;
	    }
	    else{
		double angle14, angle23;
		angle14 = asin((v4.y - v1.y) / v4.distance(v1));
		if(v4.x - v1.x < eps)
		    angle14 = M_PI - angle14;
		angle23 = asin((v3.y - v2.y) / v3.distance(v2));
		if(v3.x - v2.x < eps)
		    angle23 = M_PI - angle23;
	        std::cout << angle14 << " " << angle23 << std::endl;
		if(std::abs(angle14 - angle23) < eps){
		    std::swap(v2, v4);
		    std::swap(v4, v3);
		    angle12 = angle14;
		}
		else if(std::abs(std::abs(angle14 - angle23) - M_PI) < eps) { 
		    std::swap(v2, v4);
		    angle12 = angle14;
		}else throw std::invalid_argument("Vertexes don't compoze a trapeze");
	    }
	}
	else std::swap(v3, v4);
    }
    double angle23 = asin((v3.y - v2.y) / v3.distance(v2));
    if(std::abs(angle23 - angle12) < eps || std::abs(std::abs(angle23 - angle12) - M_PI) < eps)
	throw std::invalid_argument("Vertexes don't compoze a trapeze");
    double k = v4.distance(v3) / v2.distance(v1);
    double r = v3.distance(v2);
    double angle = asin((v3.y - v2.y) / r);
    if(v3.x - v2.x < eps)
	angle = M_PI - angle;
    center.x = v2.x + r * cos(angle) / (k+1);
    center.y = v2.y + r * sin(angle) / (k+1);
}

std::ostream & Trapeze::print(std::ostream & ostream) const {
    return ostream << "Trapeze ";
}
