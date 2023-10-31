#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "yuv.h"

using namespace std;

int main(){

	ifstream inputFile("rgb.txt");
	int maxComponents = 128 * 3* 256;
	int rgb[128 * 3 * 256];
	hls::stream<uint_input> rgbStream;
	//float out_y[128 * 256];
	//float out_cr[128 * 256];
	//float out_cb[128 * 256];
	// Read and display lines from the file

	std::string line;
    int i = 0;

	 while (i < maxComponents && getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
             if (i < maxComponents) {
                rgb[i++] = stoi(token);
            } else {
                break;
            }
        }
    }

	inputFile.close();

	for(int i = 0; i < 256 * 3 * 128; i++){
		uint_input valIn;
		valIn.data = rgb[i];
		rgbStream << valIn;
	}

	hls::stream<uint_output> yStream;
	hls::stream<uint_output> cbStream;
	hls::stream<uint_output> crStream;
	yuv(rgbStream, yStream, cbStream, crStream);

	while(!yStream.empty()){
		uint_output valOutY;
		uint_output valOutCb;
		uint_output valOutCr;
		yStream.read(valOutY);
		cbStream.read(valOutCb);
		crStream.read(valOutCr);
		cout << "Y: " << valOutY.data << " Cb: " << valOutCb.data << " Cr: " << valOutCr.data << endl;
	}

	cout << endl << "################################################################################################" << endl;

	return 0;
}
