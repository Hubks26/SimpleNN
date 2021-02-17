#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Layer : public sf::Drawable
{
public :
	
	Layer(std::size_t size);
	
	std::size_t size() const;
	
	void setPosition(float x);
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::size_t m_size;
	std::vector<Neuron> m_neurons;
	float m_position;
};

#endif // LAYER_H
