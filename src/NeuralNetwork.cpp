#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	std::vector<Layer*> layers;
	
	// ARCHITECHTURE DU RESEAU
	
	layers.push_back(new Layer(1));
	layers.push_back(new Layer(3));
	layers.push_back(new Layer(4));
 	layers.push_back(new Layer(3));
	layers.push_back(new Layer(1));
	
	// #######################
	
	m_layers = layers;
	
	std::vector<Matrix*> weights;
	
	for(std::size_t k = 0; k < m_layers.size()-1; ++k)
	{
		Matrix* mat = new Matrix(m_layers[k+1]->size(), m_layers[k]->size());
		
		for(std::size_t i = 0; i < mat->row(); ++i)
		{
			for(std::size_t j = 0; j < mat->col(); ++j)
			{
				mat->setCoeff(i, j, ((float)rand() / (float)RAND_MAX) * 2 - 1);
			}
		}
		
		weights.push_back(mat);
	}
	
	m_weights = weights;
	
	Matrix input(1,1);
	Matrix output(1,1);
	
	for(int i = 0; i < 100000; ++i)
	{
		input.setCoeff(0, 0, 1.f);
		output.setCoeff(0, 0, 0.f);
		
		feedForward(input);
		backPropagation(output);
		
		input.setCoeff(0, 0, 0.f);
		output.setCoeff(0, 0, 1.f);
		
		feedForward(input);
		backPropagation(output);
		
		input.setCoeff(0, 0, 0.4);
		output.setCoeff(0, 0, 0.3);
		
		feedForward(input);
		backPropagation(output);
		
		input.setCoeff(0, 0, 0.6);
		output.setCoeff(0, 0, 0.7);
		
		feedForward(input);
		backPropagation(output);
	}
}

NeuralNetwork::NeuralNetwork(std::vector<Layer*> layers)
: m_layers(layers)
{
}

Matrix NeuralNetwork::feedForward(const Matrix& input) const
{
	std::size_t n1 = m_layers[0]->size();
	
	if (input.row() != n1 || input.col() != 1)
		throw std::runtime_error ("NeuralNetwork::feedForward - wrong dimensions for the input");
	
	for(std::size_t i = 0; i < n1; ++i)
	{
		m_layers[0]->setNeuronValue(i, input.getCoeff(i, 0));
	}
	
	Matrix output = (*m_weights[0])*(input) + m_layers[1]->getBiaisMatrix(); // Le premier layer correspond 
																			 //à l'input et n'a donc pas de biais
	output.applySigmo();
	
	for(std::size_t i = 0; i < m_layers[1]->size(); ++i)
	{
		m_layers[1]->setNeuronValue(i, output.getCoeff(i, 0));
	}
	
	for(std::size_t i = 1; i < m_weights.size(); ++i)
	{
		output = (*m_weights[i])*output + m_layers[i+1]->getBiaisMatrix();
		output.applySigmo();
		
		for(std::size_t j = 0; j < m_layers[i+1]->size(); ++j)
		{
			m_layers[i+1]->setNeuronValue(j, output.getCoeff(j, 0));
		}
	}
	
	return(output);
}

void NeuralNetwork::backPropagation(const Matrix& outputExpected)
{	
	std::size_t size_layers = m_layers.size();
	std::size_t size_weights = m_weights.size();
	
	std::size_t size_output = m_layers[size_layers - 1]->size();
	
	if (size_output != outputExpected.row() || outputExpected.col() != 1)
		throw std::runtime_error ("NeuralNetwork::backPropagation - wrong dimensions");
	
	// Calcul des DW, DB et DA
	//Initialisation : 
	
// 	std::vector<Matrix*> DB_vect;
// 	std::vector<Matrix*> DW_vect;
	
	Matrix z = (*m_weights[size_weights - 1])*m_layers[size_layers - 2]->getValueMatrix() + m_layers[size_layers - 1]->getBiaisMatrix();
	z.applySigmoPrime();
	z.constMult(2.f);
	Matrix Z = z.diag();
	Matrix output = m_layers[size_layers - 1]->getValueMatrix();
	Matrix Y = outputExpected;
	Y.constMult(-1.f);
	Matrix DB = Z * (output + Y);
	
	Matrix A = m_layers[size_layers - 2]->getValueMatrix();
	Matrix DW = DB * A.transposee();
	
	Matrix DA = (*m_weights[size_weights - 1]).transposee() * DB;
	
	std::vector<Matrix*> DB_vect(1, new Matrix(DB));
	std::vector<Matrix*> DW_vect(1, new Matrix(DW));
	for (std::size_t i = 2; i < size_weights; ++i)
	{
		z = (*m_weights[size_weights-i])*m_layers[size_layers-i-1]->getValueMatrix()+m_layers[size_layers-i]->getBiaisMatrix();
		z.applySigmoPrime();
		Z = z.diag();
		DB = Z * DA;
		
		A = m_layers[size_layers - i - 1]->getValueMatrix();
		DW = DB * A.transposee();
		
		DA = (*m_weights[size_weights - i]).transposee() * DB;
		
		DB_vect.push_back(new Matrix(DB));
		DW_vect.push_back(new Matrix(DW));
	}
	
	z = (*m_weights[0])*m_layers[0]->getValueMatrix()+m_layers[1]->getBiaisMatrix();
	z.applySigmoPrime();
	Z = z.diag();
	DB = Z * DA;

	A = m_layers[0]->getValueMatrix();
	DW = DB * A.transposee();
	
	DB_vect.push_back(new Matrix(DB));
	DW_vect.push_back(new Matrix(DW));
	
	for (std::size_t i = 0; i < size_weights; ++i)
	{
		(*m_layers[i+1]) -= (*DB_vect[size_weights-i-1]);
		(*m_weights[i]) -= (*DW_vect[size_weights-i-1]);
	}
	
	float cost = 0.f;
	
	for(std::size_t i = 0; i < output.row(); ++i)
	{
		cost += (output.getCoeff(i, 0) - outputExpected.getCoeff(i, 0)) * (output.getCoeff(i, 0) - outputExpected.getCoeff(i, 0));
	}
	
	std::cout << "COST : " << cost << std::endl;
}

// void NeuralNetwork::fit()   ### Le but de cette fonction sera de rendre le feed forward et
// la back propagation privées et de simplifier l'utilisation du réseau de neuron.

void NeuralNetwork::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::size_t size = m_layers.size();
	std::vector<Layer*> layers = m_layers;
	float width_screen = target.getSize().x;
	float height_screen = target.getSize().y;
	
	//Partie temporaire test (affichage à refaire au terme du réseau de neurone
	
	for (std::size_t i = 0; i < size-1; ++i)
	{
		for (std::size_t j = 0; j < layers[i]->size(); ++j)
		{
			for (std::size_t k = 0; k < layers[i+1]->size(); ++k)
			{
				sf::VertexArray lines(sf::Lines, 2);
				
				lines[0].position.x = (i+1)*width_screen/(size+1);
				lines[0].position.y = (j+1)*height_screen/(layers[i]->size()+1);
				lines[1].position.x = (i+2)*width_screen/(size+1);
				lines[1].position.y = (k+1)*height_screen/(layers[i+1]->size()+1);
				
				float colorLevel = m_weights[i]->getCoeff(k, j);
				if(colorLevel > 0.f)
				{
					if(int(40.f * colorLevel) >= 255)
					{
						lines[0].color = sf::Color(255, 0, 0);
						lines[1].color = sf::Color(255, 0, 0);
					}
					else
					{
						lines[0].color = sf::Color(int(40.f * colorLevel), 0, 0);
						lines[1].color = sf::Color(int(40.f * colorLevel), 0, 0);
					}
				}
				if(colorLevel <= 0.f)
				{
					if(int(-40.f * colorLevel) >= 255)
					{
						lines[0].color = sf::Color(0, 0, 255);
						lines[1].color = sf::Color(0, 0, 255);
					}
					else
					{
						lines[0].color = sf::Color(0, 0, int(-40.f * colorLevel));
						lines[1].color = sf::Color(0, 0, int(-40.f * colorLevel));
					}
				}
				
				target.draw(lines, states);
			}
		}
	}
	
	for (std::size_t i = 0; i < size; ++i)
	{
		layers[i]->setPosition((i+1)*width_screen/(size+1));
		
		target.draw((*layers[i]), states);
	}
}
