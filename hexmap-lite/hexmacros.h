/* hexmap -- a library for display of hexagonal grids
 * Copyright (C) 2001 R. Steinke
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA  02111-1307  USA.
 */

#ifndef HEX_MACROS_H
#define HEX_MACROS_H
#include <cstdint>


#define HEX_SQRT3				1.73205080757
#define HEX_HALF_HEIGHT(width)			((int_fast32_t) ((width) * (HEX_SQRT3 / 4) + 0.5))
#define HEX_HEIGHT(width)			(HEX_HALF_HEIGHT(width) * 2)
#define HEX_QUARTER_WIDTH(width)		(((width) + 1) / 4)
#define HEX_MIDDLE_HALF_WIDTH(width)		((width) - 2 * HEX_QUARTER_WIDTH(width))
#define HEX_THREE_QUARTER_WIDTH(width)		((width) - HEX_QUARTER_WIDTH(width))

#define HEX_DRAW_X(x, width)			(HEX_THREE_QUARTER_WIDTH(width) * (x))
#define HEX_DRAW_Y(x, y, width, height)		((height) * (y) + ((height) / 2) * \
						(((x) % 2) ? 1 : 0))

#define HEX_TOP_LEFT_X_OFFSET(width)		HEX_QUARTER_WIDTH(width)
#define HEX_BOTTOM_LEFT_X_OFFSET(width)		HEX_TOP_LEFT_X_OFFSET(width)
#define HEX_TOP_RIGHT_X_OFFSET(width)		HEX_THREE_QUARTER_WIDTH(width)
#define HEX_BOTTOM_RIGHT_X_OFFSET(width)	HEX_TOP_RIGHT_X_OFFSET(width)
#define HEX_MIDDLE_LEFT_X_OFFSET(width)		0
#define HEX_MIDDLE_RIGHT_X_OFFSET(width)	(width)
				

#define HEX_TOP_LEFT_Y_OFFSET(height)		0
#define HEX_BOTTOM_LEFT_Y_OFFSET(height)	(height)
#define HEX_MIDDLE_LEFT_Y_OFFSET(height)	((height) / 2)
#define HEX_TOP_RIGHT_Y_OFFSET(height)		HEX_TOP_LEFT_Y_OFFSET(height)
#define HEX_BOTTOM_RIGHT_Y_OFFSET(height)	HEX_BOTTOM_LEFT_Y_OFFSET(height)
#define HEX_MIDDLE_RIGHT_Y_OFFSET(height)	HEX_MIDDLE_LEFT_Y_OFFSET(height)

typedef struct {
  int_fast32_t x, y;
} HexPoint;

bool	hex_point_in		(uint_fast32_t	     width,
					 int_fast32_t	     x,
					 int_fast32_t	     y);

void		hex_get_hex_from_coords	(uint_fast32_t       hex_width,
					 int_fast32_t        x,
					 int_fast32_t        y,
					 int_fast32_t       *x_hex,
					 int_fast32_t       *y_hex);

uint_fast32_t		hex_set_points		(HexPoint   *points,
					 uint_fast32_t       width);


#endif /* HEX_MACROS_H */
