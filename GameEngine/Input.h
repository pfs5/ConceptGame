#pragma once
#include <SFML/Window.hpp>

/**
	Class handles all out-of-game inputs. Provides static methods for accessing user inputs.
**/
class Input {
public:
	static const int NUMBER_OF_KEYS = 256;

private:
	static bool m_key[NUMBER_OF_KEYS];
	static bool m_keyDown[NUMBER_OF_KEYS];
	static bool m_keyUp[NUMBER_OF_KEYS];

public:
	// ## Keys enum ##
	enum KeyCode : int {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
		LCTRL, RCTRL, LALT, RALT, SPACE, LSHIFT, RSHIFT, ENTER, ESCAPE,
		LARROW, RARROW, UARROW, DARROW
	};

	// ## Static key methods ##
	/**
	Return true if the key is pressed in this frame, false otherwise.
	**/
	static bool getKey(KeyCode _key);

	/**
	Return true if the key has been pressed since the last frame;
	**/
	static bool getKeyDown(KeyCode _key);

	/**
	Return true if the key has been released since the last frame;
	**/
	static bool getKeyUp(KeyCode _key);

	// ## Methods called by the engine ##
	static void update();

private:
	static void updateKey(Input::KeyCode _key, sf::Keyboard::Key _sfmlKeyCode);
};