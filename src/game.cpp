#include "game.h"
#include <string>
#include <SDL3_image/SDL_image.h>
#include "texture.h"
#include "Balloon.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	TextureSpec{"arrow.png"},
	TextureSpec{"balloons.png", 7 , 6},

};

Game::Game()
  : exit(false)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
		throw "window or renderer: "s + SDL_GetError();

	SDL_SetRenderDrawColor(renderer, bgcolor.r, bgcolor.g, bgcolor.b, SDL_ALPHA_OPAQUE);

	// Carga las texturas al inicio
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (...) {
		// TODO: liberar la memoria reservada
		for (Texture* tex : textures) delete tex;
		throw; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Inicializa variables
	rndGenerator = std::mt19937_64(std::random_device()());
	lastUpdate = SDL_GetTicks();
	balElapsed = 0;

	// Crea los objetos del juego
	addBalloonRnd();
}

Game::~Game()
{
	// TODO: liberar la memoria reservada por la clase
	for (Texture* tex : textures) delete tex;
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	for (Balloon bal : balloons) bal.render();

	SDL_RenderPresent(renderer);
}

void
Game::update(const float& delta)
{
	// generación de globos
	balElapsed += delta;
	if (balElapsed >= balDelay) {
		balElapsed = 0;
		addBalloonRnd();
	}

	// globos
	for (int i = 0; i < balloons.size(); i++) {
		if (!balloons[i].update(delta)) {
			balloons.erase(balloons.begin() + i);
			i--;
		}
	}

}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego

		float currentUpate = SDL_GetTicks();
		update(currentUpate - lastUpdate);
		lastUpdate = currentUpate;

		handleEvents();
		render();
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
	}
}

 bool
 Game::checkCollision(const Rectangle& rect)
 {
	// TODO
	return false;
 }

 void Game::addBalloonRnd() {
	 balloons.push_back(Balloon(
		 Vector2D(
			 (float)uniform_int_distribution<int>(WINDOW_WIDTH / 3.0f, WINDOW_WIDTH - 125)(rndGenerator),
			 (float)WINDOW_HEIGHT), 
		 -(float)uniform_int_distribution<int>(100, 500)(rndGenerator),
		 getTexture(BALLOONS), 
		 uniform_int_distribution<int>(0,6)(rndGenerator)));
 }
