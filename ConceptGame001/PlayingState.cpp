#include "PlayingState.h"
#include "Debug.h"
#include "Input.h"

#include <SFML/Window.hpp>

PlayingState::PlayingState() {
}


PlayingState::~PlayingState() {
}

void PlayingState::update(float _dt) {
	Debug::log(Input::getKey(Input::KeyCode::Num0));
}

void PlayingState::draw() {
}
