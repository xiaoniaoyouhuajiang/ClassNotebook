#include <iostream>
#include "GameField.h"

GameField::GameField(size_t height, size_t width)
{

    height_ = height;
    width_ = width;
    auto tmp_  = new Tale*[height_];
    for (int i = 0; i < height; ++i)
        tmp_[i] = new Tale[width];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            tmp_[i][j].object_ = nullptr;
            int r = rand() % 3;
            if (r == 0)
                tmp_[i][j].landscape_ = landscapeFactory_.getFieldLandscape();
            else if (r == 1)
                tmp_[i][j].landscape_ = landscapeFactory_.getForestLandscape();
            else
                tmp_[i][j].landscape_ = landscapeFactory_.getMountainLandscape();
            tmp_[i][j].x_ = i;
            tmp_[i][j].y_ = j;
        }
    }
    field_ = tmp_;
    maxOfObjects_ = height_ * width_;
    objectCounter_ = 0;
}

int GameField::addObject(Object *object, size_t x, size_t y)
{
    if (objectCounter_ + 1 > maxOfObjects_) return 1;
    field_[x][y].object_ = object;
    field_[x][y].x_ = x;
    field_[x][y].y_ = y;
    objectCounter_++;
    object->x_ = x;
    object->y_ = y;
    return 0;
}

void GameField::deleteObject(size_t x, size_t y)
{
    if(field_[x][y].object_ != nullptr)
    {
        field_[x][y].object_ = nullptr;
        objectCounter_--;
    }
}

void GameField::moveObject(size_t x1, size_t y1, size_t x2, size_t y2)
{
    if(field_[x2][y2].object_ == nullptr)
    {
        field_[x2][y2].object_ = field_[x1][y1].object_;
        field_[x1][y1].object_ = nullptr;
    }
}

void GameField::printField()
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {

            if (field_[i][j].object_ == nullptr)
                std::cout << field_[i][j].landscape_->getID() << " " << field_[i][j].landscape_->getID();
            else
                std::cout << field_[i][j].landscape_->getID() << field_[i][j].object_->id_<< field_[i][j].landscape_->getID();
        }
        std::cout << std::endl;
    }
}

void GameField::swap(GameField &other)
{
    std::swap(field_, other.field_);
    std::swap(width_, other.width_);
    std::swap(height_, other.height_);
    std::swap(maxOfObjects_, other.maxOfObjects_);
    std::swap(objectCounter_, other.objectCounter_);
}

GameField::GameField(const GameField &other)
{
    field_ =  other.field_;
    width_ = other.width_;
    height_ = other.height_;
    maxOfObjects_ = other.maxOfObjects_;
    objectCounter_ = other.objectCounter_;
}

GameField& GameField::operator=(GameField const &other)
{
    if (&other != this)
        GameField(other).swap(*this);
    return *this;
}

GameField& GameField::operator=(GameField &&other)
 {
     swap(other);
     return *this;
}

GameField::~GameField()
{
    /*for (int i = 0; i < this->height_; ++i)
    {
        this->field_[i] = nullptr;
        delete [] this->field_[i];
    }
    delete [] this->field_;
    for (int i = 0; i < height_; ++i)
    {
        delete field_[i]->object_;
        delete [] field_[i];
    }
    delete [] field_;*/
}