#include "NtrlStrategies.h"

NtrlObjEffect HillingStrategy::effect(int n)
{
	return { n, EffectTypes::hp };
}

NtrlObjEffect BaffDamageStrategy::effect(int n)
{
	return { n, EffectTypes::damage };
}

NtrlObjEffect BaffRangeStrategy::effect(int n)
{
	return { n, EffectTypes::range };
}