#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game
{
private:

	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	//Initalization
	void initwindow();
	void initStates();

public:
	Game();

	virtual~Game();

	//Functions

	void updateDt();
	void updateSFMLevents();
	void update();
	void render();
	void run();

};

#endif

