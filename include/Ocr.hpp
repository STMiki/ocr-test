#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <tesseract/baseapi.h>
#include <vector>

class Ocr {
public:
    Ocr(const std::string &lang = "eng");
    ~Ocr() = default;

    std::vector<std::string> getTextFromImage(const sf::Texture &path);

private:
    tesseract::TessBaseAPI api;
};
