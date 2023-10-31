#include <hls_stream.h>
#include <iostream>
#include <ap_axi_sdata.h>
typedef ap_axiu<8,2,5,6> uint_input;
typedef ap_axiu<32,0,0,0> uint_output;

//void yuv(hls::stream<uint8_input> &inStream, hls::stream<uint_output> &outStream);
void yuv(hls::stream<uint_input> &inStream, hls::stream<uint_output> &yStream, hls::stream<uint_output> &cbStream, hls::stream<uint_output> &crStream);
