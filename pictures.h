#ifndef PICTURES_H
#define PICTURES_H

#include <boost/filesystem.hpp>

#include <string>
#include <vector>

class Pictures
{
public:
    explicit Pictures(const std::string& directoryPath);

    void changeDirectory(const std::string& directoryPath);

public:
    std::vector<std::string> m_pictures;

private:
    void searchInDirectory();

    bool isPicture(const std::string& file);

private:
    boost::filesystem::path m_directoryPath;
};

#endif // PICTURES_H
