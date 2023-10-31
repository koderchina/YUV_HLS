#include "yuv.h"
void yuv(hls::stream<uint_input> &inStream,
		hls::stream<uint_output> &yStream,
		hls::stream<uint_output> &cbStream,
		hls::stream<uint_output> &crStream)
{
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE axis port=yStream
#pragma HLS INTERFACE axis port=cbStream
#pragma HLS INTERFACE axis port=crStream

	uint_input r, g, b;
	for (int i = 0; i < 128 * 3 * 256; i++) {
#pragma HLS PIPELINE
		uint_output y, cb, cr;
		//int ua, ub, uc;
		if (i != 0 && i % 3 == 0) {
			// konverzija
			//ua = r.data *  .299000 + g.data *  .587000 + b.data *  .114000;
			y.data = (r.data >> 2) + (g.data >> 1) + (b.data >> 3) + 10;
			//y.data = r.data * .25 + g.data * .5 + b.data * .125;
			//std::cout << y.data << " " << ua << std::endl;
			//ub = r.data * -.168736 + g.data * -.331264 + b.data *  .500000 + 128;
			cb.data = -(r.data >> 3) - (g.data >> 2) + (b.data >> 1) + 118;
			//std::cout << cb.data << " " << ub << std::endl;
			//uc = r.data *  .500000 + g.data -.418688 + b.data * -.081312 + 128;
			cr.data = (r.data >> 1) - (g.data >> 1) + 128;
			//std::cout << cr.data << " " << uc << std::endl;
			// cb.data = g.data << 4 + b.data << 2 + 128;
			// cr.data = r.data << 2 - g.data << 4 + 128;
			yStream.write(y);
			cbStream.write(cb);
			crStream.write(cr);
			/*
			out_y[y_i++] = y;
			out_cb[cb_i++] = cb;
			out_cr[cr_i++] = cr;
			*/
		}
		if (i % 3 == 0) {
			// r
			//r = rgb[i];
			r = inStream.read();
		}
		else if (i % 3 == 1) {
			// g
			//g = rgb[i];
			r = inStream.read();
		}
		else if (i % 3 == 2) {
			// b
			//b = rgb[i];
			r = inStream.read();
		}
	}
}
