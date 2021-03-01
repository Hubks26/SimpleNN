#include "Game.h"

const sf::Time Game::m_timePerFrame = sf::seconds(1.f/3.f);

Game::Game()
: m_window(sf::VideoMode(1200, 600), "Neural Network")
, m_nn()//std::vector<Layer>(5, Layer(25)))
, m_input(1, 1)
, m_output(1, 1)
, m_parite(0)
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

	if(m_parite%6 == 0)
	{
		m_input.setCoeff(0, 0, 0.f);
		std::cout << 0 << " -> " << 0.9 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	if(m_parite%6 == 1)
	{
		m_input.setCoeff(0, 0, 0.2);
		std::cout << 0.2 << " -> " << 0.1 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	if(m_parite%6 == 2)
	{
		m_input.setCoeff(0, 0, 0.4);
		std::cout << 0.4 << " -> " << 0.9 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	if(m_parite%6 == 3)
	{
		m_input.setCoeff(0, 0, 0.6);
		std::cout << 0.6 << " -> " << 0.1 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	if(m_parite%6 == 4)
	{
		m_input.setCoeff(0, 0, 0.8);
		std::cout << 0.8 << " -> " << 0.9 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	if(m_parite%6 == 5)
	{
		m_input.setCoeff(0, 0, 1.f);
		std::cout << 1 << " -> " << 0.1 << "~" << m_nn.feedForward(m_input).getCoeff(0, 0) << std::endl;
	}
	
	++m_parite;
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_nn);
	m_window.display();
}
