#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	std::vector<Layer> layers;
	
	layers.push_back(Layer(4));
	layers.push_back(Layer(2));
	layers.push_back(Layer(2));
	layers.push_back(Layer(2));
	layers.push_back(Layer(1));
	
	m_layers = layers;
}

NeuralNetwork::NeuralNetwork(std::vector<Layer> layers)
: m_layers(layers)
{
}

void NeuralNetwork::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::size_t size = m_layers.size();
	std::vector<Layer> layers = m_layers;
	float width_screen = target.getSize().x;
	float height_screen = target.getSize().y;
	
	for (std::size_t i = 0; i < size-1; ++i)
	{
		for (std::size_t j = 0; j < layers[i].size(); ++j)
		{
			for (std::size_t k = 0; k < layers[i+1].size(); ++k)
			{
				sf::VertexArray lines(sf::Lines, 2);
				
				lines[0].position.x = (i+1)*width_screen/(size+1);
				lines[0].position.y = (j+1)*height_screen/(layers[i].size()+1);
				lines[1].position.x = (i+2)*width_screen/(size+1);
				lines[1].position.y = (k+1)*height_screen/(layers[i+1].size()+1);
				
				lines[0].color = sf::Color::Blue;
				lines[1].color = sf::Color::Red;
				
				target.draw(lines, states);
			}
		}
	}
	
	for (std::size_t i = 0; i < size; ++i)
	{
		layers[i].setPosition((i+1)*width_screen/(size+1));
		
		target.draw(layers[i], states);
	}
}
