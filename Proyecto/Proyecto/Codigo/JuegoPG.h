#ifndef JUEGOPG_H
#define JUEGOPG_H
#include <vector>
#include <string>
#include <Box2D\Box2D.h>
#include "TexturasSDL.h"
#include <float.h>
#include <stack>
class EstadoJuego;

using namespace std;
class JuegoPG
{
	int score;

	stack<EstadoJuego*> estados;

	void initMedia();

	void freeMedia();

	bool initSDL();

	void closeSDL();

	void run();

	void handleInput();
	SDL_Rect r;
	SDL_Rect r2;
	b2Vec2 pos;
	b2World * world;
	b2Body * tostadora;
	b2Body * gato;
	b2Body * wall;

	SDL_Rect recta;

	SDL_Window* pWindow;

	SDL_Renderer* pRenderer;

	vector<TexturasSDL*> texturas;

	vector<string> nombreTexturas;

	struct Ventana { //Struct que contiene el tama�o y el color de la ventana.
		int ancho;
		int alto;
		SDL_Color color;
	} window;

	bool error, gameOver, exit;

	struct Mouse {
		int x;
		int y;

	}mousePos;
	
	SDL_Rect fondoRect;

	char moveC;

	bool dcha, izq, up, down;

	bool KEYS[322];

public:
	JuegoPG(b2World * mundo);
	~JuegoPG();

	enum Texturas_t {
		tTostadora, tGato, tFondo
	};
	
	void move(char c);

	TexturasSDL* getTextura(Texturas_t t);

	SDL_Renderer* getRender() const;

	void getMousePos(int &mpx, int &mpy) const;

	bool getError();

	void salir();

	bool handle_event();

	static const Uint32  MSxUpdate = 17;

	Uint32 lastUpdate;

	void update();

	void draw();
};


#endif 