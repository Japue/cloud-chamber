#include <iostream>
#include "image.h"

//define once, use the include for all other files
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char* argv[]) {
	const std::string path = argv[1];
	Image image = load_image(path);
	std::cout << "Image loaded: w = " << image.width << ", h = " << image.height << "\n";
}
