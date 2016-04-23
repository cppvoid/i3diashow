#ifndef DIASHOW_H
#define DIASHOW_H

#include "pictures.h"

#include <string>
#include <chrono>
#include <cstdint>

class Diashow
{
public:
    explicit Diashow(const std::string& directoryPath, int32_t seconds);

    void runAfterRow();

    void runRandom();

private:
    void changeWallpaper(const std::string& filePath);

private:
    Pictures m_pictures;

    std::chrono::seconds m_secondsToWait;
};

#endif // DIASHOW_H
