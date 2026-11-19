#include <iostream>
#include "image.h"
#include "calibration.h"
#include <SFML/Graphics.hpp>

//define once, use the include for all other files
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char* argv[]) {
	const std::string path = argv[1];
	Image image = load_image(path);
	std::cout << "Image loaded: w = " << image.width << ", h = " << image.height << "\n";

	sf::Vector<sf::Vector2i> anchors = calibrate_setup(image);
	calibrate(image, anchors);
	
	stbi_write_png("new_image", image.width, image.height, 4, image.pixels.data(), image.width * 4);
}
