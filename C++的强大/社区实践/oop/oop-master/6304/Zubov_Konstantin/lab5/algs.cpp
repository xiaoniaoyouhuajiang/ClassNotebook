#include "algs.hpp"
#define MIN(a, b) ((a) < (b) ? (a) : (b))

vector<shared_ptr<Shape>> create(){ //creating a vector of 1000 elements
    vector<shared_ptr<Shape>> a(1000);
    for(int i=0;i<1000;i++){
        int k=rand() % 3;
        if(!k)
            a[i]=shared_ptr<Shape>(new Arc(rand()%3,rand()%3,1+rand()%3,rand()%90+1,rand()%180+90));
        else if(k==1)
            a[i]=shared_ptr<Shape>(new Circle(rand()%3,rand()%3,1+rand()%3));
        else
            a[i]=shared_ptr<Shape>(new Ellipse(rand()%3,rand()%3,1+rand()%3,1+rand()%3));
    }
    return a;
}



bool search(const vector<shared_ptr<Shape>>& a, const vector<shared_ptr<Shape>>& b){
    bool f=false;
    while(!f)
    for(const auto& it1: a){
        for(const auto& it2: b){
        if((*it1).getlength()!=(*it2).getlength()){
            std::cout<<"Выведены первые 2 элемента, длина которых различна\n";
            std::cout<<*it1;
            std::cout<<*it2;
            std::cout<<"///////////////////////\n";
            f=true;
            return f;
            break;
    }
    else {
        f=false;
    }
    return f;

     }
    }
}



 vector<shared_ptr<Shape>> create_p(vector<shared_ptr<Shape>>& mass, int k, int i){

    vector<shared_ptr<Shape>> b(k);
    int j=i+k;
    std::cout<< "Диапазон элементов последовательности: " <<std::endl;
    std::cout<<i<<std::endl;
    std::cout<<j<<std::endl;

       for(int m=0;m<k;++m){
       b[m]=mass[i];
       i++;
       }
    return b;
    }


void print(const vector<shared_ptr<Shape>>& mass){
    for(auto i: mass)
        std::cout<<*(i.get());
}

bool predikat1(Shape* first, Shape* second){
	return (first->getlength() == second->getlength());
}

bool predikat2(Shape* first, Shape* second){
    double x1,y1,x2,y2;
    first->getcentr(x1,y1);
    second->getcentr(x2,y2);
    if(x1==x2 && y1==y2){
       return true;
    }
}


void length_sort(vector<shared_ptr<Shape>> &arr, int left, int right){
	int i = left, j = right;
	shared_ptr<Shape> tmp;
	shared_ptr<Shape> p = arr[(left + right) / 2];

	while (i <= j) {
		while (arr[i]->getlength() < p->getlength())
			i++;
		while (arr[j]->getlength() > p->getlength())
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j){
		length_sort(arr, left, j);
	}
	if (i < right){
		length_sort(arr, i, right);
	}

}

vector<shared_ptr<Shape>> intersection(const vector<shared_ptr<Shape> > &first, const vector<shared_ptr<Shape> > &second){
	vector<shared_ptr<Shape>> result;

	//Создание множества пересечений
	for (unsigned int i = 0; i < MIN(first.size(), second.size()); i++){
		if (predikat1(first[i].get(), second[i].get())&&predikat2(first[i].get(),second[i].get())) {
		    result.push_back(first[i]);

		}
	}

	if(result.size()){
    length_sort(result, 0, result.size()-1);
    return result;
	}
    else
    return result;
}








