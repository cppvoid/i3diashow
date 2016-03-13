#include "pictures.h"

#include <stdexcept>
#include <regex>

Pictures::Pictures(const std::string& directoryPath)
    : m_directoryPath(directoryPath)
{
    searchInDirectory();
}

void Pictures::changeDirectory(const std::string& directoryPath)
{
    m_directoryPath = directoryPath;

    searchInDirectory();
}

void Pictures::update()
{
	m_pictures.clear();

	searchInDirectory();
}

void Pictures::searchInDirectory()
{
    namespace fs = boost::filesystem;

    if(!fs::exists(m_directoryPath))
    {
        throw std::runtime_error(std::string("cannot open: ") + m_directoryPath.string());
    }

    fs::directory_iterator iterEnd;

    for(fs::directory_iterator iter(m_directoryPath); iter != iterEnd; ++iter)
    {
        if(fs::is_regular_file(iter->status()))
        {
            std::string file = iter->path().string();

            if(isPicture(file))
            {
                m_pictures.push_back(file);
            }
        }
    }
}

bool Pictures::isPicture(const std::string& file)
{
    std::regex regex("^.*\\.(png|jpg|jpeg)$");

    return std::regex_match(file, regex);
}

