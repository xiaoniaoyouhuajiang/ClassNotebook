#pragma once

#include <map>

#include <GAME/engine/Unit.hpp>
#include <GAME/engine/BoardListener.hpp>
#include <GAME/engine/Interceptor.hpp>
#include <GAME/engine/Info.hpp>

using std::map;

class Home : public Unit {
private:
	static const int MAX_UNITS_COUT = 10;
	set<int> _children;
	map<sf::Keyboard::Key, int> _keyToUnit;
	shared_ptr<Unit> _selectedUnitInstance;
	int _selectedUnit = Info::BUM_SOLDIER;

	void validateSelectedUnitInstance();

public:
	Home(int squad);
	Home(const Home& from);
	~Home();

	virtual bool onClick(sf::Vector2i& cell) override;
	virtual bool onKeyPressed(sf::Event key) override;

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onObjectAttached(GameObject& object) override;
	virtual void onObjectDetached(GameObject& object) override;

	virtual int info() const override;
};