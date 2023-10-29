#include "yuv.h"
void yuv(hls::stream<uint_input> &inStream,
		hls::stream<uint_output> &outStream)
{
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE axis port=outStream

	uint_input r, g, b;
	for (int i = 0; i < 128 * 3 * 256; i++) {
#pragma HLS PIPELINE
		uint_output y, cb, cr;
		if (i != 0 && i % 3 == 0) {
			// konverzija
			cout << "R = " << r.data << " G = " << g.data << " B = " << b.data;
			y.data = r.data *  .299000 + g.data *  .587000 + b.data *  .114000;
			cb.data = r.data * -.168736 + g.data * -.331264 + b.data *  .500000 + 128;
			cr.data = r.data *  .500000 + g.data -.418688 + b.data * -.081312 + 128;
			//cout << " Y = " << y.data << " Cb = " << cb.data << " Cr = " << cr.data << endl;
			outStream.write(y);
			outStream.write(cb);
			outStream.write(cr);
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
			g = inStream.read();
		}
		else if (i % 3 == 2) {
			// b
			//b = rgb[i];
			b = inStream.read();
		}
	}
}
