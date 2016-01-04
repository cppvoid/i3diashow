#include "diashow.h"

#include <thread>
#include <cstdlib>
#include <random>

Diashow::Diashow(const std::string& directoryPath, int seconds)
    : m_pictures(directoryPath), m_secondsToWait(seconds)
{
}

void Diashow::runAfterRow()
{
    do
    {
        for(const auto& i : m_pictures.m_pictures) //hmm looks not really good :(
        {
            changeWallpaper(i);

            std::this_thread::sleep_for(m_secondsToWait);
        }
    }while(1);
}

void Diashow::runRandom()
{
    do
    {
        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<int> dis(0, m_pictures.m_pictures.size() - 1);
        changeWallpaper(m_pictures.m_pictures[dis(mt)]);

        std::this_thread::sleep_for(m_secondsToWait);
    }while(1);
}

void Diashow::changeWallpaper(const std::string& filePath)
{
    std::string cmd = "nitrogen --set-auto ";
    cmd += filePath;

    std::system(cmd.c_str());
}

