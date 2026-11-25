#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <list>
#include "rectangle.h"

// Declaraciones anticipadas
class Texture;
class Bow;
class SceneObject;

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
	// Periodo entre frames de animacion en milisegundos
	static constexpr int ANIM_FRAMES_RATE = FRAME_PERIOD * 2;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;
	// Numero por el que son mulitplicadas todas las velocidades
	static constexpr float SPEED_RATIO = 0.1f;
	// Velocidad de las flechas
	static constexpr float DEFAULT_ARROW_SPEED = 10.0f;

	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOONS,
		REWARDS,
		BUTTERFLY,
		NUM_TEXTURES
	};

	// struct para colores RGB
	struct RGBColor
	{
		int r, g, b;

		friend std::ostream& operator<<(std::ostream& out, const RGBColor& rgb) {
			return out << rgb.r << " " << rgb.g << " " << rgb.b;
		}
		friend std::istream& operator>>(std::istream& in, RGBColor& rgb) {
			in >> rgb.r >> rgb.g >> rgb.b;
			return in;
		}
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update(const float delta);
	void handleEvents();

	void addRndBalloon();
	void addRndButterfly();

	void loadFLevel(int level);
	bool loadNextLevel();

	void saveGame();
	void loadGame();
	
	bool exit;

	// Atributos del juego
	int nArrows = 7,
		balPoints = 1,
		goal = 10,
		curLevel = 0;
	float balDelay = 500;
	RGBColor bgcolor = { 44, 168, 94 };
	long score = 0,
		totalScore = 0;
	bool btflyEndgame = false,
		goalEndgame = true;
	
	// Variables internas
	std::mt19937_64 rndGenerator;
	float lastUpdate;
	float balElapsed;
	int mustDelBfr; // cuenta el numero de objetos que tienen que destruirse antes de terminar la partida
	int currentBtfly; // cuenta el numero de mariposas presentes, si llega a cero y la configuracion lo indica termina la partida 

	// Elementos del juego
	std::list<SceneObject*> _objs;
	Bow* bow;

public:
	Game();
	~Game();

	// spawnea un arrow
	void addArrow(const Vector2D<float>& pos);

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// devuelve el numero de flechas restantes
	const int& getArrows() const { return nArrows; };

	// añade base * mult a la puntuacion
	void addScore(int base, int mult);

	// resta uno al contador de butterflies
	void substractBtf() { currentBtfly--; };

	// devuelve el valor en puntos de los globos
	int getBalPoints() const { return balPoints; };

	// Ejecuta el bucle principal del juego
	void run();

	// suma 'num' a unclosableObjs
	void addUnclosable(int num) { mustDelBfr += num; };

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect);

	// Genera un int aleatorio
	int generateRndInt(int min, int max);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
