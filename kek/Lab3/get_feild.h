#ifndef GET_FEILD_H
#define GET_FEILD_H

#include <iostream>
#include <fstream>
#include <vector>

class Feild_Loader
{
public:
	Feild_Loader();
	int get_height() { return height; };
	int get_width() { return width; };
	std::vector<int> get_cells() { return cells; };
private:
	std::string file_name = "Feild.life";
	std::ifstream input_file;

	int read_height();
	int read_width();
	std::vector<int> read_cells();

	int height;
	int width;
	std::vector<int> cells;
};

#endif