#include "Ocr.hpp"
#include <allheaders.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <tesseract/publictypes.h>

Ocr::Ocr(const std::string &lang)
{
    api.Init(NULL, lang.c_str(), tesseract::OEM_LSTM_ONLY);
    api.SetPageSegMode(tesseract::PSM_AUTO);
}

std::vector<std::string> Ocr::getTextFromImage(const sf::Texture &target)
{
    std::cout << "Getting text from image" << std::endl;
    std::vector<std::string> result;
    std::vector<uint8_t> pixels;

    target.copyToImage().saveToMemory(pixels, "png");
    auto image = pixReadMemPng(pixels.data(), pixels.size());
    api.SetImage(image);
    api.SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_LINE);

    if (api.Recognize(nullptr)) {
        std::cout << "Error while recognizing text" << std::endl;
        return result;
    }
    tesseract::ResultIterator *ri = api.GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    if (ri != nullptr) {
        std::cout << "getting something !" << std::endl;
        do {
            const char *word = ri->GetUTF8Text(level);
            // float conf = ri->Confidence(level);
            if (word != nullptr) {
                std::cout << "word: " << word << std::endl;
                result.emplace_back(word);
                delete[] word;
            } else
                std::cout << "word is null" << std::endl;
        } while (ri->Next(level));
    }
    pixDestroy(&image);
    delete ri;
    return result;
}
