#include <iostream>
#include "image.h"

//define once, use the include for all other files
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char* argv[]) {
	const std::string path = argv[1];
	const int cutoff = std::stoi(argv[2]);
	Image image = load_image(path);
	std::cout << "Image loaded: w = " << image.width << ", h = " << image.height << "\n";

	for (Pixel& pixel : image.pixels) {
		if (pixel.r < cutoff) {
			pixel = Pixel(0, 0, 0, 255);
		}
	}
	const std::string output_path = "output_" + std::to_string(cutoff) + ".png";
	stbi_write_png(output_path.c_str(), image.width, image.height, 4, image.pixels.data(), image.width * 4);
}
