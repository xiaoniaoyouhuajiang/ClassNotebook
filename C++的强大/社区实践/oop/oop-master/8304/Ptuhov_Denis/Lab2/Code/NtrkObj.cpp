#include "NtrkObj.h"

std::vector<char> HillingWaterFall::who()
{
	return { 'S', 'W', 'M', 'X', 'A', 'R' };
}

NtrlObjEffect HillingWaterFall::get()
{
	return stg.effect(20);
}

std::vector<char> Trap::who()
{
	return { 'S', 'W', 'M', 'X', 'A', 'R' };
}

NtrlObjEffect Trap::get()
{
	return stg.effect(-20);
}

std::vector<char> PowerStatue::who()
{
	return {'W', 'X', 'R', 'S'};
}

NtrlObjEffect PowerStatue::get()
{
	return stg.effect(10);
}

std::vector<char> InsightStatue::who()
{
	return { 'S', 'A', 'M' };
}

NtrlObjEffect InsightStatue::get()
{
	return stg.effect(1);
}
