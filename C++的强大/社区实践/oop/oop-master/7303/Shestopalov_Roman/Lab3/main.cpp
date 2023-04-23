#include <iostream>
#include "shape.h"
#include "pentagon.h"
#include "triangle.h"
#include "trap.h"
//#include "vector.h"
#include "list.h"

/*void sort(vector<Shape*> v){
  size_t i,j = 0;
  for (i;i<v.size()-1;i++) {
      for (i;j<v.size()-1;j++) {
          if (v[j]->countang < v[j-1]->countang){
              Shape* buf = v[j];
              v[j] = v[j-1];
              v[j-1]  = buf;
            }
        }
    }
  for(size_t k=0;k<v.size();k++){
       Triangle* trig = dynamic_cast<Triangle*>(v[k]);
         Trap* trap = dynamic_cast<Trap*>(v[k]);
           RegularPentagon* pent = dynamic_cast<RegularPentagon*>(v[k]);
           if(trig){
               std::cout<< *trig<<std::endl;
             }           if(trap){
               std::cout<< *trap<<std::endl;
             }           if(pent){
               std::cout<< *pent<<std::endl;
             }
  }
}
*/

int main() {
/*
  Triangle t({0, 0}, {2, 2}, {-2, -2});
  std::cout << t << std::endl << std::endl;

  t.rotate(50);
  std::cout << t << std::endl << std::endl;

  RegularPentagon p({0, 0}, 2);
  std::cout << p << std::endl << std::endl;

  p.scale(2);
  std::cout << p << std::endl << std::endl;

  p.move(2, 2);
  std::cout << p << std::endl << std::endl;

  p.rotate(25);
  std::cout << p << std::endl << std::endl;

  Trap tr({0, 2}, {2, 2}, {-2, -2}, {4, -2});
  std::cout << tr << std::endl << std::endl;

  tr.rotate(12);
  std::cout << tr << std::endl << std::endl;
*/
/*
  vector<Shape*> v(0);
  v.push_back(new Triangle ({0, 0}, {2, 2}, {-2, -2}));
  v.push_back(new RegularPentagon ({0, 0}, 2));
  v.push_back(new Trap ({0, 2}, {2, 2}, {-2, -2}, {4, -2}));

  sort(v);
  */

  list<Shape*> l1;

  l1.push_back(new Triangle ({0, 0}, {2, 2}, {-2, -2}));
  l1.push_back(new RegularPentagon ({0, 0}, 2));
  l1.push_back(new Trap ({0, 2}, {2, 2}, {-2, -2}, {4, -2}));

  for(list_iterator<Shape*> it = l1.begin(); it != l1.end(); it++){
      Triangle* trig = dynamic_cast<Triangle*>(*it);
        Trap* trap = dynamic_cast<Trap*>(*it);
          RegularPentagon* pent = dynamic_cast<RegularPentagon*>(*it);
          if(trig){
              std::cout<< *trig<<std::endl;
            }           if(trap){
              std::cout<< *trap<<std::endl;
            }           if(pent){
              std::cout<< *pent<<std::endl;
            }
          std::cout<<std::endl;

  }

    list<Shape*> l2;

    l2.push_back(new Trap ({0, 2}, {2, 2}, {-2, -2}, {4, -2}));
      l2.push_back(new RegularPentagon ({0, 0}, 2));
        l2.push_back(new Triangle ({0, 0}, {2, 2}, {-2, -2}));

        for(list_iterator<Shape*> it = l2.begin(); it != l2.end(); it++){
            Triangle* trig = dynamic_cast<Triangle*>(*it);
              Trap* trap = dynamic_cast<Trap*>(*it);
                RegularPentagon* pent = dynamic_cast<RegularPentagon*>(*it);
                if(trig){
                    std::cout<< *trig<<std::endl;
                  }           if(trap){
                    std::cout<< *trap<<std::endl;
                  }           if(pent){
                    std::cout<< *pent<<std::endl;
                  }
                    std::cout<<std::endl;
        }

        for(list_iterator<Shape*> it1 = l1.begin(); it1 != l1.end(); it1++){
            Triangle* trig1 = dynamic_cast<Triangle*>(*it1);
              Trap* trap1 = dynamic_cast<Trap*>(*it1);
                RegularPentagon* pent1 = dynamic_cast<RegularPentagon*>(*it1);

                if(trig1){
                    for(list_iterator<Shape*> it2 = l2.begin(); it2 != l2.end(); it2++){
                        Triangle* trig = dynamic_cast<Triangle*>(*it2);
                        l1.insert(it1,*it2);
                        l2.erase(it2);
                        break;
                      }
                  }
                    if(trap1){
                        for(list_iterator<Shape*> it2 = l2.begin(); it2 != l2.end(); it2++){
                            Trap* trap2 = dynamic_cast<Trap*>(*it2);
                            l1.insert(it1,*it2);
                            l2.erase(it2);
                            break;
                          }
                  }
                    if(pent1){
                        for(list_iterator<Shape*> it2 = l2.begin(); it2 != l2.end(); it2++){
                            RegularPentagon* pent2 = dynamic_cast<RegularPentagon*>(*it2);
                            l1.insert(it1,*it2);
                            l2.erase(it2);
                            break;
                          }
                  }
                    std::cout<<std::endl;
          }

        for(list_iterator<Shape*> it = l1.begin(); it != l1.end(); it++){
            Triangle* trig = dynamic_cast<Triangle*>(*it);
              Trap* trap = dynamic_cast<Trap*>(*it);
                RegularPentagon* pent = dynamic_cast<RegularPentagon*>(*it);
                if(trig){
                    std::cout<< *trig<<std::endl;
                  }           if(trap){
                    std::cout<< *trap<<std::endl;
                  }           if(pent){
                    std::cout<< *pent<<std::endl;
                  }
                std::cout<<std::endl;

        }

  return 0;
}
