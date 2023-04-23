#include <iostream>
#include "stepik_containers.h"

using namespace stepik;
using std::cout;
using std::endl;

int main()
{
    list<int> numeral_list;
    vector<int> linear_vector = {1, 2, 3, 4, 5};
    vector<int> square_vector(linear_vector);

    for (int i = 1; i < 6; i++)
    {
        numeral_list.push_back(i + 1);
        square_vector[i - 1] *= square_vector[i - 1];
    }

    vector<int> qube_vector(square_vector.begin(), square_vector.end());
    for (int i = 0; i < 5; i++)
        qube_vector[i] *= linear_vector[i];

    linear_vector.push_back(6);
    square_vector.push_back(36);
    qube_vector.push_back(216);
    numeral_list.push_front(1);

    cout << "Sqaure and qube table:" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << i + 1 << ") " << linear_vector[i] << " - "
             << square_vector[i] << " - " << qube_vector[i] << endl;
        if (i % 2 == 0)
            numeral_list.pop_front();
        else
            numeral_list.pop_back();
    }

    if (numeral_list.empty())
        cout << "Numeral list is now empty." << endl;

    vector<int> all_element_vector = square_vector;
    all_element_vector.insert(all_element_vector.begin(), linear_vector.begin(), linear_vector.end());
    linear_vector.erase(linear_vector.begin(), linear_vector.end());
    for (int i = 0; i < 6; i++)
    {
        all_element_vector.insert(all_element_vector.end(), qube_vector[0]);
        qube_vector.erase(qube_vector.begin());
    }

    if (linear_vector.empty() && qube_vector.empty())
        cout << "Linear and qube vectors are now empty." << endl;
    for (unsigned int i = 0; i < all_element_vector.size(); i++)
        cout << all_element_vector[i] << " ";
    cout << endl;

    return 0;
}
