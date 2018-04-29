#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
	Manages all "heavy" external resources for the game and allows easy access by name using the singleton pattern.

	Handles images, fonts, ...
**/
class ResourceManager {
	// Folders
	const std::string RESOURCE_MANAGER_DATA = "../resources/resource_manager.json";
	const std::string FONT_FOLDER = "../resources/fonts/";
	const std::string TEXTURE_FOLDER = "../resources/textures/";
	const std::string AUDIO_FOLDER = "../resources/audio/";

	const std::map<std::string, sf::Font*> m_fonts = loadFonts();
	const std::map<std::string, sf::Texture*> m_textures = loadTextures();
	const std::map<std::string, sf::SoundBuffer*> m_sounds = loadSounds();
	const std::map<std::string, sf::Music*> m_music = loadMusic();

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
	sf::SoundBuffer * getSound(std::string _soundName);
	sf::Music * getMusic(std::string _musicName);
private:
	std::map<std::string, sf::Font*> loadFonts();
	sf::Font * loadFont(const std::string & _fileName);

	std::map<std::string, sf::Texture*> loadTextures();
	sf::Texture * loadTexture(const std::string & _fileName);

	std::map<std::string, sf::SoundBuffer*> loadSounds();
	sf::SoundBuffer * loadSound(const std::string & _fileName);

	std::map<std::string, sf::Music*> loadMusic();
	sf::Music * loadMusicFile(const std::string & _fileName);
};