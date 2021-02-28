#include "Layer.h"

Layer::Layer(std::size_t size)
: m_size(size)
, m_neurons(m_size, Neuron(0.f, ((float)rand() / (float)RAND_MAX) * 2 - 1))
, m_position(0.f)
{
}

std::size_t Layer::size() const
{
	return(m_size);
}

Matrix Layer::getBiaisMatrix() const
{
	Matrix res(m_size, 1);
	
	for(std::size_t i = 0; i < m_size; ++i)
	{
		res.setCoeff(i, 0, m_neurons[i].getBiais());
	}
	
	return(res);
}

Matrix Layer::getValueMatrix() const
{
	Matrix res(m_size, 1);
	
	for(std::size_t i = 0; i < m_size; ++i)
	{
		res.setCoeff(i, 0, m_neurons[i].getValue());
	}
	
	return(res);
}

void Layer::operator-=(const Matrix& B)
{
	for(std::size_t i = 0; i < B.row(); ++i)
	{
		m_neurons[i].setBiais(m_neurons[i].getBiais() - B.getCoeff(i, 0));
	}
}

void Layer::setNeuronValue(std::size_t i, float value)
{
	m_neurons[i].setValue(value);
}

void Layer::setNeuronBiais(std::size_t i, float biais)
{
	m_neurons[i].setBiais(biais);
}

void Layer::setPosition(float x)
{
	m_position = x;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(25.f);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1.f);
	sf::FloatRect rect = circle.getLocalBounds();
	circle.setOrigin({rect.width/2.f, rect.height/2.f});
	
	for (std::size_t i = 0; i < m_size; ++i)
	{
		float neuronValue = m_neurons[i].getValue();
		
		circle.setPosition(m_position, (i+1)*target.getSize().y/(m_size+1));
		circle.setFillColor(sf::Color(0, int(neuronValue*255), 0));
		
		target.draw(circle, states);
	}
}
