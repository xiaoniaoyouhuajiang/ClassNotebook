#ifndef IDRAWABLE_H
#define IDRAWABLE_H


class IDrawable
{
public:
    virtual ~IDrawable() = default;
    virtual char draw() = 0;
};

#endif // IDRAWABLE_H
