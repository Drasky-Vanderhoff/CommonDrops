#pragma once
#include "Crystal.h"
#include <deque>

typedef std::deque<Crystal*> CrystalVectorType;
typedef std::deque<CrystalVectorType> CrystalMatrixType;

class CrystalMatrix
{
private:
	const sf::Vector2u startPosition;
	const sf::Vector2u matrixDimensions;
	CrystalMatrixType matrix;
	unsigned int destroyRepeatedCrystalsFromPosition(const sf::Vector2u position,
													 const CrystalColor color,
													 const unsigned int minDistance,
													 const unsigned int comboDelta);
public:
	CrystalMatrix(sf::Vector2u startPosition, sf::Vector2u matrixDimensions);
	void fillMatrixWithRandomCrystals();
	bool addRandomCrystalRowToMatrix();
	void pushCrystalInCol(int col, Crystal *crystal);
	Crystal* popCrystalInCol(int col);
	CrystalColor getBackCrystalColor(int col) const;
	CrystalColor CrystalMatrix::getBackCrystalColor(unsigned int x, unsigned int y) const;
	bool trasferCrystalFromMatrix(const int destCol, CrystalMatrix *source, const unsigned int srcCol);
	unsigned int destroyRepeatedCrystalsFromColumn(const unsigned int col, const CrystalColor color);
	void drawMatrix(sf::RenderWindow &window);
	~CrystalMatrix();
};

