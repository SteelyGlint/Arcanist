#ifndef __HexBuild_hpp__
#define __HexBuild_hpp__

#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include "hexmacros.h"

static const std::string xpm_header = "/* XPM */\nstatic char * xpm_data[] = {\n";


std::string xpm_info(int width, int height, int colors = 2, int chars_per_pixel = 1)
{
	return std::string(std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(colors) + " " + std::to_string(chars_per_pixel));
}

static const std::string xpm_colors[] =
{	"	c None",
	".	c white",
};

std::vector<char> bar_line(int total_width, int line_width)
{
	std::vector<char> line_offset((total_width - line_width)/2,'!');
	std::vector<char> line(line_width + line_width%2,'.');

	std::vector<char> ret_line(line_offset.size()*2 + line.size());

	std::copy(line_offset.begin(),line_offset.end(),ret_line.begin());
	std::copy(line.begin(),line.end(),ret_line.begin()+line_offset.size());
	std::copy(line_offset.begin(),line_offset.end(),ret_line.begin()+line_offset.size()+line.size());
	return ret_line;
}


std::vector<std::string> BuildXPM(int radius)
{
	int width = radius*2;
	int height = HEX_HEIGHT(width);
	
	std::vector<std::string> trapazoid;
	for(int i_radius=1; i_radius < radius;++i_radius)
	{
		std::vector<char> line = bar_line(width,i_radius);
		std::string line_str(line.begin(),line.end());
		trapazoid.emplace_back(std::move(line_str));
	}


	int n_erase = trapazoid.size() - height;	

	return trapazoid;
	//return xpm_info(width, height);
}


#if 0
{
  const std::string& tmp = stringstream.str();
  const char* cstr = tmp.c_str();
}
#endif

#endif
