#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include <vector>
class SnowBall
{

public:
	SnowBall(sf::Texture *texture, sf::Vector2f position, float speed, bool isRight);
	~SnowBall();


	float topBall, rightBall, leftBall, bottomBall;
	float _speedBall;
	bool isOutside(sf::Vector2f pos);
	void UpdateBall();
	void DrawWindow(sf::RenderWindow& window);
	sf::RectangleShape ball;
};