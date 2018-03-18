#include "Input.h"

bool Input::m_key[Input::NUMBER_OF_KEYS];
bool Input::m_keyDown[Input::NUMBER_OF_KEYS];
bool Input::m_keyUp[Input::NUMBER_OF_KEYS];

bool Input::getKey(KeyCode _key) {
	return m_key[static_cast<int>(_key)];
}

bool Input::getKeyDown(KeyCode _key) {
	return m_keyDown[static_cast<int>(_key)];
}

bool Input::getKeyUp(KeyCode _key) {
	return m_keyUp[static_cast<int>(_key)];
}

void Input::update() {
	updateKey(KeyCode::A, sf::Keyboard::A);
	updateKey(KeyCode::B, sf::Keyboard::B);
	updateKey(KeyCode::C, sf::Keyboard::C);
	updateKey(KeyCode::D, sf::Keyboard::D);
	updateKey(KeyCode::E, sf::Keyboard::E);
	updateKey(KeyCode::F, sf::Keyboard::F);
	updateKey(KeyCode::G, sf::Keyboard::G);
	updateKey(KeyCode::H, sf::Keyboard::H);
	updateKey(KeyCode::I, sf::Keyboard::I);
	updateKey(KeyCode::J, sf::Keyboard::J);
	updateKey(KeyCode::K, sf::Keyboard::K);
	updateKey(KeyCode::L, sf::Keyboard::L);
	updateKey(KeyCode::M, sf::Keyboard::M);
	updateKey(KeyCode::N, sf::Keyboard::N);
	updateKey(KeyCode::O, sf::Keyboard::O);
	updateKey(KeyCode::P, sf::Keyboard::P);
	updateKey(KeyCode::R, sf::Keyboard::R);
	updateKey(KeyCode::S, sf::Keyboard::S);
	updateKey(KeyCode::T, sf::Keyboard::T);
	updateKey(KeyCode::U, sf::Keyboard::U);
	updateKey(KeyCode::V, sf::Keyboard::V);
	updateKey(KeyCode::W, sf::Keyboard::W);
	updateKey(KeyCode::X, sf::Keyboard::X);
	updateKey(KeyCode::Y, sf::Keyboard::Y);
	updateKey(KeyCode::Z, sf::Keyboard::Z);

	updateKey(KeyCode::Num0, sf::Keyboard::Num0);
	updateKey(KeyCode::Num1, sf::Keyboard::Num1);
	updateKey(KeyCode::Num2, sf::Keyboard::Num2);
	updateKey(KeyCode::Num3, sf::Keyboard::Num3);
	updateKey(KeyCode::Num4, sf::Keyboard::Num4);
	updateKey(KeyCode::Num5, sf::Keyboard::Num5);
	updateKey(KeyCode::Num6, sf::Keyboard::Num6);
	updateKey(KeyCode::Num7, sf::Keyboard::Num7);
	updateKey(KeyCode::Num8, sf::Keyboard::Num8);
	updateKey(KeyCode::Num9, sf::Keyboard::Num9);

	updateKey(KeyCode::LCTRL, sf::Keyboard::LControl);
	updateKey(KeyCode::RCTRL, sf::Keyboard::RControl);
	updateKey(KeyCode::LALT, sf::Keyboard::LAlt);
	updateKey(KeyCode::RALT, sf::Keyboard::RAlt);
	updateKey(KeyCode::SPACE, sf::Keyboard::Space);
	updateKey(KeyCode::LSHIFT, sf::Keyboard::LShift);
	updateKey(KeyCode::RSHIFT, sf::Keyboard::RShift);
	updateKey(KeyCode::ENTER, sf::Keyboard::Return);
	updateKey(KeyCode::ESCAPE, sf::Keyboard::Escape);

	updateKey(KeyCode::LARROW, sf::Keyboard::Left);
	updateKey(KeyCode::RARROW, sf::Keyboard::Right);
	updateKey(KeyCode::UARROW, sf::Keyboard::Up);
	updateKey(KeyCode::DARROW, sf::Keyboard::Down);

}

void Input::updateKey(Input::KeyCode _key, sf::Keyboard::Key _sfmlKeyCode) {
	bool newKeyValue = sf::Keyboard::isKeyPressed(_sfmlKeyCode);
	int keyIndex = static_cast<int>(_key);
	// check key down and key up
	bool frameDifference = m_key[keyIndex] != newKeyValue;
	m_keyDown[keyIndex] = (newKeyValue) ? frameDifference : false;
	m_keyUp[keyIndex] = (!newKeyValue) ? frameDifference : false;

	// update key value
	m_key[keyIndex] = newKeyValue;
}
