#include "Enemy.h"
#include "AnimationEnemy.h"


Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speedEnemy): animationE(texture, imageCount, switchTime)
{
	_speedEnemy = speedEnemy;
	row = 0;
	faceRight = true;
	goRight = true;

	rect.setSize(sf::Vector2f(75.0f, 100.0f));
	rect.setTexture(texture);
}

Enemy::~Enemy()
{
}

bool Enemy::Collision(Enemy p, Player p1)
{
	if ((right < p.leftEnemy || left > p.rightEnemy || top > p.bottomEnemy || bottom < p.topEnemy) &&
		(rightEnemy < p1.left || leftEnemy > p1.right || topEnemy > p1.bottom || bottomEnemy < p1.top))
	{
		return false;
	}
	return true;
}

void Enemy::UpdateEnemy(float deltaTime)
{
	sf::Vector2f movementEnemy(0.0f, 0.0f);



	if ((_speedEnemy > 0.0f) && (goRight))
		movementEnemy.x += _speedEnemy * deltaTime;

	else
		movementEnemy.x -= _speedEnemy *deltaTime;
	



	if(movementEnemy.x > 0.0f || movementEnemy.x < 0.0f)
	{
		row = 0;

		if (movementEnemy.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}


	animationE.updateAnimationEnemy(row, deltaTime, faceRight);
	rect.setTextureRect(animationE.textureRect);
	
	
	bottomEnemy = rect.getPosition().y + rect.getSize().y;
	leftEnemy = rect.getPosition().x;
	rightEnemy = rect.getPosition().x + rect.getSize().x;
	topEnemy = rect.getPosition().y;
	
	rect.move(movementEnemy);


	//_speedEnemy = 100.0f;
}

void Enemy::DrawWindow(sf::RenderWindow & window)
{
	window.draw(rect);
}

bool Enemy::endingGame(Enemy p, Player p1)
{
	if ((right < p.leftEnemy || left > p.rightEnemy || top > p.bottomEnemy || bottom < p.topEnemy) &&
		(rightEnemy < p1.left || leftEnemy > p1.right || topEnemy > p1.bottom || bottomEnemy < p1.top))
	{
		return false;
	}
	return true;
}



