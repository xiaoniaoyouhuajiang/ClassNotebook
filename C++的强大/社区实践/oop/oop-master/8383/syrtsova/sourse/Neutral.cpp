#include "pch.h"
#include "Neutral.h"
#include "Object.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "ctime"

Neutral::Neutral(char n, string message_, int x_, int y_, int col) {
	name = n; 
	object = name;
	color = col;
	XY.x = x_;
	XY.y = y_;
}

void Neutral::setLoc(int x, int y)
{
	XY.x = x;
	XY.y = y;
}


Neutral* Neutral::getLink(int &x, int &y)
{
	for (int i = 0; i < 4; i++)
	{
		if(link[i]->getX() == x && link[i]->getY() == y)
		return link[i];
	}
}

int Neutral::getX()
{
	return XY.x;
}


int Neutral::getY()
{
	return XY.y;
}


Neutral* Neutral::returnThis(int x, int y)
{
	if (x == this->XY.x && y == this->XY.y)
		return this;
}



Pab::Pab(int x, int y) : Neutral('P', "This is PAB!", x, y, colorLand::red){
	
}

void Pab::message (){
	string message[] = { "Около кривой дороги стоит Таверна. Не просто таверна, а Таверна с большой такой буквы. Старая кривая вывеска зазывает путников. Снизу, неровными буквами, подписано: «МО ЭВМ». \n Само четырехэтажное здание было выложено из огромных камней и рассчитано даже на дракона. Последний этаж венчал бревенчатый сруб с покатой крышей. \nЗайдя внутрь, нашего Путника встречает просторный зал с каменными полами, деревянными стенами и потолком, под которым клубится подозрительный дым. \n Оглядевшись, Юнит видит камин в одном углу, а стойку из цельного дуба в противоположном. Старая лестница намекнет, что тут и номерок можно взять на ночь или пожить с месяцок, а то и больше. \n А уж запахи, тянущиеся с кухни, не оставят равнодушным никого. Жаркое из кабана, суп «лягушачьи головы» и похлебка из человеческих потрошков – только малая часть меню. \nОбычно зал толи на половину пуст, толи на половину полон, не разберешь. Но за грубыми столами кто - то режется в карты, пьет, ест или потягивает пиво в темном углу, а на отполированных лавках некоторых неловко пытаются тискать за причинные места.Хозяин на это смотрит сквозь пальцы и сам радушно нальет пиво любому, кто попросит.Что помягче или покрепче появится на столе, стоит только попросить желаемое. \nДенег тут не берут, все за счет заведения." };
	for (int i = 0; i != message->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
	Sleep(10);
	for (int i = 0; i != message->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
	Sleep(10);
	cout << endl;
	string message_2[] = { "Юнит полностью восстановил свои силы. Более того, оказанный радушный приём повысил его основные показатели: здравье, атаку и броню. /n. Количество ячеек для передвижения также сократилось. Юнит объелся и плохо передвигается! " };
	for (int i = 0; i != message_2->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
}

Pab::~Pab() {
	cout << endl << "О, нет! За ЧТО?!";
}

Tablet::Tablet(int x, int y) : Neutral('T', "This is Tablet", x, y, colorLand::cyan) {
}

void Tablet::message(){
	cout << "Юнит достиг середины карты, впереди множетсво опасностей!";
}
Tablet::~Tablet() {
	cout << endl << "Теперь случайный путник точно потеряется =(";
}


Cave::Cave(int x, int y) : Neutral('C', "This is Cave", x, y, colorLand::yellow) {
	dragon = new Dragon;
}


void Cave::message(){
	cout << endl << "Юнит достиг замка. Замок полон древних артефактов и сокровищ. Одно только но. Все это дело стережет дракон.";
}

Cave::~Cave() {
	cout << endl << "Замок уничтожен!";
}


Ruin::Ruin(int x, int y) : Neutral('R', "This is Ruin", x, y, colorLand::lightBlue) {
	trap_1 = true;
	strength_1 = 100;
	trap_2 = true;
	strength_2 = 100;
	trap_3 = true;
	strength_3 = 100;
	trap_4 = true;
	strength_4 = 100;
	trap_5 = true;
	strength_5 = 100;
	state = true;
}


void Ruin::printMessage(string message)
{
	for (int i = 0; i != message.length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
}


bool Ruin::passage()
{
	if (state)
	{
		string message = "Юнит заходит в руины, но они полны опасносней. Везде таятся ловушки. Юнит случайно наступил не на ту плиту. Он слышит как, что-то большое стремительно движется к нему, успеет ли он добижать до ближайшего убежища?";
		int chance = 0;
		srand(time(0));
		if (trap_1)
		{
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "Юнит смог добежать до ближайшего поворота. Но закончились ли на этом опасности?";
				
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				printMessage(message);
			}
			else
			{
				message = "Юнит не смог добежать до ближайшего поворота. Огромный валун раздавил беднягу. Какая глупая смерть";
				printMessage(message);
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				return false;
			}
		}
		if (trap_2)
		{
			message = "За поворотом юнит видит странную головоломку. Он понятия не имеет, как её решить. Ну, что ж, понадееся на удачу.";
			printMessage(message);
			chance = 0 + rand() % strength_2;
			if (chance <= 50)
			{
				message = "Удивительно, но юнит отгадал шифр и дверь распасхуналсь!";
				strength_2 -= 20;
				if (strength_2 == 0)
					trap_2 = false;
				printMessage(message);
			}
			else
			{
				message = "Настоящий боец на удачу не надеется. Юнит позабыл об этом. Из отверстия вылетела отравленная стрела. Юнит умер.";
				printMessage(message);
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				return false;
			}
		}
		if (trap_3 == true)
		{
			message = "За дверью юнит видит огромного монстра. Но на удивление, тот не стал нападать, а загодал загадку. Знает ли юнит на неё ответ?";
			printMessage(message);
			chance = 0 + rand() % strength_3;
			if (chance <= 50)
			{
				message = "Юнит всоминает, как слышал данную загадку в местном пабе. Он гордо отвечает: Полиморфизм. После чего монстр распался на разные типы данных.";
				strength_3 -= 20;
				if (strength_3 == 0)
					trap_3 = false;
				printMessage(message);
			}
			else
			{
				message = "Юнит не знает ответа и говорит: Гомоиконность. В то же мгновение он остается без головы. ";
				printMessage(message);
				if (strength_3 != 0)
					strength_3 -= 20;
				return false;
			}
		}
		if (trap_4 == true)
		{
			message = "Юнит заходит в огронмый тронный зал. Сверху начинает литься вода. Успеет ли юнит найти рычаг? ";
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "Юнит нашёл рычаг. Он запрыгнул на лодку, которая вынурнула из под воды. Нужно спешить, иначе тут все развалиться.";
				if (strength_1 != 0)
					strength_1 -= 20;
				printMessage(message);
			}
			else
			{
				message = "Юнит не смог найти рычаг и задохнулся. На последок он пошутил: Выглядит, как мой курсач. Прекрасная смерть";
				printMessage(message);
				if (strength_1 != 0)
					strength_1 -= 20;
				return false;
			}
		}
		if (trap_5 == true)
		{
			message = "Юнит заходит в покои драконоубицы. Он видит скелет с мечом. От них исходила пугающая аура. Этим мечом были убиты тысячи траконов, он хранит в себе их души и силу. Внезаптно скелет ожил и сказа: ты можешь взять этот меч, но у тебя всего одна попытка.";
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "Юнит сразу понял, что тут какой-то подвох. Он оглянулся и увидел доспехи скелета, от которых исходила полностью противоположаня аура. Он надел доспехи, после чего легко взял меч, а скелет тот час превратился в пыль.";
				printMessage(message);
				state = false;
				return true;
			}
			else
			{
				message = "Юнит радостно потянулся за мечом, но как только тот его каснулся, юнит превратился в пыль.";
				printMessage(message);
				if (strength_1 != 0)
					strength_1 -= 20;
				return false;
			}
		}
	}
	else
	{
		string message = "Юнит просто прогулялся по руинам. Отличный вид, но тут больше нечего ловить.";
		printMessage(message);
	}
}

void Ruin::message(){
	cout << "Юнит нашёл древние руины некогда могущественной циливизации. /nОн видит огромного дракона, который сторожит великое сокровище, увеличивающее атаку на 100 единиц. /n Хватит ли силы у юнита одолеть монстра?/n";
}
Ruin::~Ruin() {
	cout << endl <<"Руины были уничтожены";
}



Creating::Creating(int x_max, int y_max, Map* field)
{
	pab = new Pab(x_max - 2, 1);
	tablet = new Tablet(x_max / 2, y_max / 2);
	cave = new Cave(x_max, y_max);
	ruin = new Ruin(x_max / 2, y_max - 3);
	(*field).addOnMap(pab->getX(), pab->getY(), pab);
	(*field).addOnMap(tablet->getX(), tablet->getY(), tablet);
	(*field).addOnMap(cave->getX(), cave->getY(), cave);
	(*field).addOnMap(ruin->getX(), ruin->getY(), ruin);
}


Creating::Creating(int x_max, int y_max, Map* field, bool state)
{
	pab = new Pab(x_max, y_max);
	tablet = new Tablet(x_max, y_max);
	cave = new Cave(x_max, y_max);
	ruin = new Ruin(x_max, y_max);
}

//int x_p, int y_p, int x_t, int y_t, int x_c, int y_c, int x_r, int y_r