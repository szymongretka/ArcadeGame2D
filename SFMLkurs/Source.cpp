#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Enemy.h"
#include "Player.h"
#include "SnowBall.h"
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>

std::vector<SnowBall> balls;
std::vector<Enemy> enemies;
std::vector<std::vector<int>> CollMap;

void LoadCollisionMap(const char*filename)
{
	std::ifstream openfile(filename);
	std::vector<int> tempMap;
	CollMap.clear();

	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			std::string str, value;
			std::getline(openfile, str);//gets line from stream into a string
			std::stringstream stream(str); //operates on strings, objects of this class use a string buffer that contains a sequence of characters
											//this sequence  can be accessed directly as a string object
			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					int a = atoi(value.c_str());//taking string and converting it into integer
					tempMap.push_back(a);

				}
			}
			CollMap.push_back(tempMap);
			tempMap.clear();
		}
	}
}

int main()
{
	int shoot = 0;
	int shootDelay = 50;

	bool menuIsOpen = true;
	bool pause = false;
	bool endGame = false;
	bool isDead = false;
	bool isDead2 = false;

	LoadCollisionMap("CollisionMap.txt"); //Collision map

	sf::Vector2i screenDimensions(1280, 720);
	sf::RenderWindow Screen;
	Screen.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Arcade Game!");

	Menu menu(1280, 720);
	
	sf::Music music;
	sf::SoundBuffer soundbuffer;
	sf::Sound sound;
	soundbuffer.loadFromFile("throw.wav");
	sound.setBuffer(soundbuffer);
	music.openFromFile("forest.ogg");
	music.setVolume(10);
	music.play();


	sf::Texture background;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture endingGameTexture;
	sf::Texture snowball;

	sf::Sprite Picture;
	sf::Sprite EndingGame;

	background.loadFromFile("background.png");
	playerTexture.loadFromFile("Tux.png");
	enemyTexture.loadFromFile("tester.png");
	endingGameTexture.loadFromFile("black.png");
	snowball.loadFromFile("Snowball.png");


	Picture.setTexture(background);
	Picture.setScale(1.0f, (float)screenDimensions.y / background.getSize().y);

	EndingGame.setTexture(endingGameTexture);


	Player player(&playerTexture, sf::Vector2u(3, 9),0.3f, 350.0f, 550.0f, 300.0f);
	player.body.setPosition(100.f, 0.0f);


	Enemy enemy(&enemyTexture, sf::Vector2u(2, 5), 0.3f, 100.0f);
	Enemy enemy2(&enemyTexture, sf::Vector2u(2, 5), 0.3f, 100.0f);

	enemy.rect.setPosition(3800.0f, 620.0f);
	enemy2.rect.setPosition(1500.0f, 620.0f);

	enemies.push_back(enemy);
	enemies.push_back(enemy2);


	Enemy end(&enemyTexture, sf::Vector2u(0, 0), 0.0f, 0.0f);
	end.rect.setPosition(7020.0f, 480.0f);



	float deltaTime = 0.0f;
	sf::Clock clock;
	


	sf::View view;
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y)); // sets initial bounds of the screen which we want to view
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //gives the ratio of the displayed view

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

	
	while (Screen.isOpen()) //main loop 
	{

		sf::Event event;


		if ((menuIsOpen) && (!endGame))
		{
			
			while (Screen.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							menuIsOpen = false;
							break;
						case 1:
							std::cout << "Credit button has been pressed" << std::endl;
							break;
						case 2:
							Screen.close();
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					Screen.close();

					break;

				}
			}


			Screen.clear();

			menu.draw(Screen);

			Screen.display();

		}

		if (pause)
		{

			while (Screen.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							pause = false;
							break;
						case 1:
							std::cout << "Option button has been pressed" << std::endl;
							break;
						case 2:
							Screen.close();
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					Screen.close();

					break;

				}
			}
			

			Screen.clear(sf::Color::Black);

			menu.draw(Screen);

			Screen.display();
		}

		if ((endGame) && (!menuIsOpen))
		{


			while (Screen.pollEvent(event))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{

					menuIsOpen = true;
					endGame = false;
				}
			
			}

			isDead = false;
			isDead2 = false;

			Screen.clear(sf::Color::Black);

			Screen.draw(EndingGame);

			Screen.display();
			
		}

		deltaTime = clock.restart().asSeconds();

		if ((!menuIsOpen) && (!pause) && (!endGame))
		{

		

		if (shoot < shootDelay)
		{
			shoot++;
		}

		while (Screen.pollEvent(event))
		{

			if (event.type == sf::Event::Closed) //button responsible for closing game was pushed
				Screen.close(); //close the game

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				pause = true;
			



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{

				if (shoot >= shootDelay)
				{
					balls.push_back(SnowBall(&snowball, { player.body.getPosition().x, player.body.getPosition().y + player.body.getSize().y / 2 }, 10.0f, player.isRight()));
					shoot = 0;
					sound.play();
				}
				
			}


		}


		//
		end.UpdateEnemy(deltaTime);

		enemy.UpdateEnemy(deltaTime);
		enemy2.UpdateEnemy(deltaTime);

		player.UpdatePlayer(deltaTime);


		//collision with map for a player

		for (int i = 0; i < CollMap.size(); i++)
		{
			for (int j = 0; j < CollMap[i].size(); j++)
			{

				int CollBottom, CollRight, CollLeft, CollTop;
				CollBottom = i * 32 + 32;
				CollTop = i * 32;
				CollLeft = j * 32;
				CollRight = j * 32 + 32;

				if (player.right < CollLeft || player.left > CollRight || player.top > CollBottom || player.bottom < CollTop)
				{
					//no collision
				}
				else
				{
					if (CollMap[i][j] == 3)
					{
						if (player.bottom > CollTop)
						{
							player.canFall = false;
							player.canJump = true;
							player.body.setPosition(player.body.getPosition().x, player.platform = player.body.getPosition().y);
							break;
						}
					}
					if (CollMap[i][j] == 2)
					{
						if (player.left < CollRight)
						{
							player.body.setPosition(player.body.getPosition().x + 1, player.body.getPosition().y);
							player._speed -= player._speed;
							break;
						}
					}
					if (CollMap[i][j] == 1)
					{
						if (player.right > CollLeft)
						{
							player.body.setPosition(player.body.getPosition().x - 1, player.body.getPosition().y);
							player._speed -= player._speed;
							break;
						}
					}
					if (CollMap[i][j] == 4)
					{
						if (player.top < CollBottom)
						{
							player.canJump = false;
							player._jumpSpeed -= player._jumpSpeed;
							break;
						}
					}
				}

			}
		}



		if (isDead)
		{
			enemy.rect.setPosition(-100.0f, -100.0f);
		}
		if (isDead2)
		{
			enemy2.rect.setPosition(-100.0f, -100.0f);
		}



		if (enemy.Collision(enemy, player))
		{
			player.body.setPosition(50.0f, 0.0f);
		}
		if (enemy2.Collision(enemy2, player))
		{
			player.body.setPosition(50.0f, 500.0f);
		}
		if (end.endingGame(end, player))
		{
			endGame = true;
			player.body.setPosition(100.0f, 0.0f);
		}

		if (player.body.getPosition().y > 840.0f)
		{
			player.body.setPosition(100.0f, 0.0f);
		}

		//collision with map for an enemy
		for (size_t k = 0; k < enemies.size(); k++)
		{



			for (int i = 0; i < CollMap.size(); i++)
			{
				for (int j = 0; j < CollMap[i].size(); j++)
				{

					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;


					if (enemies[k].rightEnemy < CollLeft || enemies[k].leftEnemy > CollRight || enemies[k].topEnemy > CollBottom || enemies[k].bottomEnemy < CollTop)	
					{
						//nothing
					}
					else
					{
						if (CollMap[i][j] == 1)
						{
							if (enemies[k].rightEnemy > CollLeft)
							{
								enemies[k].goRight = false;
								//break;
							}

						}

						if (CollMap[i][j] == 2)
						{
							if (enemies[k].leftEnemy < CollRight)
							{
								enemies[k].goRight = true;
								//break;
							}

						}

					}

				}
			}
		}




		/*for (int i = 0; i < CollMap.size(); i++)
		{
			for (int j = 0; j < CollMap[i].size(); j++)
			{

				int CollBottom, CollRight, CollLeft, CollTop;
				CollBottom = i * 32 + 32;
				CollTop = i * 32;
				CollLeft = j * 32;
				CollRight = j * 32 + 32;

				if ((enemy.rightEnemy < CollLeft || enemy.leftEnemy > CollRight || enemy.topEnemy > CollBottom || enemy.bottomEnemy < CollTop) && 
					(enemy2.rightEnemy < CollLeft || enemy2.leftEnemy > CollRight || enemy2.topEnemy > CollBottom || enemy2.bottomEnemy < CollTop))
				{
					//nothing
				}
				else
				{
					if (CollMap[i][j] == 1)
					{
						if (enemy.rightEnemy > CollLeft)
						{
							enemy.goRight = false;
							//break;
						}
						if (enemy2.rightEnemy > CollLeft)
						{
							enemy2.goRight = false;
							//break;
						}

					}

					if (CollMap[i][j] == 2)
					{
						if (enemy.leftEnemy < CollRight)
						{
							enemy.goRight = true;
							//break;
						}
						if (enemy2.leftEnemy < CollRight)
						{
							enemy2.goRight = true;
							//break;
						}

					}

				}

			}
		}*/






		if (player.body.getPosition().y < player.platform - player._jumpHeight)
		{
			player.canJump = false;
		}



		if (player.body.getPosition().x + 50 > screenDimensions.x / 2)
			position.x = player.body.getPosition().x + 100;
		else
			position.x = screenDimensions.x / 2;

		/*if (player.body.getPosition().y + 75 < screenDimensions.y / 2)
			position.y = player.body.getPosition().y + 150;
		else
			position.y = screenDimensions.y / 2;*/

		view.setCenter(position); //when player reaches half of the screen it starts scrolling
		Screen.setView(view);
		Screen.clear(sf::Color::Black);
		Screen.draw(Picture);

		player.DrawWindow(Screen);
		enemy.DrawWindow(Screen);
		enemy2.DrawWindow(Screen);


		for (size_t i = 0; i < balls.size(); i++)
		{


			balls[i].UpdateBall();
			balls[i].DrawWindow(Screen);

			/*for (int j = 0; j < CollMap.size(); j++)
			{
				for (int k = 0; k < CollMap[j].size(); k++)
				{
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (balls[i].rightBall < CollLeft || balls[i].leftBall > CollRight || balls[i].topBall > CollBottom || balls[i].bottomBall < CollTop)
					{
						//nothing
					}
					else
					{
						if (CollMap[i][j] == 1)
						{
							if (balls[i].rightBall > CollLeft)
							{
								balls.erase(balls.begin() + i);
								std::cout << "trafienie" << std::endl;
								break;
							}


						}
						if (CollMap[i][j] == 2)
						{
							if (balls[i].leftBall < CollRight)
							{
								balls.erase(balls.begin() + i);
								std::cout << "trafienie" << std::endl;
								break;
							}

						}



					}

				}
			}*/

			if (balls[i].isOutside(player.body.getPosition())) 
			{
				balls.erase(balls.begin() + i);
				break;
			}
		
				if (balls[i].ball.getGlobalBounds().intersects(enemy.rect.getGlobalBounds())) 
				{
					isDead = true;
					balls.erase(balls.begin() + i);
					break;
				}
				if (balls[i].ball.getGlobalBounds().intersects(enemy2.rect.getGlobalBounds()))
				{
					isDead2 = true;
					balls.erase(balls.begin() + i);
					break;
				}




		}


		Screen.display();

		}

	}

	return 0;
}
