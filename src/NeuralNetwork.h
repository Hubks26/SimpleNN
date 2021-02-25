#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"

class NeuralNetwork : public sf::Drawable
{
public :
	
	NeuralNetwork();
	NeuralNetwork(std::vector<Layer*>);
	
	Matrix feedForward(const Matrix&) const;
	void backPropagation(const Matrix&);
	
private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	
	std::vector<Layer*> m_layers;
	std::vector<Matrix*> m_weights;
};

#endif // NEURALNETWORK_H
