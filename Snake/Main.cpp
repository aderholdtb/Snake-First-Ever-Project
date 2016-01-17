// SFML TEST.cpp : Defines the entry point for the console application.//
#include"stdafx.h"
#include<cstdlib>
#include<ctime>
#include<vector>
#include<string>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

static std::vector<sf::RectangleShape> Robjects;
static std::vector<sf::RectangleShape> egger;
static sf::RenderWindow window(sf::VideoMode(600, 500), "");;
static sf::RectangleShape square;
static sf::Event event;
static sf::Text score, gameOver, playButton, snake, menuButton, exitButton, HighName, CreatedBy;
static sf::Text HighScore, HighScoreTitle, HighButton, enterName, nameEnter, invincible3;
static sf::RectangleShape egg;
static std::string text;
static sf::Font font;
static int score1 = 0, counter = 0;
static bool invincible1 = false;
static bool invincible = false;
static bool eggs = false;
static bool eggs1 = false;
static bool killTail = false;
static sf::Clock clockInvincible;
static sf::Time elapsedInvincible;
static float timeInv;

const float sizex = 18;
const float sizey = 18;
const int speed = 1;
void highScores();
bool checkBlock(int xS, int yS, int xB, int yB);
void keepMoving(int direction, int& x, int& y);
bool addHighScores();

void invincible2(int& xBlock, int& yBlock)
{
	if(xBlock > 605 - sizex){
		xBlock = 0;
	}
	else if(xBlock <= 0){
		xBlock = 600 - sizex;
	}
	else if(yBlock > 505 - sizey){
		yBlock = 0;
	}
	else if(yBlock <= 0){
		yBlock = 500 - sizey;
	}
}
void setColor(int counters, int speeds)
{
	     if(counter % speeds == 0){
		for(int i = 0; i < Robjects.size(); i++){
	Robjects[i].setFillColor(sf::Color(61, 245, 0));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(42, 160, 0));
	}
			}
			else{
	   for(int i = 0; i < Robjects.size(); i++){
	Robjects[i].setFillColor(sf::Color(200, 50, 50));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(40, 40, 40));
		}
	}
}
void setEgg(int& red, int& green, int& blue)
{
	char w, r, g, y, b, p;
	int choice = 0;
	srand(time(NULL));

	for(int i = 0; i < 1500; i++)
	choice = 1 + rand() % 100;

	if(choice < 61){
		red = 150;
		green = 150;
		blue = 150;
	}
	else if(choice < 71){
		red = 200;
		green = 40;
		blue = 40;
	}
	else if(choice < 79){
		red = 40;
		green = 200;
		blue = 40;
	}
	else if(choice < 86){
		red = 204;
		green = 255;
		blue = 51;
	}
	else if(choice < 91){
		red = 41;
		green = 40;
		blue = 200;
	}
	else if(choice < 94){
		red = 205;
		green = 51;
		blue = 255;
	}
	else if (choice < 96){
		invincible = true;
		red = 0;
		green = 0;
		blue = 0;
	}
	else if(choice < 98){
		red = 30;
		green = 255;
		blue = 30;
		killTail = true;
	}
	else {
		red = 255;
		green = 255;
		blue = 255;
		eggs1 = true;
	}
}
std::string convertInt(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}
void AddTail(int direction, int xPrev,int yPrev)
{
	sf::RectangleShape square1(sf::Vector2f(sizex, sizey));
	float xNew, yNew;

	if(direction == 1){
			xNew = xPrev + sizex + 10;
			square1.setPosition(xNew,yPrev);
		}
		else if(direction == 2){
			xNew = xPrev - (sizex + 10);
			square1.setPosition(xNew,yPrev);
		}
		else if(direction == 3){
			yNew = yPrev + sizey + 10;
			square1.setPosition(xPrev,yNew);
	    }
		else if(direction == 4){
			yNew = yPrev - (sizey + 10);
			square1.setPosition(xPrev,yNew);
		}
    square1.setFillColor(sf::Color(61, 245, 0));
	square1.setOutlineThickness(2);
    square1.setOutlineColor(sf::Color(42, 160, 0));

	Robjects.push_back(square1);

}
int CreateTail(int xPrev, int yPrev, int direction, bool& checkGameOver, bool add)
{
	int xNew, yNew, x , y;
	int firstx = xPrev, firsty = yPrev;
	int prevDirection = direction;

	for(int i = 0; i < Robjects.size(); i++)
	{
		sf::Vector2f position = Robjects[i].getPosition();	
	xNew = position.x;
	yNew = position.y;

  if((yNew < yPrev + 1)&&(yNew > yPrev - 1)) {
		if(prevDirection == 1){
			if((invincible1 == true)&&(xPrev > xNew)){
			    xNew = xNew - speed;
				invincible2(xNew, yNew);
				Robjects[i].setPosition(xNew , yNew);
			}
			else{
			xNew = xPrev + sizex + 10;
			Robjects[i].setPosition(xNew , yPrev);
			}
		}
		else if(prevDirection == 2){
			if((invincible1 == true)&&(xPrev < xNew)){
			    xNew = xNew + (speed);
				invincible2(xNew, yNew);
				Robjects[i].setPosition(xNew , yNew);
			}
			else{
			xNew = xPrev - (sizex + 10);
			Robjects[i].setPosition(xNew,yPrev);
			}
		}
  }
  else if((xNew < xPrev + 1)&&(xNew > xPrev - 1)){
	  if(prevDirection == 3) {
		  	if((invincible1 == true)&&(yPrev > yNew)){
			    yNew = yNew - (speed);
				invincible2(xNew, yNew);
				Robjects[i].setPosition(xNew , yNew);
			}
			else{
		  yNew = yPrev + sizey + 10;
		  Robjects[i].setPosition(xPrev,yNew);
			}
	  }
	  else if(prevDirection == 4){
		  	if((invincible1 == true)&&(yPrev < yNew)){
			    yNew = yNew + (speed);
				invincible2(xNew, yNew);
				Robjects[i].setPosition(xNew , yNew);
			}
			else{
		  yNew = yPrev - (sizey + 10);
		  Robjects[i].setPosition(xPrev,yNew);
			}
	  }
  }
  //--------------------------------------------------------------------
  else{
  if((direction == 1)||(direction == 2)){
	  if(yNew < yPrev){
		  yNew = yNew + speed;
		  direction = 4;
	  }
	  else{
		  yNew = yNew - speed;
		  direction = 3;
	  }
  }
  else if((direction == 3)||(direction == 4)){
	  if(xNew > xPrev){
		  xNew = xNew - speed;
		  direction = 1;
	  }
	  else{
		  xNew = xNew + speed;
		  direction = 2;
	  }
  }
  Robjects[i].setPosition(xNew,yNew);
  }
  //--------------------------------------------------------------
  xPrev = xNew;
  yPrev = yNew;
  prevDirection = direction;

  if((i >= 1)&&(invincible1 != true)){
	  checkGameOver = checkBlock(firstx, firsty, xPrev, yPrev);
	  if(checkGameOver == true)
	  return direction;
  }
}
	if(add == true){
		AddTail(direction, xPrev, yPrev);
	}

	return direction;
}
bool checkOutOfBounds(int& xCoor, int& yCoor)
{
	if(xCoor < 0)
	    return true;
	else if(xCoor + sizex > 600)
		return true;
	else if(yCoor < 0)
		return true;
	else if(yCoor + sizey > 500)
		return true;

	return false;
}
bool checkBlock(int xS, int yS, int xB, int yB)
{

	if(((xS >= xB) && (yS >= yB) && (xS <= xB + sizex + 5) && (yS <= yB + sizey + 5)) ||
		((xS <= xB + sizex + 5) && (yS + sizey + 3 >= yB) && (xS >= xB) && (yS <= yB)) ||
		((xS <= xB) && (yS <= yB) && (xS + sizex + 3 >= xB) && (yS + sizey + 3 >= yB)) ||
		((xS + sizex + 3 >= xB) && (yS >= yB) && (xS <= xB) && (yS <= yB + sizey + 5)))
	{
		return true;
	}
	else
		return false;
}
void BlockSpawn(int& xCoor, int& yCoor)
{
	int xOriginal, yOriginal;
	xOriginal = xCoor;
	yOriginal = yCoor;
	srand(time(NULL));

	for(int i = 0; i < 1500; i++)
	xCoor = sizex + rand() % 550;

	if(xCoor > 550)
		xCoor = xCoor - sizex;

	for(int i = 0; i < 1500; i++)
	yCoor = 50 + rand() % 450;

	if(yCoor > 450)
		yCoor = yCoor - sizey;
}
void keepMoving(int direction, int& xCoor, int& yCoor)
{
	if(direction == 1)
		xCoor = xCoor - speed;
	if(direction == 2)
		xCoor = speed + xCoor;
	if(direction == 3)
	    yCoor = yCoor - speed;
	if(direction == 4)
		yCoor = speed + yCoor;
}
int move(int direction, int& xCoor, int& yCoor)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(direction == 2){}
		else{
		xCoor = xCoor - speed;
		return 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(direction == 1){}
		else{
		xCoor = speed + xCoor;
		return 2;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		if(direction == 4){}
		else{
		yCoor = yCoor - speed;
		return 3;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(direction == 3){}
		else{
		yCoor = speed + yCoor;
		return 4;
		}
	}
}
void setAll(int& x,int& y,int& xBlock,int& yBlock)
{
	x = 375; 
	y = 250;
	
	if(!font.loadFromFile("ethnocentric rg.ttf"))
	{
		//error...
	};

	text = convertInt(score1);
	score.setString(text);
	score.setFont(font);
	score.setCharacterSize(24);
	score.setColor(sf::Color(60,60,255));
	
	square.setPosition(x,y);
	xBlock = 100;
	yBlock = 100;
}
bool updateGame(int& x, int& y, int& xBlock, int& yBlock, int& direction, int& directionOfBack,
	            bool checkGameOver, float timer, int& red, int& green, int& blue)
{
	bool bump = false;
	int timing, xNew, yNew, size;

	keepMoving(direction, x, y);
	square.setPosition(x,y);
	elapsedInvincible = clockInvincible.getElapsedTime();

	if(invincible1 == true){

	if((invincible1 == true)&&(timeInv - elapsedInvincible.asSeconds() <= 0)){
		invincible1 = false;
		for(int i = 0; i < Robjects.size(); i++){
    Robjects[i].setFillColor(sf::Color(61, 245, 0));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(42, 160, 0));
		}
	}

	else if((invincible1 == true)&&(timeInv - elapsedInvincible.asSeconds() < 5)){
		timing = (timeInv - elapsedInvincible.asSeconds());
		if(timing > 1){
	 setColor(counter, 1);
		}
		else if (timing > 2){
	 setColor(counter, 2);
		}
		else if(timing > 3){
     setColor(counter, 3);
		}
		else if(timing > 4){
     setColor(counter, 4);
		}
		counter++;
	}

	else if(invincible1 == true){
		for(int i = 0; i < Robjects.size(); i++){
	Robjects[i].setFillColor(sf::Color(200, 50, 50));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(40, 40, 40));
		}
	}

	}
	else{
		for(int i = 0; i < Robjects.size(); i++){
    Robjects[i].setFillColor(sf::Color(61, 245, 0));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(42, 160, 0));
		}
	}

	if(eggs == true){
	if(timeInv - elapsedInvincible.asSeconds() <= 0){
		size = egger.size();
		eggs = false;
		egger.erase(egger.begin()+0, egger.begin()+size);
		window.clear();
	}
	else{
	for(int i = 0; i < 120; i++){
	sf::Vector2f position = egger[i].getPosition();	
	xNew = position.x;
	yNew = position.y;
	bump = checkBlock(x, y, xNew, yNew);
	if(bump == true){
	    score1 = score1 + 10;
	    text = convertInt(score1);
	    score.setString(text);
		egger[i].setPosition(-50, -50);
		bump = false;
		break;
	}
	}
	}
}

else{
	bump = checkBlock(x, y, xBlock, yBlock);
	if ((bump == true)&&(timer > 200)){
		if(invincible == true){
			invincible1 = true;
			invincible = false;
			elapsedInvincible = clockInvincible.getElapsedTime();
			timeInv = 15 + elapsedInvincible.asSeconds();
		}

		if((eggs1 == true)){
			sf::RectangleShape square1(sf::Vector2f(sizex, sizey));
			    square1.setFillColor(sf::Color(175, 175, 175));
	            square1.setOutlineThickness(2);
                square1.setOutlineColor(sf::Color(30, 80, 30));

					for(int j = 0; j < 10; j++){
				for(int i = 0; i < 12; i++){
					square1.setPosition((i*50) + 10, (j*50) + 10);
					egger.push_back(square1);
				}
					}
		
					eggs = true;
					eggs1 = false;
			elapsedInvincible = clockInvincible.getElapsedTime();
			timeInv = 3 + elapsedInvincible.asSeconds();
		}

		BlockSpawn(xBlock, yBlock);
		if(eggs == true){
		}
		else
		egg.setPosition(xBlock,yBlock);
		directionOfBack = CreateTail(x, y, direction, checkGameOver, true);

		if(killTail == true){
			size = Robjects.size();
			if(size > 5)
			Robjects.erase(Robjects.begin()+size -5, Robjects.begin()+size);
			else if(size == 4)
			Robjects.erase(Robjects.begin()+size -4, Robjects.begin()+size);
			else if(size == 3)
            Robjects.erase(Robjects.begin()+size -3, Robjects.begin()+size);
			else if(size == 2)
			Robjects.erase(Robjects.begin()+size -2, Robjects.begin()+size);
			else if(size == 1)
            Robjects.erase(Robjects.begin()+size -1, Robjects.begin()+size);
			else
			{}
			killTail = false;
		}

		if(red == 150)
		    score1 = score1 + 10;
		else if(red == 200)
			score1 = score1 + 20;
		else if(red == 40)
			score1 = score1 + 30;
		else if(red == 204)
			score1 = score1 + 40;
		else if(red == 41)
			score1 = score1 + 50;
		else if(red == 205)
			score1 = score1 + 80;

		setEgg(red, green, blue);
		text = convertInt(score1);
	    score.setString(text);

		return true;
         }
	return false;
}
}

void menu()
{
	int x, y;
	bool exit = false, high = false;
		if(!font.loadFromFile("ethnocentric rg.ttf"))
	{
		//error...
	};
		window.clear();
	sf::RectangleShape menuSquare(sf::Vector2f(550, 450));
	menuSquare.setFillColor(sf::Color(75, 75, 75));
	menuSquare.setOutlineThickness(4);
    menuSquare.setOutlineColor(sf::Color(50, 50, 50));
	menuSquare.setPosition(25, 25);

	sf::RectangleShape play(sf::Vector2f(80, 40));
	play.setFillColor(sf::Color(255, 0, 0));
	play.setOutlineThickness(4);
    play.setOutlineColor(sf::Color(255, 50, 0));
	play.setPosition(100, 350);

	playButton.setString("Play");
	playButton.setFont(font);
	playButton.setCharacterSize(20);
	playButton.setColor(sf::Color(30, 30, 30));
	playButton.setPosition(100, 357);

		sf::RectangleShape High(sf::Vector2f(90, 40));
	High.setFillColor(sf::Color(255, 0, 0));
	High.setOutlineThickness(4);
    High.setOutlineColor(sf::Color(255, 50, 0));
	High.setPosition(300, 350);

	HighButton.setString("High\nScores");
	HighButton.setFont(font);
	HighButton.setCharacterSize(15);
	HighButton.setColor(sf::Color(30, 30, 30));
	HighButton.setPosition(300, 350);

	snake.setString("SNAKE 2.0");
	snake.setFont(font);
	snake.setCharacterSize(50);
	snake.setColor(sf::Color(30, 30, 255));
	snake.setPosition(80, 75);

    CreatedBy.setString("Created by\nBrandon Aderholdt\nJanuary 10th, 2014");
	CreatedBy.setFont(font);
	CreatedBy.setCharacterSize(15);
	CreatedBy.setColor(sf::Color(30, 30, 70));
	CreatedBy.setPosition(140, 200);

	window.clear();
	while(true){
		sf::Event event;
		  while(window.pollEvent(event)) {
			  if(event.type == sf::Event::Closed)
				  window.close();

			 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				 sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				 x = localPosition.x;
				 y = localPosition.y;
				 if((x > 100) && (x < 180) && (y < 390) && (y > 350))
				 {
					exit = true;
				 }
				 if((x > 300) && (x < 390) && (y < 390) && (y > 350))
				 {
					 high = true;
				 }
		       }
	         }
		 
		  	  window.draw(menuSquare);
			  window.draw(High);
		      window.draw(HighButton);
			  window.draw(play);
			  window.draw(playButton);
			  window.draw(snake);
			  window.draw(CreatedBy);
		      window.display();

			  if(high == true){
				  highScores();
				  window.clear();
				  high = false;
				  	HighButton.setString("High\nScores");
	HighButton.setFont(font);
	HighButton.setCharacterSize(15);
	HighButton.setColor(sf::Color(30, 30, 30));
	HighButton.setPosition(300, 350);

	snake.setString("SNAKE 2.0");
	snake.setFont(font);
	snake.setCharacterSize(50);
	snake.setColor(sf::Color(30, 30, 255));
	snake.setPosition(80, 75);

	playButton.setString("Play");
	playButton.setFont(font);
	playButton.setCharacterSize(20);
	playButton.setColor(sf::Color(30, 30, 30));
	playButton.setPosition(100, 357);

	CreatedBy.setString("Created by\nBrandon Aderholdt\nJanuary 10th, 2014");
	CreatedBy.setFont(font);
	CreatedBy.setCharacterSize(15);
	CreatedBy.setColor(sf::Color(30, 30, 70));
	CreatedBy.setPosition(140, 200);
			  }

			  if(exit == true){
				  for(int i = 4; i <= 0; i--){
				  play.setOutlineThickness(i);
				  sf::sleep(sf::seconds(1));
			      window.draw(play);
		          window.display();
				  }
			  break;
			  }
	}
}
bool exit()
{
	int x, y, size;
	bool exit1 = false;

	if(addHighScores() == true)
		return true;

	if(!font.loadFromFile("ethnocentric rg.ttf"))
	{
		//error...
	};
	gameOver.setString("Game Over");
	gameOver.setFont(font);
	gameOver.setCharacterSize(50);
	gameOver.setColor(sf::Color(200, 200, 0));
	gameOver.setPosition(85, 200);

	sf::RectangleShape exit2(sf::Vector2f(80, 40));
	exit2.setFillColor(sf::Color(255, 0, 0));
	exit2.setOutlineThickness(4);
    exit2.setOutlineColor(sf::Color(255, 100, 0));
	exit2.setPosition(250, 350);

	sf::RectangleShape menu(sf::Vector2f(80, 40));
	menu.setFillColor(sf::Color(255, 0, 0));
	menu.setOutlineThickness(4);
    menu.setOutlineColor(sf::Color(255, 100, 0));
	menu.setPosition(100, 350);

	exitButton.setString("Exit");
	exitButton.setFont(font);
	exitButton.setCharacterSize(20);
	exitButton.setColor(sf::Color(30, 30, 30));
	exitButton.setPosition(260, 357);

	menuButton.setString("Menu");
	menuButton.setFont(font);
	menuButton.setCharacterSize(20);
	menuButton.setColor(sf::Color(30, 30, 30));
	menuButton.setPosition(100, 357);
	        window.draw(gameOver);
			  window.draw(exit2);
			  window.draw(menu);
			  window.draw(gameOver);
			  window.draw(exitButton);
			  window.draw(menuButton);
		      window.display();
	while(true){
		  while(window.pollEvent(event)) {
			  if(event.type == sf::Event::Closed)
				  window.close();

			 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				 sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				 x = localPosition.x;
				 y = localPosition.y;
				 if((x > 100) && (x < 180) && (y < 390) && (y > 350)){
					exit1 = true;
				 }
				 else if((x > 250) && (x < 330) && (y < 390) && (y > 350)){
			size = Robjects.size();
			Robjects.erase(Robjects.begin()+0, Robjects.begin()+size);
				 window.close();
				 }
		       }
	         }

			  if(exit1 == true)
				  break;

			  size = Robjects.size();
			Robjects.erase(Robjects.begin()+0, Robjects.begin()+size);
	}
	window.clear();
	return true;
}
void highScores()
{
	bool exit1 = false;
	std::string filename, name1, score1;
	std::vector<sf::Text> HighNames;
	std::vector<sf::Text> HighScores;
	int x = 75, y = 100, x2 = 300, y2 = 100, size;
	filename = "Highscores.txt";
    std::ifstream inFile(filename);

	if(!font.loadFromFile("ethnocentric rg.ttf"))
	{
		//error...
	};

	int count = 0;
	inFile>>name1>>score1;

	while(count != 5){
	HighName.setString(convertInt(count + 1) + ".  " + name1);
	HighName.setFont(font);
	HighName.setCharacterSize(20); 
	HighName.setColor(sf::Color(50, 50, 50));
	HighName.setPosition(x, y + (50 * count));

	HighScore.setString(score1);
	HighScore.setFont(font);
	HighScore.setCharacterSize(20);
	HighScore.setColor(sf::Color(50, 50, 50));
	HighScore.setPosition(x2, y2 + (50 * count));

	HighScoreTitle.setString("High Scores");
	HighScoreTitle.setFont(font);
	HighScoreTitle.setCharacterSize(50);
	HighScoreTitle.setColor(sf::Color(130, 30, 30));
	HighScoreTitle.setPosition(50, 20);

	menuButton.setString("Menu");
	menuButton.setFont(font);
	menuButton.setCharacterSize(20);
	menuButton.setColor(sf::Color(100, 100, 100));
	menuButton.setPosition(100, 357);

	sf::RectangleShape menu(sf::Vector2f(80, 40));
	menu.setFillColor(sf::Color(255, 0, 0));
	menu.setOutlineThickness(4);
    menu.setOutlineColor(sf::Color(255, 100, 0));
	menu.setPosition(100, 350);

		HighNames.push_back(HighName);
		HighScores.push_back(HighScore);
		count++;
		name1 = "";
		score1 = "";
		inFile>>name1>>score1;
	}
	
	size = HighNames.size();

window.clear();
window.draw(HighScoreTitle);
window.draw(HighNames[0]);
window.draw(HighScores[0]);
window.draw(HighNames[1]);
window.draw(HighScores[1]);
window.draw(HighNames[2]);
window.draw(HighScores[2]);
window.draw(HighNames[3]);
window.draw(HighScores[3]);
window.draw(HighNames[4]);
window.draw(HighScores[4]);
window.draw(menuButton);
window.display();
while(true){
		  while(window.pollEvent(event)) {
			  			  if(event.type == sf::Event::Closed){
			size = Robjects.size();
			Robjects.erase(Robjects.begin()+0, Robjects.begin()+size);
				  window.close();

			  }
			 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				 sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				 x = localPosition.x;
				 y = localPosition.y;
				 if((x > 100) && (x < 180) && (y < 390) && (y > 350))
					exit1 = true;
			 }
		  }
			 if(exit1 == true)
				 break;
	}
inFile.close();
window.clear();
}
bool addHighScores()
{
	std::ofstream outFile;
	std::ifstream inFile;
	std::string filename, name, finalName;
	std::vector<std::string> names;
	std::vector<int> scores;
	int score, count = 0, scored;
	bool enterIt = false, breaker = false;
	scored = score1;
	if(!font.loadFromFile("ethnocentric rg.ttf"))
	{
		//error...
	};

	filename = "Highscores.txt";

	inFile.open(filename);

	enterName.setString("Enter Name: ");
	enterName.setFont(font);
	enterName.setCharacterSize(20);
	enterName.setColor(sf::Color(100, 100, 100));
	enterName.setPosition(20, 357);

	nameEnter.setString(name);
	nameEnter.setFont(font);
	nameEnter.setCharacterSize(20);
	nameEnter.setColor(sf::Color(100, 100, 100));
	nameEnter.setPosition(225, 357);

	inFile>>name>>score;
	while(inFile){
      names.push_back(name);
      scores.push_back(score);
      inFile>>name>>score;
	}
//------------------------------------------------------------
if(scores.size() == 5){
for(int i = 0; i < scores.size(); i++) {
	if(scores[i] < scored)
		enterIt = true;
}
}
//------------------------------------------------------------
else {
	for(int i = 0; i < scores.size(); i++) {
	if(scores[i] < scored){
		enterIt = true;
		break;
	}
}
	if(enterIt != true) 
		enterIt = true;
}
//--------------------------------------------------------------
int i = 0;
name = "";

window.clear();
sf::Event event;

if(enterIt == true) {
	while(true){

		if(enterIt = true)
			window.clear();
		enterIt = false;
	nameEnter.setString(name);
	window.draw(enterName);
	window.draw(nameEnter);
	window.display();

	  while(window.pollEvent(event)) {
		   switch(event.type){
		   case sf::Event::TextEntered:

			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				   breaker = true;
				   break;
			   }
			   else if((event.text.unicode != 8)&&(i < 9)){
				   name += (char)event.text.unicode;
				   i++;
				   finalName = name;
			   }

			   else if (event.text.unicode == '\b'){
                       name = name.substr(0, name.length() - 1);
					   window.clear();
					   enterIt = true;
					   if(!i == 0)
					   i--;
                }
    }
	
	  }
	  if(breaker == true)
			   break;
	}

if(names.size() == 0){
	names.push_back(finalName);
	scores.push_back(scored);
}
else if(names.size() < 5){
	for(int i = 0; i < names.size(); i++){
		if(scores[i] < scored){
			names.insert(names.begin() + i, finalName);
			scores.insert(scores.begin() + i, scored);
			enterIt = true;
			break;
		}
	}
	if(!enterIt == true){
	names.push_back(finalName);
	scores.push_back(scored);
	}
}
else {
		for(int i = 0; i < names.size(); i++){
		if(scores[i] < scored){
			names.insert(names.begin() + i, finalName);
			scores.insert(scores.begin() + i, scored);
			names.pop_back();
			scores.pop_back();
			break;
		}
		}
}

    inFile.close();
    std::ofstream outFile(filename);
	for(int i = 0; i < names.size(); i++)
		outFile<<names[i]<<" "<<scores[i]<<std::endl;
	outFile.close();
	return true;
}
return false;
outFile.close();
}
void main()
	{
	menu();
	while(true){
	sf::Clock clock, clockInvincible;
    score1 = 0;
	int  xBlock, yBlock, x, y, seconds = 0, red, green, blue;
	int direction = 0, directionOfBack = 0, size;
	bool checkGameOver = false, outOfBounds = false, restarter = false, breaker = false;
			size = Robjects.size();
			Robjects.erase(Robjects.begin()+0, Robjects.begin()+size);
			window.clear();
	//---------------------------------------------------------------------------
	//sf::RenderWindow window(sf::VideoMode(600, 500), "Testing");
	//---------------------------------------------------------------------------
	event.type = sf::Event::Count;
	sf::RectangleShape square(sf::Vector2f(sizex, sizey));
	square.setFillColor(sf::Color(200, 60, 0));
	square.setOutlineThickness(2);
    square.setOutlineColor(sf::Color(140, 30, 0));
	//---------------------------------------------------------------------------
	sf::RectangleShape egg(sf::Vector2f(sizex + 2, sizey + 2));
	egg.setFillColor(sf::Color(red, green, blue));
	egg.setOutlineThickness(2);
    egg.setOutlineColor(sf::Color(200, 200, 200));
	//---------------------------------------------------------------------------
	setAll(x, y, xBlock, yBlock);
	//---------------------------------------------------------------------------
  	egg.setPosition(xBlock, yBlock);
	//---------------------------------------------------------------------------
	setEgg(red, green, blue);
 while(window.isOpen())
	  {
		  if(invincible1 == true){
			  invincible2(x, y);
		for(int i = 0; i < Robjects.size(); i++){
	Robjects[i].setFillColor(sf::Color(200, 50, 50));
	Robjects[i].setOutlineThickness(2);
    Robjects[i].setOutlineColor(sf::Color(40, 40, 40));
		}
		  }
		  else 
              outOfBounds = checkOutOfBounds(x , y);

	sf::Time elapsed1 = clock.getElapsedTime();
	seconds = elapsed1.asMilliseconds();
	//---------------------------------------------------------------------------
    restarter = updateGame(x, y, xBlock, yBlock, direction, directionOfBack, checkGameOver, seconds, red, green, blue);

	egg.setFillColor(sf::Color(red, green, blue));
	if(restarter == true)
	clock.restart();
	directionOfBack = CreateTail(x, y, direction, checkGameOver, false);
   	//---------------------------------------------------------------------------
	if((x % 25 == 0)&&(y % 25 == 0)){
		//------------------------------------------------------------
		  while(window.pollEvent(event)) {
			  if(event.type == sf::Event::Closed){
			size = Robjects.size();
			Robjects.erase(Robjects.begin()+0, Robjects.begin()+size);
				  window.close();

			  }
			  //---------------------------------------------------------------------
			  if((event.key.code == sf::Keyboard::P)&&(event.type == sf::Event::KeyPressed)){
			  window.draw(square);
			  for(int i = 0; i < Robjects.size(); i++)
			  window.draw(Robjects[i]);

			  if(eggs == true){}
			  else
			  window.draw(egg);

			  window.draw(score);
		      window.display();
				  while(true){
			  while(window.pollEvent(event)) {
			  if((event.key.code == sf::Keyboard::P)&&(event.type == sf::Event::KeyPressed))
				  breaker = true;
			  			  }
			  if(breaker == true)
				  break;
			  }
			  }
				  breaker = false;
				  event.key.code == sf::Keyboard::Q;
			  if(event.type == sf::Event::KeyPressed){
			  direction = move(direction, x, y);
			  square.setPosition(x,y);
			  }
		    }
		  }
	//---------------------------------------------------------------------------
		if((checkGameOver == true)||(outOfBounds == true))
		{
			  window.clear();
		      window.draw(square);
			  for(int i = 0; i < Robjects.size(); i++)
			  window.draw(Robjects[i]);
			  window.draw(egg);
			  window.draw(score);
			  window.draw(gameOver);
              exit();
			  window.clear();
			  menu();
			  break;
		 }
	//---------------------------------------------------------------------------
		  square.setPosition(x,y);
		  egg.setPosition(xBlock, yBlock);

		  	  window.clear();
		      window.draw(square);
			  for(int i = 0; i < Robjects.size(); i++)
			  window.draw(Robjects[i]);

			  if(eggs == false){
				    window.draw(egg);
			  }
			  else{
		for(int i = 0; i < 120; i++)
		window.draw(egger[i]); 
			  }
			  			if(invincible == true)
	{
			invincible3.setString("I");
	        invincible3.setFont(font);
	        invincible3.setCharacterSize(10);
	        invincible3.setColor(sf::Color(255, 255, 255));
	        invincible3.setPosition(xBlock + 4, yBlock + 4);
			window.draw(invincible3);
	}
			  window.draw(score);
		      window.display();
			  if(eggs == true)
				  sf::sleep(sf::seconds(.0009));
			  else
			 sf::sleep(sf::seconds(.003));
	  }
}
    //return 0;
}