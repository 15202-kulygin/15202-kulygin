#include "get_feild.h"

Feild_Loader::Feild_Loader()
{
	input_file.open(file_name);
	height = read_height();
	width = read_width();
	cells = read_cells();
}

int Feild_Loader::read_height()
{
	int result = 0;
	std::string input_string;
	input_file >> input_string;
	if (input_string == "HEIGHT=")
	{
		std::cout << "Height is found, reading" << std::endl;
		input_file >> result;
		std::cout << result << std::endl;
		return result;
	}
	return 0;
}

int Feild_Loader::read_width()
{
	int result = 0;
	std::string input_string;
	input_file >> input_string;
	if (input_string == "WIDTH=")
	{
		std::cout << "Width is found , reading" << std::endl;
		input_file >> result;
		std::cout << result << std::endl;
		return result;
	}
	std::cout << "Not found, bitch" << input_string <<std::endl;
	return 0;
}

std::vector<int> Feild_Loader::read_cells()
{
	std::vector<int> result;
	int buffer = 0;
	int i = 0;
	std::string input_string;
	input_file >> input_string;
	if (input_string != "FEILD:")
	{
		throw -1;
	}
	while (!input_file.eof())
	{
		input_file >> buffer;
		result.push_back(buffer);
		std::cout << buffer << std::endl;
	}

	std::cout << "Successfully read the feild" << std::endl;
	for (int i = 0; i < result.size()-1; i+=2)
	{
		std::cout << result[i] << " " << result[i+1] << std::endl;
	}
	return result;
}


