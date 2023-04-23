#ifndef RHOMBUS_H
#define RHOMBUS_H

class Rhombus : public Shape {

    private:
        double minDiagonal;
        double maxDiagonal;

    public:

        Rhombus(double _minDiagonal, double _maxDiagonal, point _center) : Shape(_center) {

            if (_minDiagonal < _maxDiagonal) {

                minDiagonal = _minDiagonal;
                maxDiagonal = _maxDiagonal;

            } else {
                maxDiagonal = _minDiagonal;
                minDiagonal = _maxDiagonal;
            }

            makeCoordinates();
        }

        void scale(double multiplier) {

            maxDiagonal *= multiplier;
            minDiagonal *= multiplier;
            makeCoordinates();
        }

        double getArea() {
            return (double)0.5 * minDiagonal * maxDiagonal;
        }

        ~Rhombus() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Rhombus& rhombus) {

            outputStream << "Rhombus" << endl;
            outputStream << (const Shape&)rhombus;

            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back(center);

            coordinates.push_back({ center.x - maxDiagonal / 2, center.y});
            coordinates.push_back({ center.x, center.y + minDiagonal / 2});
            coordinates.push_back({ center.x + maxDiagonal / 2, center.y});
            coordinates.push_back({ center.x, center.y - minDiagonal / 2});

            rotate(angle);
        }
};


#endif // RHOMBUS_H
