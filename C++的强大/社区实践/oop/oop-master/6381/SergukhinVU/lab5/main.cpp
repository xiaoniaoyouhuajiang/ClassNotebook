
#include "shape.h"
#define MAX_R_NUM 50

void chooseShape(){
	int choice=0;
	while(choice!=4)
	{
	cout << endl << "***********************************************************" <<endl;
	cout << "Please, select the shape." << endl;
	cout << "1 - Ellipse" << endl;
	cout << "2 - Trapeze" << endl;
	cout << "3 - Isosceles Trapeze" << endl;
	cout << "4 - Exit" << endl;
	cout << "***********************************************************" << endl <<endl;
	cin.clear();
	cin >> choice;

	switch (choice){
		case 1:{
			Ellipse e(0,1,2,3,"White");
			cout << e;
			e.chooseOption();
			break;	
		}
		case 2:{
			Trapeze t(2,1,1,90,"Blue");
			cout << t;
			t.chooseOption();
			break;	
		}
		case 3:{
			IsoscelesTrapeze it(2,1,1,"Red");
			cout << it;
			it.chooseOption();
			break;
		}
		case 4:
			return;
			break;
		default:
		cout << "Please, use 1-4 keys" << endl;
	}
	}
};
void Generate( vector <shared_ptr<Shape> > &shapes , int number)
{
	 string colour;
for (int i = 0; i < number; ++i)
{
	int r_num1=(rand() % MAX_R_NUM) +1;
	int r_num2=(rand() % MAX_R_NUM) +1;
	int r_num3=(rand() % MAX_R_NUM) +1;
	int r_centerx=(rand() % MAX_R_NUM) ;
	int r_centery=(rand() % MAX_R_NUM) ;


	int r_colour = rand() % 7;
	switch(r_colour)
	{
		case 0:
		colour="Red";
		break;
		case 1:
		colour="Orange";
		break;
		case 2:
		colour="Yellow";
		break;
		case 3:
		colour="Green";
		break;
		case 4:
		colour="Blue";
		break;
		case 5:
		colour="Indigo";
		break;
		case 6:
		colour="Violet";
		break;
		default:
		break;
	}

	int r_figure = rand() % 3;
	if (r_figure == 0)
	{
		int r_num4=(rand() % MAX_R_NUM) +1;
		shapes.push_back(shared_ptr<Shape> (new Ellipse(r_centerx, r_centery, r_num3, r_num4,  colour)));
	}
	else if (r_figure == 1)
	{
		int r_angle=(rand() % 90) +1;
		shapes.push_back(shared_ptr<Shape>(new Trapeze(r_num1, r_num2, r_num3, r_angle, colour)));
		shapes.back()->move(r_centerx,r_centery);
	}
	else
	{
		shapes.push_back(shared_ptr<Shape>(new IsoscelesTrapeze(r_num1, r_num2, r_num3, colour)));
		shapes.back()->move(r_centerx,r_centery);
	}
}
}

void print_All( vector <shared_ptr<Shape> > const & shapes)
{
	for(size_t i =0; i<shapes.size(); i++)
		cout << "Number: "<< i << endl << *shapes[i] << endl;
};


/*template <typename cmp_type>
bool predicate( cmp_type const & cmp1,  cmp_type const & cmp2 )
{
	return *(cmp1)==*(cmp2);
};*/

int Find_First_Eq( vector <shared_ptr<Shape> > const & shapes)
{
	for(size_t i =0; i<shapes.size()-1; i++)
		if(shapes[i]->getColour()==shapes[i+1]->getColour()) return i;
	return -1;
};
int Delete_Shapes(vector <shared_ptr<Shape> > & shapes, Point fst, Point scd)
{
	int num_del=0;
	for(size_t i =0; i<shapes.size(); i++)
	{
		Point center = shapes[i]->getCenter();
		if( center.x > fst.x && center.x < scd.x && center.y > fst.y && center.y < scd.y )
		{
			shapes.erase(shapes.begin()+i);
			i--;
			num_del++;
		}
	}
	return num_del;
}
int main()
{
	srand(time(NULL));
	fflush(stdout);
	int num;
	int choice;
	int res;
	vector <shared_ptr<Shape> > shapes;
	cout << "Choose how many shapes you want to generate:" << endl;
	cin >> num;
	Generate( shapes, num);
	cout << "Shapes have been succesfully generated!" << endl;
	while(choice!=5)
		{
		cout << endl << "***********************************************************" << endl;
		cout << "Please, choose the option." << endl;
		cout << "1 - Print all shapes" << endl;
		cout << "2 - Search for first two adjacent shapes that have same colours" << endl;
		cout << "3 - Delete shapes..." << endl;
		cout << "4 - Change the shape..." << endl;
		cout << "5 - Exit" << endl;
		cout << "***********************************************************" << endl << endl ;
		cin.clear();
		cin >> choice;
		switch (choice){
			case 1:
				print_All( shapes);
				break;
			case 2:

				if( ( res = Find_First_Eq(shapes)) != -1 )
				{
						cout <<"Elements have been succesfully found."<< endl;
						cout << "Number: "<< res << endl << *shapes[res] << endl;
						cout << "Number: "<< res+1 << endl << *shapes[res+1] << endl;
				} 
				else
					cout <<"There aren't neighbors with the same colour."<< endl;
				break;
			case 3:
				cout << "Enter the range ( (x1, y1) (x2, y2) )" << endl;
				cout << "Shapes whose center belong into this range will be deleted:" << endl;
				Point fst, scd;
				fflush(stdin);
				cin >> fst.x >> fst.y;
				cin >> scd.x >> scd.y;

				if( ( res = Delete_Shapes(shapes, fst, scd)) )
					cout<< res << " elements have been succesfully deleted."<< endl;
				else
					cout << "There aren't any elements into this range.";
				
				break;
			case 4:
				int num;
				cout << "Enter the number of shape you want to change : " << endl;
				cin >> num;
				shapes[num]->chooseOption();
				break;
			case 5:
				shapes.clear();
				return 0;
				break;
			default:
				cout << "Use only 1 - 5 keys!" << endl;
				
		}		
		}
	return 0;
}

