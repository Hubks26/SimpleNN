#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"

class NeuralNetwork : public sf::Drawable
{
public :
	
	NeuralNetwork();
	NeuralNetwork(std::vector<Layer>);
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::vector<Layer> m_layers;
};

#endif // NEURALNETWORK_H
