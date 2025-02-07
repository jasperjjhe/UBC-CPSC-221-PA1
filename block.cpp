#include "block.h"
#include <cmath>
#include <iostream>



int Block::Height() const {
	/* your code here */
	return 0;
}

int Block::Width() const {
	/* your code here */
	return 0;
}

void Block::Render(PNG &im, int x) const {
	/* your code here */
	
	
}

void Block::Build(PNG &im, int x, int width) {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < im.height(); j++) {
			RGBAPixel * pixel = im.getPixel(i + x, j);
			data[i][j] = *pixel;
		}
	}
	
}
