#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager {
	// Folders
	const std::string FONT_FOLDER = "resources/fonts/";

	const std::map<std::string, sf::Font*> m_fonts = {{ "atwriter", loadFont("atwriter.ttf")} };

	ResourceManager() {};
public:
	#pragma region Singleton
	static ResourceManager & getInstance() {
		static ResourceManager instance;
		return instance;
	}
	#pragma endregion

	sf::Font * getFont(std::string _fontName);

private:
	sf::Font * loadFont(const std::string & _fileName);
};