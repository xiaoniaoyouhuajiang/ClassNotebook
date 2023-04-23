#include <algorithm>
#include <iostream>
#include "list.h"
#include "shape.h"
#include "shared_ptr.h"

using namespace std;
using namespace stepik;

shared_ptr<Shape> randShape();
list<shared_ptr<Shape>> randList();