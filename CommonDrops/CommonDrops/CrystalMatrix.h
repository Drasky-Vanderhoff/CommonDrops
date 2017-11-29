#pragma once
#include "Crystal.h"

typedef std::vector<Crystal*> CrystalVectorType;
typedef std::vector<CrystalVectorType> CrystalMatrixType;

class CrystalMatrix
{
private:
	const sf::Vector2u startPosition;
	const sf::Vector2u matrixDimensions;
	CrystalMatrixType matrix;
public:
	CrystalMatrix(sf::Vector2u startPosition, sf::Vector2u matrixDimensions);
	void CrystalMatrix::fillMatrixWithRandomCrystals();
	void CrystalMatrix::pushCrystalInCol(int col, Crystal *crystal);
	Crystal* CrystalMatrix::popCrystalInCol(int col);
	void CrystalMatrix::trasferCrystalFromMatrix(const int destCol, CrystalMatrix *source, const unsigned int srcCol);
	void drawMatrix(sf::RenderWindow &window);
	~CrystalMatrix();
};

