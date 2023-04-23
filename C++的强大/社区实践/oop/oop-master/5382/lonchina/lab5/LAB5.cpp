#include <iostream>
#include <vector>
#include "Figures/AbstractShape.h"
#include "Figures/Trapezium.h"
#include "Factories/RectangleFactory.h"
#include "Factories/CircleFactory.h"
#include "Factories/TrapeziumFactory.h"
#include <ctime>
#include <cstdlib>
#include <memory>

using namespace std;

void generator(vector< shared_ptr<AbstractShape> > &List) {
	RectangleFactory* rectangle_factory = new RectangleFactory;
	CircleFactory*  circle_factory = new CircleFactory;
	TrapeziumFactory*  trapezium_factory = new TrapeziumFactory;

	for (int i = 0; i < 10000; ++i) {
		int chooseFigure = rand() % 3;
		switch (chooseFigure) {
		case 0: {
					vector<Point> rectangleCoords;
					Point coord;

					Point center;
					center.x = rand() % 10;
					center.y = rand() % 10;

					for (int j = 0; j < 3; ++j) {
						coord.x = rand() % 10;
						coord.y = rand() % 10;
						rectangleCoords.push_back(coord);
					}

					shared_ptr<AbstractShape> aaa(rectangle_factory->createShape(rectangleCoords, center, 3, "rectangle"));
					List.push_back(aaa);
					break;
		}
		case 1: {
					vector<Point> circleCoords;
					Point coord;

					Point center;
					center.x = rand() % 10;
					center.y = rand() % 10;

					for (int j = 0; j < 2; ++j) {
						coord.x = rand() % 10;
						coord.y = rand() % 10;
						circleCoords.push_back(coord);
					}
					shared_ptr<AbstractShape> aaa(circle_factory->createShape(circleCoords, center, 2, "circle"));
					List.push_back(aaa);
					break;
		}
		case 2: {
					vector<Point> trapeziumCoords;
					Point coord;

					Point center;
					center.x = rand() % 10;
					center.y = rand() % 10;

					for (int j = 0; j < 4; ++j) {
						coord.x = rand() % 10;
						coord.y = rand() % 10;
						trapeziumCoords.push_back(coord);
					}
					shared_ptr<AbstractShape> aaa(circle_factory->createShape(trapeziumCoords, center, 2, "circle"));
					break;
		}
		default: {
					 break;
		}
		}
	}
}

void menu()
{
	// �������������� ������ �����
	vector< shared_ptr<AbstractShape> > sss, ppp, lll;
	srand(time(nullptr));

	// �����
	int choose = 0;
	do {
		cout << "1. Non-modyfying algorithm" << endl;
		cout << "2. Modyfying algorithm" << endl;
		cout << "3. Output figures" << endl;
		cout << "0. EXIT" << endl;
		cin >> choose;
		switch (choose) {
		case 1: {
					// ���������� ��� ������
					generator(sss);
					generator(ppp);

					// ��������� �������� �� ��������
					sort(sss.begin(), sss.end(), [](shared_ptr<AbstractShape> a, shared_ptr<AbstractShape> b) {
						return a.get()->getArea() > b.get()->getArea();
					});
					sort(ppp.begin(), ppp.end(), [](shared_ptr<AbstractShape> a, shared_ptr<AbstractShape> b) {
						return a.get()->getArea() > b.get()->getArea();
					});

					// ��������� ����� �� ������ ����������� �� �������
					bool flag = false;
					for (int i = 0; i < sss.size() && i < ppp.size(); ++i) {
						if (sss[i].get()->getArea() != ppp[i].get()->getArea()) {
							flag = true;
						}
					}
					if (flag) {
						cout << "Lists of figures not equal;(" << endl;
					}
					else {
						cout << "Lists of figures are equal;)" << endl;
					}
					break;
		}
		case 2: {
					// ���������� ������
					generator(lll);

					// ������ �������, � ������� ��������� ��������
					unsigned n = 0;
					cout << "Enter range of sorting: ";
					cin >> n;

					// ��������� �� �����������
					sort(lll.begin(), lll.begin() + n, [](shared_ptr<AbstractShape> a, shared_ptr<AbstractShape> b) {
						return a.get()->getArea() > b.get()->getArea();
					});
					break;
		}
		case 3: {
					for (auto fig : sss) {
						cout << fig.get()->getArea() << ' ';
					}
					cout << endl;

					for (auto fig : ppp) {
						cout << fig.get()->getArea() << ' ';
					}
					cout << endl;

					for (auto fig : lll) {
						cout << fig.get()->getArea() << ' ';
					}
					cout << endl;
					break;
		}
		case 0: {
					return;
		}
		default: {
					 cout << "Your choice is wrong ;( Try again";
		}
		}
	} while (choose);
}

int main() {
	menu();
	return EXIT_SUCCESS;
};