#ifndef __HexGrid_hpp__
#define __HexGrid_hpp__
#include <cstdint>
#include "HexCell.hpp"

namespace Wand
{

class HexGrid
{
public:
	uint8_t rows() { return m_rows; }
	uint8_t cols() { return m_cols; }

private:
	uint8_t m_rows;
	uint8_t m_cols;
};


} /* namespace Wand */
#endif
