#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <GAME/engine/GameObject.hpp>
#include <GAME/graphics/ShapeDrawer.hpp>
#include <GAME/engine/BoardListener.hpp>

class Unit;

class Neutral : public GameObject {
private:
	const sf::Texture *_texture = nullptr;
	ShapeDrawer _shapeDrawer;
	int _effectDistance = 0;
	
	void validateShapeDrawer();
public:
	Neutral();
	Neutral(const Neutral& from);

	void effectDistance(int distance);
	int effectDistance();

	void texture(const sf::Texture* texture);
	const sf::Texture* texture() const;

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual bool onClick(sf::Vector2i& cell) override;
	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onObjectAttached(GameObject& object) override;
	virtual void onObjectMoved(GameObject& object, sf::Vector2i& from, sf::Vector2i& to) override;

	virtual void onUnitEntered(Unit& unit) {}
	virtual GameObject* copy() { return nullptr; }
};