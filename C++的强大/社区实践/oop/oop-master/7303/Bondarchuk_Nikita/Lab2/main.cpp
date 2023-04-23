#include <QCoreApplication>
#include "shape.h"
#include "circle.h"
#include "fiveverticals_star.h"
#include "sixverticals_star.h"
using namespace std;
int Shape::id;
int main()
{
    // Circle
   Circle s(3, 2, 2);
   cout << s << endl;
   s.scale(2);
   cout <<"scale:" << endl <<  s <<endl;
   s.MoveCentre(3,3);

    cout <<"move centre:"<< endl << s <<endl;

   //Fiveverticals_Star
   double x_arr[5];
   double y_arr[5];
   for(int i = 0; i < 5; i++){
       x_arr[i] = i + 1;
       y_arr[i] = 5 - i;
   }
   Fiveverticals_Star k(0, 0, x_arr, y_arr);
   Fiveverticals_Star k1(0, 0, x_arr, y_arr);
   /*cout << k <<endl;
   k.scale(2);
   cout << "scale:"<< endl << k <<endl;
   k.MoveCentre(1, 1);
   cout << "move centre:"<< endl << k <<endl;
   cout << "rotate: "<< k.rotate(3.14/2) << endl << k <<endl;
*/

   //Sixverticals_Star
  /* double x_arr[6];
   double y_arr[6];
   for(int i = 0; i < 6; i++){
       x_arr[i] = i + 1;
       y_arr[i] = 6 - i;
   }
   Sixverticals_Star k(0, 0, x_arr, y_arr);
   cout << k <<endl;*/

Circle s2(3, 3, 2);
cout << s2 << endl;
if(s == s2)
    cout << "Good Job";
if(k == k1)
    cout << "Perfect";
}
