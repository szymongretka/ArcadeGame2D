#pragma once
#include "Animation.h"
#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpSpeed, float jumpHeight);
	~Player();

	void UpdatePlayer(float deltaTime);
	void DrawWindow(sf::RenderWindow& window);
	
	sf::RectangleShape body;
	float top, right, left, bottom;
	float _jumpSpeed;
	float _speed;
	float platform;
	float _jumpHeight;

	bool canJump;
	bool canFall;

	bool isRight();

private:

	const float gravity = 981.0f;
	Animation animation;
	unsigned int row;
	bool faceRight;
};

