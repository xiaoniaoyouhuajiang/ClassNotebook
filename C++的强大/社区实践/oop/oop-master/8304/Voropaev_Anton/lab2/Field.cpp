#include <iostream>
#include "Field.h"
#include "FieldIterator.h"

Field::Field(const Field& field_to_copy) {
    if (this != &field_to_copy) {

        this->maxQuantity = field_to_copy.maxQuantity;

        this->currentQuantity = field_to_copy.currentQuantity;

        this->size = field_to_copy.size;

        this->field = field_to_copy.field;
    }
}


Field::Field(int width, int height) {
    if ((width <= 0) || (height <= 0)){
        std::cout << "Empty/Negative size field cannot be created\n";
        return;
    }

    std::shared_ptr<std::shared_ptr<cell[]>[]> new_field(new std::shared_ptr<cell[]>[height], std::default_delete<std::shared_ptr<cell[]>[]>());
    for (int i = 0; i < height; ++i) {
        std::shared_ptr<cell[]> new_elem(new cell[width], std::default_delete<cell[]>());

        int neutral_pos = rand() % width;
        int neutral_type = rand() % 4;
        for(int j = 0; j < width; ++j) {
            int landscape_tmp = rand() % 3;
            switch (landscape_tmp) {//Инициализация ландшавта
                case 0 :
                    new_elem[j].type = LandscapeTypes::Mountain;
                    break;
                case 1 :
                    new_elem[j].type = LandscapeTypes::Desert;
                    break;
                case 2 :
                    new_elem[j].type = LandscapeTypes::Fog;
                default:
                    break;
            }
            if(neutral_pos == j){//Иницализация нейтральных объектов
                switch(neutral_type) {
                    case 0 :
                        new_elem[j].neutral = new Forge(i + 1, j + 1);
                        break;
                    case 1 :
                        new_elem[j].neutral = new HealingFountain(i + 1, j + 1);
                        break;
                    case 2 :
                        new_elem[j].neutral = new TrainingCamp(i + 1, j + 1);
                        break;
                    case 3 :
                        new_elem[j].neutral = new MaradeursCamp(i + 1, j + 1);
                        break;
                    default :
                        new_elem[j].neutral = new Forge(i + 1, j + 1);
                        break;
                }
            }

        }
        new_field[i] = new_elem;
    }
    field = new_field;

    field[0][0].unit = new Base();
    this->base = dynamic_cast<Base*>(field[0][0].unit);

    this->size.width = width;
	this->size.height = height;
}


Field::Field(Field&& other) noexcept {

    this->currentQuantity = other.currentQuantity;
    this->size = other.size;
    this->maxQuantity = other.maxQuantity;

	this->field = other.field;
	other.field = nullptr;
}


Field& Field::operator=(const Field &proc_field) {

	if (this != &proc_field) {

		this->maxQuantity = proc_field.maxQuantity;

		this->currentQuantity = proc_field.currentQuantity;

		this->size = proc_field.size;

        this->field = proc_field.field;
	}
	return *this;
}

bool Field::moveUnit(int xPos, int yPos, int dX, int dY) {
    if (((dX > (this->getSize().width - 1) - xPos) || (dY > (this->getSize().height - 1) - yPos))
        || ((xPos + dX < 0) || (yPos + dY < 0))) {
        std::cout << "Cant step out of field's borders\n";
        return false;
    }

    auto next_cell = field[yPos + dY][xPos + dX];

    if (field[yPos][xPos].unit == nullptr || next_cell.unit != nullptr) {
        std::cout << "Can't move non-existent object / Can't move to a taken position\n";
        return false;
    }

    Unit* tmp = dynamic_cast<Unit*>(field[yPos][xPos].unit);
    auto reverse_effect = tmp->landscape_effect;

    switch (reverse_effect.type) {
        case EffectTypes::Health :
           tmp->actHealed(-reverse_effect.effect_num);
            break;
        case EffectTypes::Damage :
            tmp->IncreaseDmg(-reverse_effect.effect_num);
            break;
        case EffectTypes::Range :
            tmp->IncreaseRange(-reverse_effect.effect_num);
    }

    tmp->landscape_effect.effect_num = 0;

    if(next_cell.neutral != nullptr) {
        (*next_cell.neutral)(tmp);
    }

    field[yPos + dY][xPos + dX].unit = field[yPos][xPos].unit;

    landscape_interaction(tmp, yPos + dY, xPos + dX);

    field[yPos][xPos].unit = nullptr;
    return true;
}


bool Field::addObj(Object* object, int x, int y) {
    if(dynamic_cast<Base*>(field[0][0].unit)->create_unit(this, object, x, y)) {
        ++currentQuantity;
        return  true;
    }
    else
        return false;
}


void Field::removeObj(Location pos) {
    if(field[pos.getPosition().second - 1][pos.getPosition().first - 1].unit == nullptr){
        std::cout << "Position is already free\n";
        return;
    }
    base->unsubscribe(field[pos.getPosition().second-1][pos.getPosition().first - 1].unit);
    field[pos.getPosition().second-1][pos.getPosition().first - 1].unit = nullptr;
    --currentQuantity;
}


f_size Field::getSize() const {
	return this->size;
}


int Field::getMax() const {
	return this->maxQuantity;
}


void Field::setLimit(int lim) {
    if(lim < 0) {
        std::cout << "Field cannot contain negative quantity of objects\n";
    }
	this->maxQuantity = lim;
}


int Field::getQuantity() const {
	return this->currentQuantity;
}

std::shared_ptr<std::shared_ptr<cell[]>[]> Field::getHead() const {
    return this->field;
}


Iterator* Field::getIterator() {
    return (new Iterator(*this));
}


Iterator *Field::begin() {
    auto* start = new Iterator(*this);
    start->first();
    return start;
}


Iterator *Field::end() {
    auto* end = new Iterator(*this);
    end->first();

    for(int i = 0; i < this->size.width * this->size.height; ++i) {
        ++end;
    }
    return end;
}


void Field::print() const{
    for (int i = 0; i < size.height; ++i) {
        for (int j = 0; j < size.width; ++j)
        {
            if (!field[i][j].unit && !field[i][j].neutral)
                std::cout << "[ ] ";
            else if(field[i][j].unit != nullptr && i == 0 && j == 0)
                std::cout << "[" << 'B' << "] ";
            else if(field[i][j].unit != nullptr) {
                std::cout << "[" << dynamic_cast<Unit*>(field[i][j].unit)->name << "] ";
            }
            else if (field[i][j].neutral)
                std::cout << "[" << "N" << "] ";
    }
        std::cout << std::endl;
    }
}


void Field::landscape_interaction(Object* object, int x, int y) {

    LandscapeProxy proxy;
    auto effect = proxy.interaction(field[x][y].type);
    auto it = std::find(effect.effected_units.begin(), effect.effected_units.end(), dynamic_cast<Unit*>(object)->name);

    if(it != effect.effected_units.end()) {
        dynamic_cast<Unit*>(object)->landscape_effect.type = effect.type;
        dynamic_cast<Unit*>(object)->landscape_effect.effect_num = effect.effect_num;
        switch (effect.type){
            case EffectTypes::Damage :
                dynamic_cast<Unit*>(object)->IncreaseDmg(effect.effect_num);
                break;
            case EffectTypes::Range :
                dynamic_cast<Unit*>(object)->IncreaseRange(effect.effect_num);
                break;
            case EffectTypes::Health :
                dynamic_cast<Unit*>(object)->actHealed(effect.effect_num);
                break;
        }
    }
}

void Field::setBase(Base* new_base) {
    this->base = new_base;
}

Base *Field::getBase() {
    return this->base;
}
