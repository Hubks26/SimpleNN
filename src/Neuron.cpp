#include "Neuron.h"

Neuron::Neuron(float value, float biais)
: m_value(value)
, m_biais(biais)
{
}

float Neuron::getValue() const
{
	return(m_value);
}
