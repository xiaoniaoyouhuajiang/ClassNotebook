#include <iostream>

bool range_check(int left, int right, int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes);

stepik::vector<stepik::shared_ptr<Shapes>> copy(int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes);

float GenNum();
stepik::shared_ptr<Shapes> GenerationRectangle(int flag);
stepik::shared_ptr<Shapes> GenerationPentagram(int flag);
stepik::shared_ptr<Shapes> GenerationPentagon(int flag);
