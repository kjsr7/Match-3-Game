#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;
int ts = 60; 
Vector2i offset(36,20);

struct piece
{
	int x, y, col, row, kind, match, alpha;
	piece() { match = 0; alpha = 255; }
} box[9][9];

void swap(piece p1, piece p2)
{
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	box[p1.row][p1.col] = p1;
	box[p2.row][p2.col] = p2;
}


int main()
{
	sf::Music music;
	music.openFromFile("Faded - Alan Walker (Jaca Remix).wav");
	music.play();
	

	sf::Font font;
	font.loadFromFile("arial.ttf");

	int tot = 0;
	srand((unsigned int)time(NULL));
	

	RenderWindow app(VideoMode(780, 550), "EA GAME");
	app.setFramerateLimit(100);
	Texture sh1, sh2, sh3, sh4, sh5, b;
	sh5.loadFromFile("Triangle.png");
	sh4.loadFromFile("Square.png");
	sh3.loadFromFile("Hexagon.png");
	sh2.loadFromFile("Dode.png");
	sh1.loadFromFile("Diamond.png");
	b.loadFromFile("background.jpg");
	sh1.setSmooth(true);
	sh2.setSmooth(true);
	sh3.setSmooth(true);
	sh4.setSmooth(true);
	sh5.setSmooth(true);
	b.setSmooth(true);
	Sprite background(b),gems1(sh1), gems2(sh2), gems3(sh3), gems4(sh4), gems5(sh5);

	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			box[i][j].kind = rand() % 5;
			box[i][j].col = j;
			box[i][j].row = i;
			box[i][j].x = j*ts;
			box[i][j].y = i*ts;
		}
	int c = 0;
	int init_check = 0;
	while (1)
	{
		c = 0;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				if (box[i][j].kind == box[i + 1][j].kind)
					if (box[i][j].kind == box[i - 1][j].kind)

						++c;
				if (box[i][j].kind == box[i][j + 1].kind)
					if (box[i][j].kind == box[i][j - 1].kind)
						++c;
			}
		if (c == 0)
			break;
		else
		{
			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
				{
					box[i][j].kind = rand() % 5;
				}
		}


	}

	int x0, y0, x, y; int click = 0; Vector2i pos;
	bool isSwap = false, isMoving = false;
	int totm = 30;
	while (app.isOpen())
	{
		if (totm == 0)
		{
			sf::Text text3,text4,text5,text6;
			text3.setFont(font);
			text4.setFont(font);
			text5.setFont(font);
			text6.setFont(font);
			std::string t = to_string(tot);

			text3.setString("YOU HAD RUN OUT OF MOVES");
			text5.setString("YOUR SCORE WAS");
			text6.setString(t);


			text4.setString("CLICK CLOSE TO RESTART");
			text3.setCharacterSize(28);
			text4.setCharacterSize(28);
			text5.setCharacterSize(28);
			text6.setCharacterSize(28);


			text3.setFillColor(sf::Color::Red);
			text4.setFillColor(sf::Color::Green);
			text5.setFillColor(sf::Color::Yellow);
			text6.setFillColor(sf::Color::Magenta);



			text3.setPosition(150, 300);
			text5.setPosition(150, 350);
			text6.setPosition(150, 400);
			text4.setPosition(150, 450);

			app.clear(sf::Color::Black);
			background.setScale(100, 100);

			app.draw(background);
			app.draw(text3);
			app.draw(text4);
			app.draw(text5);
			app.draw(text6);
			app.display();
			Event e;
			while (app.pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					totm = 30; tot = 0;
				}
			}
		}
		else
		{
			Event e;
			while (app.pollEvent(e))
			{
				switch (e.type)
				{

				case sf::Event::Closed:
					app.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (e.key.code == Mouse::Left)
					{
						if (!isSwap && !isMoving) click++;
						pos = Mouse::getPosition(app) - offset;
					}
					break;
				}
			}

			if (click == 1)
			{
				x0 = pos.x / ts + 1;
				y0 = pos.y / ts + 1;
			}
			if (click == 2)
			{
				x = pos.x / ts + 1;
				y = pos.y / ts + 1;
				if (abs(x - x0) + abs(y - y0) == 1)
				{
					--totm;
					swap(box[y0][x0], box[y][x]); isSwap = 1; click = 0;
				}
				else click = 1;
			}
			int count = 0;
			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
				{
					if (box[i][j].kind == box[i + 1][j].kind)
						if (box[i][j].kind == box[i - 1][j].kind)
						{
							for (int n = -1; n <= 1; n++)
								box[i + n][j].match = 1;
							++count;

						}

					if (box[i][j].kind == box[i][j + 1].kind)
						if (box[i][j].kind == box[i][j - 1].kind)
						{
							for (int n = -1; n <= 1; n++) box[i][j + n].match = 1;
							++count;
						}
				}
			if (count == 1 && !isMoving)
				tot += 10;
			if (count > 1 && !isMoving)

				tot += 30;

	        sf::Text text, text2, textm, texts;
			text.setFont(font); 
			text2.setFont(font);
			textm.setFont(font);
			texts.setFont(font);

			text.setString(std::to_string(tot));
			text2.setString(std::to_string(totm));
			textm.setString("Moves Left");
			texts.setString("SCORE");
			text.setCharacterSize(24); 						  
			text2.setCharacterSize(24);
			textm.setCharacterSize(28);
			texts.setCharacterSize(28);
			text.setFillColor(sf::Color::Green);
			text2.setFillColor(sf::Color::Red);
			textm.setFillColor(sf::Color::Red);
			texts.setFillColor(sf::Color::Green);

			textm.setPosition(600, 250);
			text2.setPosition(600, 300);
			texts.setPosition(600, 350);
			text.setPosition(600, 400);
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			isMoving = false;
			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
				{
					piece &p = box[i][j];
					int dx, dy;
					for (int n = 0; n < 3; n++)  
					{
						dx = p.x - p.col*ts;
						dy = p.y - p.row*ts;
						if (dx) p.x -= dx / abs(dx);
						if (dy) p.y -= dy / abs(dy);
					}
					if (dx || dy) isMoving = 1;
				}

			if (!isMoving)
				for (int i = 1; i <= 8; i++)
					for (int j = 1; j <= 8; j++)
						if (box[i][j].match) if (box[i][j].alpha > 10) { box[i][j].alpha -= 10; isMoving = true; }

			if (isSwap && !isMoving)
			{
				if (!count) swap(box[y0][x0], box[y][x]); isSwap = 0;
			}
			if (!isMoving)
			{
				for (int i = 8; i > 0; i--)
					for (int j = 1; j <= 8; j++)
						if (box[i][j].match)
							for (int n = i; n > 0; n--)
								if (!box[n][j].match) { swap(box[n][j], box[i][j]); break; };

				for (int j = 1; j <= 8; j++)
					for (int i = 8, n = 0; i > 0; i--)
						if (box[i][j].match)
						{
							box[i][j].kind = rand() % 5;
							box[i][j].y = -ts*n++;
							box[i][j].match = 0;
							box[i][j].alpha = 255;
						}
			}


			app.clear(sf::Color::Black);
			background.setScale(100, 100);

			app.draw(background);
			app.draw(text2);
			app.draw(textm);
			app.draw(texts);

			app.draw(text);

			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
				{
					piece p = box[i][j];
					switch (p.kind)
					{
					case 0: 				gems1.setTextureRect(IntRect(0, 0, 100, 100));
						gems1.setColor(Color(255, 255, 255, p.alpha));
						gems1.setPosition((float)p.x, (float)p.y);
						gems1.move((float)(offset.x - ts), (float)(offset.y - ts));
						app.draw(gems1); break;
					case 1: 				gems2.setTextureRect(IntRect(0, 0, 100, 100));
						gems2.setColor(Color(255, 255, 255, p.alpha));
						gems2.setPosition((float)p.x, (float)p.y);
						gems2.move((float)(offset.x - ts), (float)(offset.y - ts));
						app.draw(gems2); break;
					case 2: 				gems3.setTextureRect(IntRect(0, 0, 100, 100));
						gems3.setColor(Color(255, 255, 255, p.alpha));
						gems3.setPosition((float)p.x, (float)p.y);
						gems3.move((float)(offset.x - ts), (float)(offset.y - ts));
						app.draw(gems3); break;
					case 3: 				gems4.setTextureRect(IntRect(0, 0, 100, 100));
						gems4.setColor(Color(255, 255, 255, p.alpha));
						gems4.setPosition((float)p.x, (float)p.y);
						gems4.move((float)(offset.x - ts), (float)(offset.y - ts));
						app.draw(gems4); break;
					case 4: 				gems5.setTextureRect(IntRect(0, 0, 100, 100));
						gems5.setColor(Color(255, 255, 255, p.alpha));
						gems5.setPosition((float)p.x, (float)p.y);
						gems5.move((float)(offset.x - ts), (float)(offset.y - ts));
						app.draw(gems5);
						break;

					}

				}

			app.display();
		}
	}
	return 0;
}
