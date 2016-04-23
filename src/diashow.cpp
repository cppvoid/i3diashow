#include "diashow.h"

#include <thread>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <string>

Diashow::Diashow(const std::string& directoryPath, int32_t seconds)
    : m_pictures(directoryPath), m_secondsToWait(seconds)
{
}

void Diashow::runAfterRow()
{
    for(;;)
    {
        for(const auto& i : m_pictures)
        {
            changeWallpaper(i);

            std::this_thread::sleep_for(m_secondsToWait);
        }
		m_pictures.update();
    }
}

void Diashow::runRandom()
{
	std::random_device rd;
    std::mt19937 mt(rd());

	for(;;)
	{
		std::shuffle(m_pictures.begin(), m_pictures.end(), mt);

		for(const auto& i : m_pictures)
		{
			changeWallpaper(i);

			std::this_thread::sleep_for(m_secondsToWait);
		}
		m_pictures.update();
    }
}

void Diashow::changeWallpaper(const std::string& filePath)
{
    std::string cmd = "nitrogen --set-auto ";
    cmd += filePath;

    auto result = std::system(cmd.c_str());

	if(result != 0)
	{
		throw std::runtime_error("nitrogen ended with exit code: " + std::to_string(result));
	}
}

