#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

class Parallelogram : public Shape {

    private:

        double height;
        double lenght;
        double rLenght;

    public:

        Parallelogram(double side, double _side, double _angle, point _center) : Shape (_center) {

            height = side * sin(_angle);
            rLenght = side * cos(_angle);
            lenght = _side - rLenght;

            makeCoordinates();
        }

        void scale(double multiplier) {

            height *= multiplier;
            lenght *= multiplier;
            rLenght *= multiplier;

            makeCoordinates();
        }

        double getArea () {
            return (double)0.5 * height * lenght;
        }

        ~Parallelogram() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Parallelogram& Pargrm) {

            outputStream << "Parallelogram" << endl;
            outputStream << (const Shape&)Pargrm;

            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back({ center.x - lenght / 2, center.y + height / 2 });
            coordinates.push_back({ center.x + rLenght + lenght / 2, center.y + height / 2 });
            coordinates.push_back({  center.x + lenght / 2, center.y - height / 2 });
            coordinates.push_back({ center.x - rLenght - lenght / 2, center.y - height / 2 });

            rotate(angle);
        }
};


#endif // PARALLELOGRAM_H
