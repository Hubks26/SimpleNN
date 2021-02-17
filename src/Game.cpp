#include "Game.h"

const sf::Time Game::m_timePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: m_window(sf::VideoMode(1000, 500), "Neural Network")
, m_nn()//std::vector<Layer>(5, Layer(25)))
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			update();
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::update()
{
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_nn);
	m_window.display();
}
