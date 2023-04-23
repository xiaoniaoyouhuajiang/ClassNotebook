#include "NtrkObj.h"

HillingWaterFall::HillingWaterFall()
{
	name = 'W';
}

std::vector<char> HillingWaterFall::who()
{
	return { 'S', 'W', 'M', 'X', 'A', 'R' };
}

NtrlObjEffect HillingWaterFall::get()
{
	return stg.effect(20);
}

Trap::Trap()
{
	name = 'T';
}

std::vector<char> Trap::who()
{
	return { 'S', 'W', 'M', 'X', 'A', 'R' };
}

NtrlObjEffect Trap::get()
{
	return stg.effect(-20);
}

PowerStatue::PowerStatue()
{
	name = 'P';
}

std::vector<char> PowerStatue::who()
{
	return {'W', 'X', 'R', 'S'};
}

NtrlObjEffect PowerStatue::get()
{
	return stg.effect(10);
}

InsightStatue::InsightStatue()
{
	name = 'I';
}

std::vector<char> InsightStatue::who()
{
	return { 'S', 'A', 'M' };
}

NtrlObjEffect InsightStatue::get()
{
	return stg.effect(1);
}

char NtrlObjNameExpansion::getName()
{
	return name;
}
