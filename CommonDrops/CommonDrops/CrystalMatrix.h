#pragma once
#include "Crystal.h"

typedef std::vector<std::vector<Crystal*>> crystalMatrixType;

class CrystalMatrix
{
private:
	const sf::Vector2u startPosition;
	const sf::Vector2u matrixDimensions;
	crystalMatrixType matrix;
public:
	CrystalMatrix(sf::Vector2u startPosition, sf::Vector2u matrixDimensions);
	void CrystalMatrix::destroyCrystalInCol(int col);
	void drawMatrix(sf::RenderWindow &window);
	~CrystalMatrix();
};

