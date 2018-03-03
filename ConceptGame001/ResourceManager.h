#pragma once

#include <map>
#include <SFML/Graphics.hpp>

/**
	Manages all "heavy" external resources for the game and allows easy access by name using the singleton pattern.

	Handles images, fonts, ...
**/
class ResourceManager {
	// Folders
	const std::string RESOURCE_MANAGER_DATA = "resources/resource_manager.json";
	const std::string FONT_FOLDER = "resources/fonts/";
	const std::string TEXTURE_FOLDER = "resources/textures/";

	const std::map<std::string, sf::Font*> m_fonts = loadFonts();
	const std::map<std::string, sf::Texture*> m_textures = loadTextures();

	ResourceManager() {};
public:
	#pragma region Singleton
	static ResourceManager & getInstance() {
		static ResourceManager instance;
		return instance;
	}
	#pragma endregion

	sf::Font * getFont(std::string _fontName);
	sf::Texture * getTexture(std::string _textureName);

private:
	std::map<std::string, sf::Font*> loadFonts();
	sf::Font * loadFont(const std::string & _fileName);

	std::map<std::string, sf::Texture*> loadTextures();
	sf::Texture * loadTexture(const std::string & _fileName);
};