#ifndef NEURON_H
#define NEURON_H

class Neuron
{
public :
	
	Neuron(float value, float biais);
	
	float getValue() const;
	
private :
	
	float m_value;
	float m_biais;
};

#endif // NEURON_H
