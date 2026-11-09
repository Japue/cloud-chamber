#include <string>
#include <vector>

struct Pixel {
	unsigned char r, g, b, a;

	Pixel() {
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Pixel(int r_, int g_, int b_, int a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}
};

struct Image {
	int width;
	int height;
	std::vector<Pixel> pixels;

	Image(int width_, int height_, std::vector<Pixel> pixels_) {
		width = width_;
		height = height_;
		pixels = pixels_;
	}
};

Image load_image(const std::string& path);
