#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include "rectangle.h"

// Declaraciones anticipadas
class Texture;
class Balloon;
class Bow;
class Arrow;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Número de actualizaciones por segundo
	static constexpr int FRAME_RATE = 30;
	// Periodo entre actualizaciones en milisegundos
	static constexpr int FRAME_PERIOD = 1000 / FRAME_RATE;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;

	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOONS,
		REWARDS,
		NUM_TEXTURES
	};

	// struct para colores RGB
	struct RGBColor
	{
		Uint8 r, g, b;
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update(const float& delta);
	void handleEvents();

	void addBalloonRnd();
	void loadLevel(int level);
	
	bool exit;

	// Atributos del juego
	int nArrows = 7;
	float balDelay = 500;
	RGBColor bgcolor = { 44, 168, 94 };
	Uint16 score = 0;
	
	// Variables internas
	std::mt19937_64 rndGenerator;
	float lastUpdate;
	float balElapsed;

	// Elemento del juego
	std::vector<Balloon*> balloons;
	std::vector<Arrow*> arrows;
	Bow* bow;

public:
	Game();
	~Game();

	// spawnea un arrow
	void addArrow(const Vector2D<float>& pos);

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// devuelve el numero de flechas
	const int& getArrows() { return nArrows; };

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
