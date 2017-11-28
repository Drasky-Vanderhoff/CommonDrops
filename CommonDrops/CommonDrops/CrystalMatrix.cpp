#include "stdafx.h"
#include "CrystalMatrix.h"

using namespace sf;

CrystalMatrix::CrystalMatrix(Vector2u startPosition, Vector2u matrixDimensions)
	: startPosition(startPosition), matrixDimensions(matrixDimensions), matrix()
{
	std::srand(CrystalColor::_CrystalColorSize);
	for (size_t i = 0; i < matrixDimensions.x; i++)
	{
		matrix.push_back(std::vector<Crystal*>());
		for (size_t j = 0; j < matrixDimensions.y; j++)
		{
			matrix[i].push_back(new Crystal((CrystalColor) (std::rand() % CrystalColor::_CrystalColorSize)));
			matrix[i][j]->move(startPosition.x + i * 32, startPosition.y + j * 32);
		}
	}
}

void CrystalMatrix::drawMatrix(RenderWindow &window)
{
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] != nullptr) window.draw(matrix[i][j]->getNextFrame(.15));
}

void CrystalMatrix::destroyCrystalInCol(int col)
{
	if(matrix[col].size() > 0) matrix[col].pop_back();
}

CrystalMatrix::~CrystalMatrix()
{
}
