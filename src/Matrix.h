#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <vector>

class Matrix
{
public :
	
	Matrix(std::size_t, std::size_t);
	
	void setCoeff(std::size_t, std::size_t, float);
	float getCoeff(std::size_t, std::size_t) const;
	std::size_t row() const;
	std::size_t col() const;
	
	Matrix operator+(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	
	void applySigmo();
	void applySigmoPrime();
	
	void disp() const; // Debug function
	
private :
	
	std::size_t m_row;
	std::size_t m_col;
	std::vector<std::vector<float>> m_mat;
};

#endif //MATRIX_H
