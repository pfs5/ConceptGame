#include "ResourceManager.h"
#include "Debug.h"
#include "json.h"

#include <fstream>

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
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto font : data["fonts"]) {
			fonts.emplace(font["name"], loadFont(font["path"]));
		}

		file.close();
	}

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
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto tex : data["textures"]) {
			textures.emplace(tex["name"], loadTexture(tex["path"]));
		}

		file.close();
	}

	return textures;
}

sf::Texture * ResourceManager::loadTexture(const std::string & _fileName) {
	sf::Texture * t = new sf::Texture();
	if (!t->loadFromFile(TEXTURE_FOLDER + _fileName)) {
		Debug::logError("Error loading texture " + _fileName);
	}

	return t;
}
