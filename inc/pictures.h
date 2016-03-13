#ifndef PICTURES_H
#define PICTURES_H

#include <boost/filesystem.hpp>

#include <string>
#include <vector>

class Pictures
{
	using iterator = std::vector<std::string>::iterator;

	using const_iterator = std::vector<std::string>::const_iterator;

public:
    explicit Pictures(const std::string& directoryPath);

    void changeDirectory(const std::string& directoryPath);

	void update();

	iterator begin() { return m_pictures.begin(); }

	iterator end() { return m_pictures.end(); }

	const_iterator cbegin() { return m_pictures.cbegin(); }

	const_iterator cend() { return m_pictures.cend(); }

public:
    std::vector<std::string> m_pictures;

private:
    void searchInDirectory();

    bool isPicture(const std::string& file);

private:
    boost::filesystem::path m_directoryPath;
};

#endif // PICTURES_H
