#include "SnowBall.h"
#include <iostream>
#include <vector>

SnowBall::SnowBall(sf::Texture * texture, sf::Vector2f position, float speedBall, bool isRight)
{


	ball.setPosition(position);
	ball.setSize(sf::Vector2f(20.f, 20.f));
	ball.setTexture(texture);

	if (isRight)
		_speedBall = speedBall;
	else
		_speedBall = -speedBall;
}

void SnowBall::UpdateBall()
{

	bottomBall = ball.getPosition().y + ball.getSize().y;
	leftBall = ball.getPosition().x;
	rightBall = ball.getPosition().x + ball.getSize().x;
	topBall = ball.getPosition().y;

	ball.move({ _speedBall, 0.0f });
}

void SnowBall::DrawWindow(sf::RenderWindow & window)
{
	window.draw(ball);
}
bool SnowBall::isOutside(sf::Vector2f pos)
{
	if (ball.getPosition().x > pos.x + 280.0f)
	{
		return true;
	}
	else
		return false;
}
SnowBall::~SnowBall()
{
}
