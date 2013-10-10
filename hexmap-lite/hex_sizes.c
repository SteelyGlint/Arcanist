/* hex_sizes -- utility program for libhexmap
 * Copyright (C) 2001 R. Steinke
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdlib.h>
#include <stdio.h>
#include "hexmacros.h"


int main(int argc, char *argv[])
{
  int_fast32_t width, min_width, max_width;

  switch(argc) {
    case 1:
      min_width = 7;
      max_width = 20;
      break;
    case 2:
      min_width = max_width = atoi(argv[1]);
      break;
    case 3:
      min_width = atoi(argv[1]);
      max_width = atoi(argv[2]);
      break;
    default:
      printf("Invalid command line arguments.\n");
      return -1;
  }

  if(min_width > max_width) {
    width = min_width;
    min_width = max_width;
    max_width = width;
  }

  if(min_width < 0)
    min_width = 0;
  if(max_width < 0)
    max_width = 0;

  for(width = min_width; width <= max_width; width++)
    printf("A hex of width %li has height %li.\n", width, HEX_HEIGHT(width));

  return 0;
}
