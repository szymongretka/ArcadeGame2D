#include "AnimationEnemy.h"



AnimationEnemy::AnimationEnemy()
{
}

AnimationEnemy::AnimationEnemy(sf::Texture * texture, sf::Vector2u imageCount, float switchTime)
{
	_imageCount = imageCount;
	_switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0;

	textureRect.width = 180;
	textureRect.height = 247.5;
}


AnimationEnemy::~AnimationEnemy()
{
}

void AnimationEnemy::updateAnimationEnemy(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= _switchTime)
	{
		totalTime -= _switchTime;
		currentImage.x++;

		if (currentImage.x >= _imageCount.x)
		{
			currentImage.x = 0;
		}
	}


	if (faceRight)
	{
		textureRect.left = currentImage.x * textureRect.width;
		textureRect.width = abs(textureRect.width);
	}
	else
	{
		textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
		textureRect.width = -abs(textureRect.width);
	}

	textureRect.top = currentImage.y * textureRect.height;
}
