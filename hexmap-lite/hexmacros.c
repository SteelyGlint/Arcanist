/* hexmap -- a library for display of hexagonal grids
 * Copyright (C) 2002 R. Steinke
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

#include "hexmacros.h"

/**
 * hex_point_in:
 * @width: The width of a hex in pixels. The height of the hex
 *         is given by HEX_HEIGHT().
 * @x: The x coordinate of a point which might lie in the hex
 * @y: The y coordinate of a point which might lie in the hex
 *
 * check if a point is inside a hex
 *
 * Return value: %true if the point is inside, %false otherwise
 **/
bool
hex_point_in	(uint_fast32_t		 width,
		 int_fast32_t		 x,
		 int_fast32_t		 y)
{
  uint_fast32_t half_height, quarter_width;

  if(x < 0 || x >= width)
    return false;

  half_height = HEX_HALF_HEIGHT(width);

  if(y < 0 || y >= 2 * half_height)
    return false;

  if(y > half_height) /* Mirror about vertical center */
    y = 2 * half_height - y;
  else if(y == half_height)
    return true;

  quarter_width = HEX_QUARTER_WIDTH(width);

  if(x >= width - quarter_width) /* Mirror about horizontal center */
    x = width - x;
  else if(x >= quarter_width)
    return true;

  return (half_height - y) * quarter_width < x * half_height;
}

/**
 * hex_set_points:
 * @points: An array of #HexPoint of size 6
 * @width: The width of the hex
 *
 * Sets @points to the coordinates of the corners of the hex,
 * starting at the upper left and going clockwise.
 *
 * Return value: The height of the hex. If this is zero, @points was not set.
 **/
uint_fast32_t
hex_set_points	(HexPoint *points,
		 uint_fast32_t     width)
{
  uint_fast32_t height = HEX_HEIGHT(width);

  if((width == 0) || (height == 0))
    return 0;

  points[0].x = HEX_TOP_LEFT_X_OFFSET(width);
  points[0].y = HEX_TOP_LEFT_Y_OFFSET(height);
  points[1].x = HEX_TOP_RIGHT_X_OFFSET(width);
  points[1].y = HEX_TOP_RIGHT_Y_OFFSET(height);
  points[2].x = HEX_MIDDLE_RIGHT_X_OFFSET(width);
  points[2].y = HEX_MIDDLE_RIGHT_Y_OFFSET(height);
  points[3].x = HEX_BOTTOM_RIGHT_X_OFFSET(width);
  points[3].y = HEX_BOTTOM_RIGHT_Y_OFFSET(height);
  points[4].x = HEX_BOTTOM_LEFT_X_OFFSET(width);
  points[4].y = HEX_BOTTOM_LEFT_Y_OFFSET(height);
  points[5].x = HEX_MIDDLE_LEFT_X_OFFSET(width);
  points[5].y = HEX_MIDDLE_LEFT_Y_OFFSET(height);

  return height;
}

/**
 * hex_get_hex_from_coords
 * @hex_width: The width of a hex in pixels. The height of the hex
 *         is given by HEX_HEIGHT().
 * @x: The distance in pixels from the left side of the grid.
 * @y: The distance in pixels from the top of the grid.
 * @x_hex: A location to return the x coordinate of the hex.
 * @y_hex: A location to return the y coordinate of the hex.
 *
 * Find the coordinates of the hex that a pixel is located in.
 **/
void
hex_get_hex_from_coords	(uint_fast32_t       hex_width,
			 int_fast32_t        x,
			 int_fast32_t        y,
			 int_fast32_t       *x_hex,
			 int_fast32_t       *y_hex)
{
  int_fast32_t x_offset, y_offset, x_hex_val, y_hex_val;

  x_hex_val = x / HEX_THREE_QUARTER_WIDTH(hex_width);
  y_hex_val = (y - HEX_HALF_HEIGHT(hex_width) * (x_hex_val % 2))
    / HEX_HEIGHT(hex_width);

  x_offset = x - x_hex_val * HEX_THREE_QUARTER_WIDTH(hex_width);
  y_offset = y - HEX_HALF_HEIGHT(hex_width) * (x_hex_val % 2)
    - y_hex_val * HEX_HEIGHT(hex_width);

  if(x_offset < HEX_QUARTER_WIDTH(hex_width)) {
    if(y_offset < (HEX_HALF_HEIGHT(hex_width) - x_offset * HEX_SQRT3)) {
      (x_hex_val)--;
      y_hex -= (x_hex_val % 2);
    }
    else if(y_offset > (HEX_HALF_HEIGHT(hex_width) + x_offset * HEX_SQRT3)) {
      (x_hex_val)-- ;
      y_hex_val += 1 - (x_hex_val % 2);
    }
  }

  if(x_hex)
    *x_hex = x_hex_val;
  if(y_hex)
    *y_hex = y_hex_val;
}
