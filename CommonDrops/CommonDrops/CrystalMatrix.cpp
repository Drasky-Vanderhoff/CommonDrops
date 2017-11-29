#include "stdafx.h"
#include "CrystalMatrix.h"

using namespace sf;

CrystalMatrix::CrystalMatrix(Vector2u startPosition, Vector2u matrixDimensions)
	: startPosition(startPosition), matrixDimensions(matrixDimensions), matrix()
{
	for (size_t i = 0; i < matrixDimensions.x; i++) matrix.push_back(std::vector<Crystal*>());
}

void CrystalMatrix::fillMatrixWithRandomCrystals()
{
	std::srand(CrystalColor::_CRYSTAL_COLOR_SIZE);
	for (size_t i = 0; i < matrixDimensions.x; i++)
	{
		for (size_t j = 0; j < matrixDimensions.y; j++)
		{
			matrix[i].push_back(new Crystal((CrystalColor)(std::rand() % CrystalColor::_CRYSTAL_COLOR_SIZE)));
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

void CrystalMatrix::pushCrystalInCol(int col, Crystal *crystal)
{
	if (matrix[col].size() < matrixDimensions.y) {
		matrix[col].push_back(crystal);
		matrix[col][matrix[col].size() - 1]->move(startPosition.x + col * 32, startPosition.y + (matrix[col].size() - 1) * 32);
	};
}

Crystal* CrystalMatrix::popCrystalInCol(int col)
{
	Crystal* result = nullptr;
	if (matrix[col].size() > 0) {
		result = matrix[col].back();
		matrix[col].pop_back();
	}

	return result;
}

void CrystalMatrix::trasferCrystalFromMatrix(const int destCol, CrystalMatrix *source, const unsigned int srcCol)
{
	if (matrix[destCol].size() < matrixDimensions.y) this->pushCrystalInCol(destCol, source->popCrystalInCol(srcCol));
}

CrystalMatrix::~CrystalMatrix()
{
}
