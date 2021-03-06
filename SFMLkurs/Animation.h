#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation();
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	sf::IntRect textureRect; //this is used in order to display the animation

	void updateAnimation(int row, float deltaTime, bool faceRight);


private:

	sf::Vector2u _imageCount; //store amount of images in each row
	sf::Vector2u currentImage;
	
	float totalTime;
	float _switchTime; //amount of time to switch the image
	
};

