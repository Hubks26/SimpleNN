#include "Game.h"

const sf::Time Game::m_timePerFrame = sf::seconds(1.f/2.f);

Game::Game()
: m_window(sf::VideoMode(1000, 500), "Neural Network")
, m_nn()//std::vector<Layer>(5, Layer(25)))
, m_input(4, 1)
, m_output(1, 1)
, m_parite(false)
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
	m_input.setCoeff(0, 0, 0.f);
	m_input.setCoeff(1, 0, 0.f);
	m_input.setCoeff(2, 0, 0.f);
	m_input.setCoeff(3, 0, 0.f);
	if(m_parite)
	{
		m_input.setCoeff(0, 0, 1.f);
		m_input.setCoeff(1, 0, 1.f);
		m_input.setCoeff(2, 0, 1.f);
		m_input.setCoeff(3, 0, 0.f);
		m_output.setCoeff(0, 0, 1.f);
		
		m_nn.feedForward(m_input);
		m_nn.backPropagation(m_output);
	}
	else
	{
		m_input.setCoeff(0, 0, 0.f);
		m_input.setCoeff(1, 0, 0.f);
		m_input.setCoeff(2, 0, 1.f);
		m_input.setCoeff(3, 0, 0.f);
		m_output.setCoeff(0, 0, 0.f);
		
		m_nn.feedForward(m_input);
		m_nn.backPropagation(m_output);
	}
	
	m_parite = not m_parite;
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_nn);
	m_window.display();
}
