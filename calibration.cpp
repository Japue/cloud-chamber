#include "calibration.h"
#include <SFML/Graphics.hpp>
#include "image.h"
//needed for the uints
#include <cstdint>
#include <iostream>


//function that sets up the calibration coordinates for using after, this should be called every independent session once
std::vector<sf::Vector2i> calibrate_setup(const Image& image) {
	//window setup
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),  "Calibration");
	window.requestFocus();
	window.setFramerateLimit(60);
	sf::View view = window.getDefaultView();

	bool is_dragging = false;
	sf::Vector2i last_mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2f last_mouse_pos_scaled = window.mapPixelToCoords(last_mouse_pos);
	sf::Vector2i first_anchor = {0, 0};
	sf::Vector2i second_anchor = {image.width - 1, image.height - 1};

	//load the image into a sprite
	sf::Texture texture(sf::Vector2u{static_cast<unsigned>(image.width), static_cast<unsigned>(image.height)});
	texture.update(reinterpret_cast<const std::uint8_t*>(image.pixels.data()));
	sf::Sprite sprite(texture);

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
					last_mouse_pos_scaled = window.mapPixelToCoords(last_mouse_pos);
					first_anchor = {static_cast<int>(last_mouse_pos_scaled.x), static_cast<int>(last_mouse_pos_scaled.y)};
					std::cout << "Set first anchor to (" << first_anchor.x << ", " << first_anchor.y << ")" << "\n";
				}
			}

			if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::E) {
					last_mouse_pos_scaled = window.mapPixelToCoords(last_mouse_pos);
					second_anchor = {static_cast<int>(last_mouse_pos_scaled.x), static_cast<int>(last_mouse_pos_scaled.y)};
					std::cout << "Set second anchor to (" << second_anchor.x << ", " << second_anchor.y << ")" << "\n";
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
		window.draw(sprite);
		//

		window.display();
	}
	return std::vector<sf::Vector2i>{first_anchor, second_anchor};
}


void calibrate(Image& image, const std::vector<sf::Vector2i>& anchors) {
	int n_width = anchors[1].x - anchors[0].x + 1;
	int n_height = anchors[1].y - anchors[0].y + 1;

	std::vector<Pixel> new_pixels = {};
	new_pixels.reserve(n_width * n_height);
	for (int y = anchors[0].y; y <= anchors[1].y; y++) {
		for (int x = anchors[0].x; x <= anchors[1].x; x++) {
			new_pixels.push_back(image.pixels.at(x + y * image.width));
		}
	}

	image.pixels = new_pixels;
	image.width = n_width;
	image.height = n_height;
}
