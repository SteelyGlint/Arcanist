/* hex_blank -- utility program for libhexmap
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
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "hex_build.hpp"
#include "hexmacros.h"

int main(int argc, char *argv[])
{
  int width, height, x, y;

  switch(argc) {
    case 1:
      width = 25;
      break;
    case 2:
      width = atoi(argv[1]);
      if(width < 0)
        width = 0;
      break;
    default:
      printf("Invalid command line arguments.\n");
      return -1;
  }

	vector<string> xpm_vec_str = BuildXPM(width);

	for( auto &l : xpm_vec_str)
	{
		std::cout << l.c_str() << std::endl;
	}

	return 0;
}

#if 0 
  height = HEX_HEIGHT(width);

  printf("/* XPM */\n");
  printf("static char * xpm_data[] = {\n");
  printf("\"%i %i 2 1\",\n", width, height);
  printf("\" 	c None\",\n");
  printf("\".	c white\",\n");

  for(y = 0; y < height; y++) {
    printf("\"");
    for(x = 0; x < width; x++) {
      if(hex_point_in(width, x, y))
        printf(".");
      else
        printf(" ");
    }
    if(y < height - 1)
      printf("\",\n");
    else
      printf("\"};\n");
  }

  return 0;
}
#endif
