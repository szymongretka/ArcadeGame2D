#pragma once
#include <iostream>
#include "Player.h"
#include <SFML\Graphics.hpp>
#include "AnimationEnemy.h"
#include <vector>

class Enemy: public Player
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speedEnemy);

	~Enemy();

	bool Collision(Enemy p, Player p1);
	bool endingGame(Enemy p, Player p1);
	bool goRight;

	void UpdateEnemy(float deltaTime);
	void DrawWindow(sf::RenderWindow& window);

	float _speedEnemy = 100.0f;
	float topEnemy, rightEnemy, leftEnemy, bottomEnemy;

	sf::RectangleShape rect;


private:

	std::vector<int> HP;
	unsigned int row;
	bool faceRight;
	AnimationEnemy animationE;
	Player player;

};