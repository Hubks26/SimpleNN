#ifndef GAME_H
#define GAME_H

#include "NeuralNetwork.h"

class Game
{
public :
	
	Game();
	void run();
	
private :
	
	void processEvents();
	void update();
	void render();
	
private :
	
	sf::RenderWindow m_window;
	static const sf::Time m_timePerFrame;
	
	NeuralNetwork m_nn;
	Matrix m_input;
	Matrix m_output;
	bool m_parite;
};

#endif //GAME_H
