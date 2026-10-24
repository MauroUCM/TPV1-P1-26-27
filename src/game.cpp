#include "game.h"
#include <string>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include "texture.h"
#include "Balloon.h"
#include "Bow.h"
#include "Arrow.h"
#include "InfoBar.h"

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
	TextureSpec{"rewards.png", 8, 10},
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

	// lectura del archivo
	loadLevel(1);

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
		// libera la memoria reservada
		for (Texture* tex : textures) delete tex;
		throw; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	// Inicializa variables internas
	rndGenerator = std::mt19937_64(std::random_device()());
	lastUpdate = SDL_GetTicks();
	balElapsed = 0;

	// Crea los objetos del juego
	bow = new Bow(this,
		Vector2D<float>(
			WINDOW_WIDTH / 16, 
			WINDOW_HEIGHT / 2),
		7.0f, 
		getTexture(BOW));
	infobar = new InfoBar(this, getTexture(ARROW));
}

Game::~Game() {
	// Liberacion de la memoria reservada
	for (Texture* tex : textures) delete tex;
	for (Balloon* bal : balloons) delete bal;
	for (Arrow* arr : arrows) delete arr;
	delete bow;
	delete infobar;
}

void Game::render() const {
	SDL_RenderClear(renderer);

	for (Balloon* bal : balloons) bal->render();
	for (Arrow* arr : arrows) arr->render();
	if(bow) bow->render();
	if (infobar) infobar->render();

	SDL_RenderPresent(renderer);
}

void Game::update(const float& delta) {
	if(bow) bow->update(delta);

	// flechas
	for (int i = 0; i < arrows.size(); i++) {
		if (!arrows[i]->update(delta)) {
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
			i--;
		}
	}

	// globos
	for (int i = 0; i < balloons.size(); i++) {
		if (!balloons[i]->update(delta)) {
			delete balloons[i];
			balloons.erase(balloons.begin() + i);			
			i--;
		}
	}

	// generación de globos
	balElapsed += delta;
	if (balElapsed >= balDelay) {
		balElapsed = 0;
		addBalloonRnd();
	}

	// comprueba si es el final del juego
	if (nArrows <= 0 && arrows.empty()) {
		exit = true;
	}

	lastUpdate = SDL_GetTicks();
}

void Game::run() {
	// bucle principal del juego
	while (!exit) { 
		float currentTime = SDL_GetTicks();

		handleEvents();
		update(currentTime - lastUpdate);
		render();

		float elapsedRun = SDL_GetTicks() - currentTime;
		if (elapsedRun < FRAME_PERIOD) {
			SDL_Delay(FRAME_PERIOD - elapsedRun);
		}
	}

	std::cout << "FINAL SCORE: " << score;
}

void Game::handleEvents() {
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		bow->handleEvent(event);
	}
}

bool Game::checkCollision(const Rectangle& rect){
	for (Balloon* bal : balloons) {
		if (bal->hit(rect)) {
			score += balPoints;
			std::cout << "Current score: " << score << "\n";
			return true;
		}
	}

	return false;
}

 void Game::addBalloonRnd() {
	 balloons.push_back(new Balloon(
		 Vector2D(
			 (float)uniform_int_distribution<int>(WINDOW_WIDTH / 3.0f, WINDOW_WIDTH - BOW_SIZE)(rndGenerator),
			 (float)WINDOW_HEIGHT), 
		 -(float)uniform_int_distribution<int>(1, 5)(rndGenerator),
		 getTexture(BALLOONS), 
		 uniform_int_distribution<int>(0,6)(rndGenerator)));
 }

 void Game::addArrow(const Vector2D<float>& pos) {
	 nArrows--;
	 arrows.push_back(new Arrow(this, pos, getTexture(ARROW), 100.0f));
 }

 void Game::loadLevel(int level) {
	// Lectura del archivo
	try {
		std::ifstream levelIn;
		string fileName = (string)LEVEL_ROOT + std::to_string(level) + ".txt",
			key;
		int aux;

		levelIn.open(fileName);
		if (!levelIn.is_open()) throw "Level file not found.";

		while (levelIn) {
			levelIn >> key;

			if (key == "arrows") {			// numero de flechas
				levelIn >> aux;
				nArrows = aux;
			}
			else if (key == "baldelay") {	// tiempo entre globos
				levelIn >> aux;
				balDelay = aux;
			}
			else if (key == "bgcolor") {	// color de fondo
				int r, g, b;
				levelIn >> r >> g >> b;
				bgcolor = { (Uint8)r, (Uint8)g ,(Uint8)b };
			}
			else if (key == "balpoints") {	// puntos por globo
				levelIn >> aux;
				balPoints = aux;
			}
			else if (key == "goal") {		// meta de puntos
				levelIn >> aux;
				goal = aux;
			}
			else {	// descartar linea
				levelIn.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
	catch (const char* error) {
		std::cout << "ERROR: "<< error << " Default settings won't be overriden.\n";

		
	}

	// se aplica el color de fondo independientemente de si ha sido cambiado
	SDL_SetRenderDrawColor(renderer, bgcolor.r, bgcolor.g, bgcolor.b, SDL_ALPHA_OPAQUE);
 }
