#ifndef SQUARE_H
#define SQUARE_H

class Square : public Shape {

    private:

        double side;

    public:

        Square(double _side, point _center) : Shape (_center) {

            side = _side;
            makeCoordinates();
        }

        void scale(double multiplier) {

            side *= multiplier;
            makeCoordinates();
        }

        double getArea() {
            return (double) side * side;
        }

        ~Square() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Square& square) {

            outputStream << "Square" << endl;
            outputStream << (const Shape&)square;
            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back({ center.x - side / 2, center.y + side / 2 });
            coordinates.push_back({ center.x + side / 2, center.y + side / 2 });
            coordinates.push_back({ center.x + side / 2, center.y - side / 2 });
            coordinates.push_back({ center.x - side / 2, center.y - side / 2 });

            rotate(angle);
        }

};


#endif // SQUARE_H
