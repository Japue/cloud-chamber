#include <vector>
#include <iostream>
#include "image.h"
#include "stb_image.h"


Image load_image(const std::string& path) {
	// try to load image
	int w, h, channels;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);
	if (!data) {
		std::cerr << "Failed to load image: " << stbi_failure_reason() << '\n';
		return Image(0, 0, {});
	}

	//create the pixel vector
	std::vector<Pixel> pixels(w * h);
	for (int i = 0; i < w * h; i++) {
		pixels[i] = Pixel(data[i * 4], data[i * 4 + 1], data[i * 4 + 2], data[i * 4 + 3]);
	}
	stbi_image_free(data);

	//return the image
	return Image(w, h, pixels);
}
