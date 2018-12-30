#include "Player.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>



Player::Player()
{
}

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpSpeed, float jumpHeight): animation(texture, imageCount, switchTime)
{

	_speed = speed;
	row = 0;
	faceRight = true;
	_jumpSpeed = jumpSpeed;
	_jumpHeight = jumpHeight;

	body.setSize(sf::Vector2f(75.0f, 100.0f));
	body.setTexture(texture);
	canFall = true;
}

Player::~Player()
{
}

void Player::UpdatePlayer(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= _speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += _speed * deltaTime;
	}
	

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (canJump))
	{
		canFall = true;	
		movement.y = -sqrt(5.0f * gravity *  _jumpSpeed) * deltaTime;
	}
	

	if(canFall)
	{
		movement.y += gravity * deltaTime;
	}

	else
	{
		body.setPosition(body.getPosition().x, platform);
		movement.y = 0;

	}

	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (movement.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}

	if (movement.y < 0.0f || movement.y > 0.0f)
	{
		row = 2;
	}

	animation.updateAnimation(row, deltaTime, faceRight);
	body.setTextureRect(animation.textureRect);


	bottom = body.getPosition().y + body.getSize().y;
	left = body.getPosition().x;
	right = body.getPosition().x + body.getSize().x;
	top = body.getPosition().y;

	body.move(movement);

	_jumpSpeed = 550.0f;
	_speed = 350.0f;
	canFall = true;
}


void Player::DrawWindow(sf::RenderWindow& window)
{
	window.draw(body);
}

bool Player::isRight() 
{
	return faceRight;
}
