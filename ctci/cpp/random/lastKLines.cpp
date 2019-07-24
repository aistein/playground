#include <iostream>
#include <fstream>
#include <string>

void lastKLines ( std::string filename, int K )
{
	std::ifstream file;
	std::string line;
	file.open( filename, std::ios::ate );
	if ( file.is_open() ) {

		while ( K > 0 ) {
			file.seekg(-1, std::ios::cur);
			if ( !file.good() ) {
				std::cout << "ERROR: file contains less than K lines.\n";
				exit(-1);
			}
			if ( file.peek() == '\n' ) --K;
		}

		int line_offset = 1;
		while ( getline( file, line ) ) {
			printf("%4d: %s\n", line_offset++, line.c_str());
		}
	}
	else {
		std::cout << "ERROR: failed to open file!" << std::endl;
	}
}

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "usage: ./lastKLines <filename> <K>\n"; 
		exit(-1);
	}
	std::string filename = argv[1];
	int K = std::stoi( argv[2] );

	lastKLines( filename, K );

	return 0;
}
