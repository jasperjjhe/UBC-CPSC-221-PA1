#include "block.h"
#include <cmath>
#include <iostream>



int Block::Height() const {
	
	if (!data.empty()) {
		return data[0].size();
	}
	
	return 0;
}

int Block::Width() const {
	return data.size();
}

void Block::Render(PNG &im, int x) const {
	
	for (int i = 0; i < Width(); i++) {
		for (int j = 0; j < Height(); j++) {
			RGBAPixel * pixel = im.getPixel(i + x, j);
			*pixel = data[i][j];
		}
	}

}

void Block::Build(PNG &im, int x, int width) {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < im.height(); j++) {
			RGBAPixel * pixel = im.getPixel(i + x, j);
			data[i][j] = *pixel;
		}
	}
	
}
