#include "Level.h"
#include <math.h>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);

	startPos.x = 0;
	startPos.y = 0;

	distanceOfDrag = 0;

	//initialise circle object
	circle.setRadius(50);
	circle.setFillColor(sf::Color::Black);
	circle.setOutlineThickness(2.f);
	circle.setOutlineColor(sf::Color::Red);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{



	//Output to console when W key is pressed
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed\n";
	}

	//Output to console when J, K and L pressed together
	if ((input->isKeyDown(sf::Keyboard::J)) & (input->isKeyDown(sf::Keyboard::K)) & (input->isKeyDown(sf::Keyboard::L)))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);

		std::cout << "J, K and L were pressed together\n";

	}

	//Exit game if escape key pressed
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	//Check if mouse wasn't down last frame and is down this frame
	if (input->isMouseLDown() && !MouseLDownLastFrame)
	{
		//get mousex and y and store it as startPos
		startPos.x = input->getMouseX();
		startPos.y = input->getMouseY();
	}

	//Check if mouse was down last frame and is now up this frame and if it is, calculate the distance between the start pos and end pos
	if (!(input->isMouseLDown()) && MouseLDownLastFrame)
	{
		endPos.x = input->getMouseX();
		endPos.y = input->getMouseY();

		distanceOfDrag = sqrt(((endPos.x - startPos.x) * (endPos.x - startPos.x)) + ((endPos.y - startPos.y) * (endPos.y - startPos.y)));
	}

	if (input->isMouseRDown())
	{
		circlePos.x = input->getMouseX();
		circlePos.y = input->getMouseY();
		circle.setPosition(circlePos.x, circlePos.y);
	}

}

// Update game objects
void Level::update()
{
	//Output the position of the mouse as text in window
	std::string mouseXString = std::to_string(input->getMouseX());
	std::string mouseYString = std::to_string(input->getMouseY());
	//text.setString("X Position: " + mouseXString + "   Y Position: " + mouseYString);
	std::string deltaXString = std::to_string(input->getMouseX() - startPos.x);
	std::string deltaYString = std::to_string(input->getMouseY() - startPos.y);
	std::string distanceOfDragString = std::to_string(distanceOfDrag);

	text.setString("X Delta: " + deltaXString + "   Y Delta: " + deltaYString + "   Distance of Drag: " + distanceOfDragString);

	MouseLDownLastFrame = input->isMouseLDown();
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}