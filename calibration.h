#pragma once

#include <SFML/Graphics.hpp>
#include "image.h"

std::vector<sf::Vector2i> calibrate_setup(const Image& image);
void calibrate(Image& image, const std::vector<sf::Vector2i>& anchors);
