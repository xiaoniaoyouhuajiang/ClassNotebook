#include <iostream>

int id = 1;

class Shape{
protected:
	int mID;
	int mColor;
	int mAngle;
public:
	Shape(): mID (id++), mColor (0), mAngle(0) {}
	~Shape() {}

	virtual void move(int x, int y) = 0;
	virtual bool zoom(int coef) = 0;			// conventionally success is 'false', failure - 'true'

	void rotate(int alpha){
		if(alpha >= 360 || alpha < 0)
			alpha = alpha % 360;     				// negative mod positive yields negative
		if(alpha < 0)
			alpha += 360;
		mAngle = (mAngle + alpha) % 360;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Rotated by " << alpha << " degrees successfully!" << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}

	void setColor(int K) {
		mColor = K;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Color set to " << K << " successfully!" << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}

	int getColor() const {
		return mColor;
	}

	friend std::ostream& operator<<(std::ostream &out, Shape &figure){
		figure.Shape::display(out);
		figure.display(out);
		return out;
	}
	virtual void display(std::ostream &out){
		out << "Base class output:" << std::endl;
		out << "Properties of figure with ID = " << mID << std::endl;
		out << "Color: " << mColor << std::endl;
		out << "Angle: " << mAngle << std::endl;
		out << "-------------------------------------------------------" << std::endl;
	}
};

class Rectangle : public Shape {
private:
	int mX;				//center coordinates
	int mY;
	int mSide1;
	int mSide2;
public:
	Rectangle(int x, int y, int a, int b): mX(x), mY(y), mSide1(a), mSide2(b){} 		// exceptions when a or b < 0 ?
	~Rectangle() {}

	void move(int x, int y) override {
		mX = x; 
		mY = y;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Figure center moved to (" << x << ", "<< y << ") successfully!" << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}

	bool zoom(int coef) override {
		if(coef <= 0){
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			std::cout << "Zooming by " << coef << ". Aborted." << std::endl;
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			return true;
		}

		mSide1 *= coef;
		mSide2 *= coef;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Zoomed by " << coef << " successfully." << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		return false;
	}

	void display (std::ostream &out) override {
		out << "Derived class output:" << std::endl;
		out << "Shape type: rectangle" << std::endl;
		out << "Center coordinates: x = " << mX << ", y = " << mY << std::endl;
		out << "Sides: a = " << mSide1 << ", b = " << mSide2 << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}
};

class Parallelogram : public Shape {
private:
	int mX;				//center coordinates
	int mY;
	int mDiag1;
	int mDiag2;
	int mDiagAngle;
public:
	Parallelogram(int x, int y, int diag1, int diag2, int alpha): mX(x), mY(y), mDiag1(diag1), mDiag2(diag2), mDiagAngle(alpha) {}
	~Parallelogram() {}

	void move(int x, int y) override {
		mX = x; 
		mY = y;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Figure center moved to (" << x << ", "<< y << ") successfully!" << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}

	bool zoom(int coef) override {
		if(coef <= 0){
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			std::cout << "Zooming by " << coef << ". Aborted." << std::endl;
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			return true;
		}

		mDiag1 *= coef;
		mDiag2 *= coef;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Zoomed by " << coef << " successfully." << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;

		return false;
	}

	void display (std::ostream &out) override {
		out << "Derived class output:" << std::endl;
		out << "Shape type: parallelogram" << std::endl;
		out << "Center coordinates: x = " << mX << ", y = " << mY << std::endl;
		out << "Diagonals: diag1 = " << mDiag1<< ", diag2 = " << mDiag2 << std::endl;
		out << "Angle between diagonals: " << mDiagAngle << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}
};

class Hexagon : public Shape {
private:
	int mX;				//center coordinates
	int mY;
	int mSide;			// that's enough cuz side = radius of circumscribed circle
public:
	Hexagon(int x, int y, int side): mX(x), mY(y), mSide(side) {}
	~Hexagon() {}

	void move(int x, int y) override  {
		mX = x; 
		mY = y;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Figure center moved to (" << x << ", "<< y << ") successfully!" << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}

	bool zoom(int coef) override {
		if(coef <= 0){
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			std::cout << "Zooming by " << coef << ". Aborted." << std::endl;
			std::cout << "───────────────────────────────────────────────────────" << std::endl;
			return true;
		}

		mSide *= coef;

		std::cout << "───────────────────────────────────────────────────────" << std::endl;
		std::cout << "Zoomed by " << coef << " successfully." << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;

		return false;
	}

	void display (std::ostream &out) override {
		out << "Derived class output:" << std::endl;
		out << "Shape type: hexagon" << std::endl;
		out << "Center coordinates: x = " << mX << ", y = " << mY << std::endl;
		out << "Side: a = " << mSide << std::endl;
		std::cout << "───────────────────────────────────────────────────────" << std::endl;
	}
};

int main(){
	// Rectangle rt(0, 0, 3, 4);
	// std::cout << rt;
	// rt.rotate(30);
	// rt.move(2, -3);
	// std::cout << rt;
	// Hexagon hx(3, 8, 5);
	// std::cout << hx;
	// hx.zoom(-2);
	// std::cout << hx;
	// Parallelogram pg(2, 4, 5, 9, 30);
	// std::cout << pg;
	// pg.zoom(2);
	// std::cout << pg;
	Shape* rect = new Rectangle(0,0,1,2);
	std::cout << *rect;
	return 0;
}