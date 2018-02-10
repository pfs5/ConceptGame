#pragma once
#pragma once
#include <SFML/Graphics.hpp>
namespace Display {
	constexpr uint16_t HEIGHT = 600;
	constexpr uint16_t WIDTH = (uint16_t)HEIGHT * 16.f / 9.f;
	const std::string TITLE = "Concept game";

	const float UPS = 60;   // 60

	/**
	* Initialize window
	*/
	void init();

	/**
	* Clears window using input color
	* @param colour
	*/
	void clear(const sf::Color& _color = { 0, 0, 0 });

	/**
	* Display content on window
	*/
	void display();

	/**
	* Draw object on window
	* @param drawable
	*/
	void draw(const sf::Drawable& _drawable);

	/**
	*
	*/
	void checkWindowEvents();

	/**
	* Check if window is open
	* @return
	*/
	bool isOpen();

	/**
	* Returns window reference
	* @return
	*/
	sf::RenderWindow &getWindow();
};