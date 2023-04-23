#include "ShapeGenerator.h"

custom::vector<custom::shared_ptr<Shape>> ShapeGenerator::generate(int num) {
    auto vec = new custom::vector<custom::shared_ptr<Shape>>;
    int choice;
    for(int i = 0; i < num; i++) {
        choice = (int) getRandomNumber(0, 3);
        switch(choice) {
            case CASE_ELLIPSE:
                vec->push_back(custom::shared_ptr<Shape>(randomEllipse(i)));
                break;
            case CASE_ELLIPSE_SECTOR:
                vec->push_back(custom::shared_ptr<Shape>(randomEllipseSector(i)));
                break;
            case CASE_PARALLELOGRAM:
                vec->push_back(custom::shared_ptr<Shape>(randomParallelogram(i)));
        }
    }
    return *vec;
}

Ellipse* ShapeGenerator::randomEllipse(int id) {
    return new Ellipse(new Point(getRandomNumber(0, 100), getRandomNumber(0, 100)), //центр
                getRandomNumber(0, 100), getRandomNumber(0, 100), //радиусы
                new Color((int) getRandomNumber(0, 255), (int) getRandomNumber(0, 255),
                          (int) getRandomNumber(0, 255)), id);
}

EllipseSector* ShapeGenerator::randomEllipseSector(int id) {
    return new EllipseSector(new Point(getRandomNumber(0, 100), getRandomNumber(0, 100)), //центр
                      getRandomNumber(0, 100), getRandomNumber(0, 100), //радиусы
                      0, getRandomNumber(0, M_PI / 2), //ограничители
                      new Color((int) getRandomNumber(0, 255), (int) getRandomNumber(0, 255),
                                (int) getRandomNumber(0, 255)), id);
}

Parallelogram* ShapeGenerator::randomParallelogram(int id) {
    return new Parallelogram(new Point(getRandomNumber(0, 100), getRandomNumber(0, 100)),
                      new Point(getRandomNumber(0, 100), getRandomNumber(0, 100)),
                      new Point(getRandomNumber(0, 100), getRandomNumber(0, 100)),
                      new Color((int) getRandomNumber(0, 255), (int) getRandomNumber(0, 255),
                                (int) getRandomNumber(0, 255)), id);
}

float ShapeGenerator::getRandomNumber(int from, int to) {
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> dist(from, to);
    return dist(mt);
}