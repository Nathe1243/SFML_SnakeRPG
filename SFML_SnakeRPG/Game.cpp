#include "Game.h"


//Initializer Functions

void Game::initwindow()
{
	std::ifstream ifs("Config/window.ini");

	std::string title = " ";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();


	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Works!!");
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

//Contructor/Destructor

Game::Game()
{
	this->initwindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


//Functions

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLevents()
{
		while (this->window->pollEvent(this->sfEvent))
		{
			if (this->sfEvent.type == sf::Event::Closed)
				this->window->close();
		}
}

void Game::update()
{
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		
		if (!this->states.empty())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				delete this->states.top();
				this->states.pop();
			}
		}
	}

	this->updateSFMLevents();
}

void Game::render()
{

	this->window->clear();

	//Render items

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();

}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
