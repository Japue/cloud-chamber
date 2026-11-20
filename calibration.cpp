#include "calibration.h"
#include <SFML/Graphics.hpp>
#include "image.h"


void draw_image_sfml(sf::RenderWindow& window, const Image& image) {
	// calculate a scaling to have the image cover most of the initial sfml window
	const float scale = 1;
	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			int vec_index = x + y * image.width;
			Pixel pixel = image.pixels.at(vec_index);

			sf::RectangleShape square(scale, scale);
			square.setPosition({static_cast<float>(x) + scale, static_cast<float>(y) + scale});
			square.setFillColor(sf::Color(pixel.r, pixel.g, pixel.b))
			window.draw(square);
		}
	}
}


//function that sets up the calibration coordinates for using after, this should be called every independent session once
std::vector<sf::Vector2i> calibrate_setup(const Image& image) {
	//window setup
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),  "Calibration");
	sf::View view = window.getDefaultView();

	bool is_dragging = false;
	sf::Vector2i last_mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2i first_anchor = {0, 0};
	sf::Vector2i second_anchor = {image.width - 1, image.height - 1};

	//gameloop
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {

			//event handling
			if (event -> is<sf::Event::Closed>()) {
				window.close();
			}

			if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::Escape) {
					window.close();
				}
			}

			if (const auto* mousePressed = event -> getIf<sf::Event::MouseButtonPressed>()) {
				if (mousePressed->button == sf::Mouse::Button::Left) {
					is_dragging = true;
				}
			}
			
			if (const auto* mouseReleased = event -> getIf<sf::Event::MouseButtonReleased>()) {
				if (mouseReleased->button == sf::Mouse::Button::Left) {
					is_dragging = false;
				}
			}

			if (const auto* scrolled = event -> getIf<sf::Event::MouseWheelScrolled>()) {
				if (scrolled->delta > 0) {
					view.zoom(0.9f);
				} else {
					view.zoom(1.1f);
				}
			}

			if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::S) {
					first_anchor = last_mouse_pos;
				}
			}

			if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::E) {
					second_anchor = last_mouse_pos;
				}
			}
		}

		window.clear();

		//dragging
		sf::Vector2i new_mouse_pos = sf::Mouse::getPosition(window);
		if (is_dragging) {
			sf::Vector2i delta_pos = last_mouse_pos - new_mouse_pos;

			sf::Vector2u window_size_u = window.getSize();
			sf::Vector2f window_size(static_cast<float>(window_size_u.x), static_cast<float>(window_size_u.y));
			sf::Vector2f view_size = view.getSize();

			sf::Vector2f scale_and_float(static_cast<float>(delta_pos.x) * (view_size.x / window_size.x), static_cast<float>(delta_pos.y) * (view_size.y / window_size.y));
			view.setCenter(view.getCenter() + scale_and_float);
		}
		last_mouse_pos = new_mouse_pos;
		window.setView(view);

		//drawing
		draw_image_sfml(window, image);
		//

		window.display();
	}
	return std::vector<sf::Vector2i>(first_anchor, second_anchor);
}


void calibrate(Image& image, std::vector<sf::Vector2i> anchors) {
	vec_index_0 = anchor[0].x + anchor[0].y * image.height;
	vec_index_1 = anchor[1].x + anchor[1].y * image.height;
	image.pixels = (image.pixels.begin() + vec_index_0, image.pixels.begin() + vec_index_1 + 1);

	image.width = anchor[1].x - anchor[0].x;
	image.height = anchor[1].y - anchor[0].y;
}
