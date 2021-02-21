#include "Matrix.h"

Matrix::Matrix(std::size_t row, std::size_t col)
: m_row(row)
, m_col(col)
, m_mat(m_row, std::vector<float>(m_col, 0.f))
{
}

void Matrix::setCoeff(std::size_t i, std::size_t j, float newValue)
{
	m_mat[i][j] = newValue;
}

float Matrix::getCoeff(std::size_t i, std::size_t j) const
{
	return(m_mat[i][j]);
}

std::size_t Matrix::row() const
{
	return(m_row);
}

std::size_t Matrix::col() const
{
	return(m_col);
}

Matrix Matrix::operator+(const Matrix& B) const
{
	//Vérification de la possibilité d'addition
	
	std::size_t rowA = this->row();
	std::size_t colA = this->col();
	std::size_t rowB = B.row();
	std::size_t colB = B.col();
	
	if (rowA != rowB || colA != colB)
		throw std::runtime_error ("Matrix::operator+ - wrong dimensions");
	
	std::size_t row = rowA;
	std::size_t col = colA;
	
	//Addition
	
	Matrix mat(row, col);
	
	for(std::size_t i = 0; i < row; ++i)
	{
		for(std::size_t j = 0; j < col; ++j)
		{
			mat.setCoeff(i, j, B.getCoeff(i, j) + this->getCoeff(i, j));
		}
	}
	
	return(mat);
}

Matrix Matrix::operator*(const Matrix& B) const
{
	//Vérification de la possibilité de multiplication
	
	std::size_t rowA = this->row();
	std::size_t colA = this->col();
	std::size_t rowB = B.row();
	std::size_t colB = B.col();
	
	if (colA != rowB)
		throw std::runtime_error ("Matrix::operator* - wrong dimensions");
	
	std::size_t temp = colA;
	std::size_t row = rowA;
	std::size_t col = colB;
	
	//Multiplication
	
	Matrix mat(row, col);
	
	for(std::size_t i = 0; i < row; ++i)
	{
		for(std::size_t j = 0; j < col; ++j)
		{
			float coef = 0.f;
			for(std::size_t k = 0; k < temp; ++k)
			{
				coef += this->getCoeff(i, k) * B.getCoeff(k, j);
			}
			
			mat.setCoeff(i, j, coef);
		}
	}
	
	return(mat);
}

void Matrix::applySigmo()
{
	for(std::size_t i = 0; i < m_row; ++i)
	{
		for(std::size_t j = 0; j < m_col; ++j)
		{
			m_mat[i][j] = 1.f / (1.f + exp(-1.f * m_mat[i][j]));
		}
	}
}

void Matrix::applySigmoPrime()
{
	for(std::size_t i = 0; i < m_row; ++i)
	{
		for(std::size_t j = 0; j < m_col; ++j)
		{
			float sigmo = 1.f / (1.f + exp(-1.f * m_mat[i][j]));
			m_mat[i][j] = sigmo * (1 - sigmo);
		}
	}
}

void Matrix::disp() const //Debug function
{
	for (std::size_t i = 0; i < m_row; ++i)
	{
		for (std::size_t j = 0; j < m_col; ++j)
		{
			std::cout << m_mat[i][j] << " / ";
		}
		std::cout << std::endl;
	}
	
	std::cout << "----------------------------------" <<  std::endl;
}
