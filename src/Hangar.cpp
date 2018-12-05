#include "Hangar.hpp"

Hangar::Hangar(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 0.f, 0, 0, 0, 40, sf::Vector2f(1.0f, 0.0f), team){ }

