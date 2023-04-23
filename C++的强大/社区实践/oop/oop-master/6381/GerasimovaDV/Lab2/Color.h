#ifndef OOP_COLOR_H
#define OOP_COLOR_H


class Color {
public:
    Color(int red, int green, int blue);

    int getRed() const;

    int getGreen() const;

    int getBlue() const;

private:
    int red;
    int green;
    int blue;
};


#endif //OOP_COLOR_H
