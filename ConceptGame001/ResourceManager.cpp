#include "ResourceManager.h"
#include "Debug.h"

sf::Font * ResourceManager::getFont(std::string _fontName) {
	try {
		return m_fonts.at(_fontName);
	} catch (std::out_of_range e) {
		return nullptr;
	}
}

sf::Texture * ResourceManager::getTexture(std::string _textureName) {
	try {
		return m_textures.at(_textureName);
	} catch (std::out_of_range e) {
		return nullptr;
	}
}

std::map<std::string, sf::Font*> ResourceManager::loadFonts() {
	std::map<std::string, sf::Font*> fonts;

	// Load fonts
	fonts.emplace("atwriter", loadFont("atwriter.ttf"));

	return fonts;
}

sf::Font * ResourceManager::loadFont(const std::string & _fileName) {
	sf::Font * f = new sf::Font();
	if (!f->loadFromFile(FONT_FOLDER + _fileName)) {
		Debug::logError("Error loading font " + _fileName);
	}

	return f;
}

std::map<std::string, sf::Texture*> ResourceManager::loadTextures() {
	std::map<std::string, sf::Texture*> textures;

	// Load textures
	textures.emplace("test", loadTexture("test.png"));


	return textures;
}

sf::Texture * ResourceManager::loadTexture(const std::string & _fileName) {
	sf::Texture * t = new sf::Texture();
	if (!t->loadFromFile(TEXTURE_FOLDER + _fileName)) {
		Debug::logError("Error loading texture " + _fileName);
	}

	return t;
}
