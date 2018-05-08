#pragma once
#include <GameState.h>

#include <SFML/Graphics.hpp>
class SplashState : public GameState {
	enum SPLASH_STATE {
		FADE_IN,
		FADE_OUT,
		HOLD
	};

	std::vector<sf::Texture *> m_splashScreens;
	sf::Sprite m_splashSprite;

	float m_timer;
	float m_fadeTimer;
	int m_currentSplash;

	SPLASH_STATE m_state;
	float m_currentAlpha;

	// Preloaded game
	GameState * m_gameState;

	// Parameters
	const int SPLASH_SCREENS = 4;
	const std::string SPLASH_SCREEN_PREFIX = "splash";
	const sf::Vector2f SPLASH_SIZE{ 1024.f, 1024.f };

	const float TIME_PER_SPLASH = 2.f;	//2
	const float FADE_TIME = 1.f;		//1
public:
	SplashState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;

	void fadeInState(float _dt);
	void fadeOutState(float _dt);
	void holdState(float _dt);
};