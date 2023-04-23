#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <tuple>

namespace figures
{
    using namespace std;

    struct point
    {
        double y;
        double x;
    };

    class shape
    {
    public:
        uint32_t get_figure_number() const;
        virtual tuple<int16_t, int16_t, int16_t> get_color() const;
        virtual void change_color(int16_t red, int16_t green, int16_t blue);
        virtual vector<point> get_coordinates() const;
        virtual void move(pair<double, double> delta);
        virtual void rotate(int16_t angle);
        virtual void scale(int8_t coef);
        virtual ~shape() = 0;
        friend ostream& operator<<(ostream& stream, shape& obj);
    protected:
        shape()
            : number_(create_figure_number())
            , red_(255), green_(255), blue_(255), points()
        {}

        static uint32_t create_figure_number()
        {
            static uint32_t number = 1;

            return number++;
        }

        virtual point get_centre() const;

    protected:
        uint32_t number_;
        int16_t red_;
        int16_t green_;
        int16_t blue_;
        vector<point> points;
    };

    inline uint32_t shape::get_figure_number() const
    {
        return number_;
    }

    inline tuple<int16_t, int16_t, int16_t> shape::get_color() const
    {
        return {red_, green_, blue_};
    }

    inline void shape::change_color(int16_t red, int16_t green, int16_t blue)
    {
        red_ = red;
        green_ = green;
        blue_ = blue;
    }

    inline vector<point> shape::get_coordinates() const
    {
        return points;
    }

    inline void shape::move(pair<double, double> delta)
    {
        for (auto& p : points)
        {
            p.y += delta.first;
            p.x += delta.second;
        }
    }

    inline void shape::rotate(int16_t angle)
    {
        auto [y_0, x_0] = get_centre();

        angle %= 360;
        double radian = angle * acos(-1) / 180;

        // Rotation
        for (auto& p : points)
        {
            p.x = x_0 + (p.x - x_0) * cos(radian) - (p.y - y_0) * sin(radian);
            p.x = y_0 + (p.y - y_0) * cos(radian) - (p.x - x_0) * sin(radian);
        }
    }

    inline void shape::scale(int8_t coef)
    {
        auto [y_0, x_0] = get_centre();

        for (auto& p : points)
        {
            p.x *= coef;
            p.y *= coef;
        }

        auto [y_1, x_1] = get_centre();

        pair<double, double> delta = {abs(y_0 - y_1), abs(x_0 - x_1)};

        if (y_1 > y_0)
            delta.first = -delta.first;

        if (x_1 > x_0)
            delta.second = -delta.second;

        move(delta);
    }

    inline point shape::get_centre() const
    {
        double y_0 = 0;
        for (auto p : points)
            y_0 += p.y;

        double x_0 = 0;
        for (auto p : points)
            x_0 += p.x;

        return {y_0, x_0};
    }

    ostream& operator<<(ostream& stream, shape& obj)
    {
        auto [red, green, blue] = obj.get_color();
        stream << "Figure number is " << obj.get_figure_number() << endl
               << "Color is " << red << ' ' << green << ' ' << blue << endl
               << "Coordinates are ";
        for (auto e : obj.get_coordinates())
            stream << e.y << "," << e.x << ' ';
        stream << endl;

        return stream;
    }

    class triangle final : public shape
    {
        triangle(point a, point b, point c);
    };

    inline triangle::triangle(point a, point b, point c)
    {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
    }

    class trapezium : public shape
    {
        trapezium(point a, point b, point c, point d);
    };

    inline trapezium::trapezium(point a, point b, point c, point d)
    {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);
    }

    class regular_polygon : public shape
    {
        regular_polygon(point a, point b, point c, point d, point e);
    };

    inline regular_polygon::regular_polygon(point a, point b, point c, point d, point e)
    {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);
        points.push_back(e);

        auto get_distance = [](point a, point b) -> double
        {
            return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
        };

        auto is_equal = [](double a, double b)
        {
            return fabs(a - b) < numeric_limits<double>::epsilon();
        };

        auto distance = get_distance(points.front(), points.back());

        for (auto it = points.begin(); it != prev(points.end()); it++)
        {
            if (!is_equal(distance, get_distance(*it, *(next(it)))))
                throw runtime_error("The polygon is not regular! Abort");
        }
    }
}