#include "stdafx.h"
#include "CrystalMatrix.h"

using namespace sf;

CrystalMatrix::CrystalMatrix(Vector2u startPosition, Vector2u matrixDimensions)
	: startPosition(startPosition), matrixDimensions(matrixDimensions), matrix()
{
	for (size_t i = 0; i < matrixDimensions.x; i++) matrix.push_back(CrystalVectorType());
}

void CrystalMatrix::fillMatrixWithRandomCrystals()
{
	std::srand(time(NULL));
	for (size_t i = 0; i < matrixDimensions.x; i++) {
		matrix[i].clear();
		for (size_t j = 0; j < std::rand() % matrixDimensions.y; j++)
			matrix[i].push_back(new Crystal((CrystalColor)(std::rand() % CrystalColor::_CRYSTAL_COLOR_SIZE)));
	}
}

bool CrystalMatrix::addRandomCrystalRowToMatrix()
{
	std::srand(time(NULL));
	for (size_t i = 0; i < matrixDimensions.x; i++)
	{
		matrix[i].push_front(new Crystal((CrystalColor)(std::rand() % CrystalColor::_CRYSTAL_COLOR_SIZE)));
		if(matrixDimensions.y <= matrix[i].size()) return true;
	}

	return false;
}

void CrystalMatrix::drawMatrix(RenderWindow &window)
{
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] != nullptr) {
				matrix[i][j]->move(startPosition.x + i * 32, startPosition.y + j * 32);
				window.draw(matrix[i][j]->getNextFrame(.15));
			}
}

void CrystalMatrix::pushCrystalInCol(int col, Crystal *crystal)
{
	if (matrix[col].size() < matrixDimensions.y && crystal != nullptr) matrix[col].push_back(crystal);
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
CrystalColor CrystalMatrix::getBackCrystalColor(int col) const
{
	if (matrix[col].size() > 0) return matrix[col].back()->getColor();
	else return CrystalColor::_CRYSTAL_COLOR_SIZE;
}

CrystalColor CrystalMatrix::getBackCrystalColor(const Vector2u position) const
{
	if (position.x >= 0 && position.x < matrixDimensions.x && position.y >= 0 && matrix[position.x].size() > position.y) 
		return matrix[position.x][position.y]->getColor();
	else return CrystalColor::_CRYSTAL_COLOR_SIZE;
}

bool CrystalMatrix::trasferCrystalFromMatrix(const int destCol, CrystalMatrix *source, const unsigned int srcCol)
{
	bool result = matrix[destCol].size() < matrixDimensions.y;
	if (result) this->pushCrystalInCol(destCol, source->popCrystalInCol(srcCol));
	return !result;
}

unsigned int CrystalMatrix::destroyRepeatedCrystalsFromColumn(const unsigned int col, const CrystalColor color)
{
	return destroyRepeatedCrystalsFromPosition(Vector2u(col, matrix[col].size() - 1), color, 2);
}

unsigned int CrystalMatrix::destroyRepeatedCrystalsFromPosition(const Vector2u position, const CrystalColor color, const unsigned int minDistance)
{
	unsigned int result = 0;

	CrystalVectorType *col = &matrix[position.x];
	Vector2u crystalRange(position.y, position.y);
	while (getBackCrystalColor(Vector2u(position.x, crystalRange.x - 1)) == color) crystalRange.x--;
	while (getBackCrystalColor(Vector2u(position.x, crystalRange.y + 1)) == color) crystalRange.y++;
	if(crystalRange.y - crystalRange.x >= minDistance)
	{
		for (size_t i = crystalRange.x; i < crystalRange.y; i++)
		{
			// TODO: There is a crash error when a crystal is called to be destroyed and it was already destroyed.
			if (getBackCrystalColor(Vector2u(position.x - 1, i)) == color) 
				result += destroyRepeatedCrystalsFromPosition(Vector2u(position.x -1, i), color, 0);
			if (getBackCrystalColor(Vector2u(position.x + 1, i)) == color) 
				result += destroyRepeatedCrystalsFromPosition(Vector2u(position.x + 1, i), color, 0);
		}
		col->erase(col->begin() + crystalRange.x, col->begin() + crystalRange.y + 1);
		result += crystalRange.y - crystalRange.x;
	}

	return result;
}

CrystalMatrix::~CrystalMatrix()
{
}
