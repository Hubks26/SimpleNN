#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include "Matrix.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Layer : public sf::Drawable
{
public :
	
	Layer(std::size_t size);
	
	std::size_t size() const;
	
	Matrix getBiaisMatrix() const;
	Matrix getValueMatrix() const;
	
	void operator-=(const Matrix&);
	
	void setNeuronValue(std::size_t, float);
	void setNeuronBiais(std::size_t, float);
	void setPosition(float x);
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::size_t m_size;
	std::vector<Neuron> m_neurons;
	float m_position;
};

#endif // LAYER_H
