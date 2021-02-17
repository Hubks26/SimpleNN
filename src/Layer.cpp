#include "Layer.h"

Layer::Layer(std::size_t size)
: m_size(size)
, m_neurons(m_size, Neuron(0.3f, 0.f))
, m_position(0.f)
{
}

std::size_t Layer::size() const
{
	return(m_size);
}

void Layer::setPosition(float x)
{
	m_position = x;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(10.f);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1.f);
	sf::FloatRect rect = circle.getLocalBounds();
	circle.setOrigin({rect.width/2.f, rect.height/2.f});
	
	for (std::size_t i = 0; i < m_size; ++i)
	{
		float neuronValue = m_neurons[i].getValue();
		
		circle.setPosition(m_position, (i+1)*target.getSize().y/(m_size+1));
		circle.setFillColor(sf::Color(int(neuronValue*250), int(neuronValue*250), int(neuronValue*250)));
		
		target.draw(circle, states);
	}
}
