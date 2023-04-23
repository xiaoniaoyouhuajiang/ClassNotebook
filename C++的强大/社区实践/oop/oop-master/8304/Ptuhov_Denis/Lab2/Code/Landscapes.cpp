#include "Landscapes.h"

std::vector<char> Ground::who()
{
	return { 'W', 'R', 'S' };
}

LandscapeInfo Ground::how(char c)
{
	if (c == 'W' || c == 'S')
		return { 10, EffectTypes::damage};

	return { 1, EffectTypes::range};
}

std::vector<char> Mountain::who()
{
	return { 'S', 'W', 'M', 'X', 'A', 'R' };
}

LandscapeInfo Mountain::how(char c)
{
	if (c == 'A' || c == 'M')
		return { 30, EffectTypes::damage};

	return { -15, EffectTypes::damage};
}

std::vector<char> Swamp::who()
{
	return { 'S', 'W', 'R', 'X' };
}

LandscapeInfo Swamp::how(char c)
{
	return { -15, EffectTypes::hp};
}

LandscapeInfo LandscapeProxy::get(LandscapeTypes type, char c)
{
	auto elem = std::make_pair(type, c);
	if (d.find(elem) != d.end())
		return d[elem];


	switch (type)
	{
		case LandscapeTypes::ground:
		{
			Ground gr;
			std::vector<char> elements = gr.who();
			if (std::find(elements.begin(), elements.end(), elem.second) == elements.end())
				return { 0, EffectTypes::damage };

			d[elem] = gr.how(elem.second);
			break;
		}
		case LandscapeTypes::mountain:
		{	
			Mountain gr;
			std::vector<char> elements = gr.who();
			if (std::find(elements.begin(), elements.end(), elem.second) == elements.end())
				return { 0, EffectTypes::damage };

			d[elem] = gr.how(elem.second);
			break;
		}
		case LandscapeTypes::swamp:
		{
			Swamp gr;
			std::vector<char> elements = gr.who();
			if (std::find(elements.begin(), elements.end(), elem.second) == elements.end())
				return { 0, EffectTypes::damage};

			d[elem] = gr.how(elem.second);
			break;
		}
	}

	return d[elem];

}
