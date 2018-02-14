#include "ResourceManager.h"

sf::Font * ResourceManager::getFont(std::string _fontName) {
	try {
		return m_fonts.at(_fontName);
	} catch (std::out_of_range e) {
		return nullptr;
	}
	
}

sf::Font * ResourceManager::loadFont(const std::string & _fileName) {
	sf::Font * f = new sf::Font();
	f->loadFromFile(FONT_FOLDER + _fileName);

	return f;
}
