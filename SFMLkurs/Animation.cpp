#include "Animation.h"



Animation::Animation()
{
}

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	_imageCount = imageCount;
	_switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0;

	textureRect.width = 56;
	textureRect.height = 80;
}

Animation::~Animation()
{
}

void Animation::updateAnimation(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= _switchTime)
	{
		totalTime -= _switchTime; // totaltime will never be equal to switch time
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
