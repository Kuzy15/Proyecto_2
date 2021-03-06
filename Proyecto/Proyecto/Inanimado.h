#ifndef INANIMADO_H_
#define INANIMADO_H_


#include "SelecZonaMenu.h"
#include "Entidad.h"
#include "Cambio.h"
#include "Crafteo.h"
#include "Play.h"
#include "Historia.h"
#include "FinalJuego.h"

class Inanimado :
	public Entidad
{
public:
	Inanimado(Juego * pj, SDL_Rect Tam, string id): Entidad(pj,Tam,id){
		bodyDef.type = b2_staticBody;
		bodyDef.fixedRotation = true;
		bodyDef.position.Set(pos.x, pos.y);
		body = pJuego->getWorld()->CreateBody(&bodyDef);
		body->SetUserData(this);
		if (id == "agujero") {
			shape = new b2CircleShape();
			static_cast<b2CircleShape*>(shape)->m_p = { (float32)(sprite->w / PPM) / 2, (float32)(sprite->h / PPM )/ 2 };
			static_cast<b2CircleShape*>(shape)->m_radius = (Tam.w / PPM )/ 2;
		}
		else {
			shape = new b2PolygonShape;
			static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
		}
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		
	}
	virtual ~Inanimado() {
		
	};
	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {};
};

//==============================================================================================
//AGUJERO
class Agujero:
	public Inanimado
{
public:
	Agujero(Juego * Pj, int x,int y, int w,int h) :Inanimado(Pj, SDL_Rect{x,y,w,h}, "agujero") {
	
		fDef.filter.categoryBits = Juego::ESCENARIO_NOCOL;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO;
		body->CreateFixture(&fDef);	
	}
	~Agujero() { };
private:

};
//==============================================================================================
//TUBERIA
class Tuberia: public Inanimado
{
public:
	Tuberia(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x,y, w,h }, "Tuberia") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR; 
		body->CreateFixture(&fDef);
	};
	~Tuberia() {};
};
//==============================================================================================
//NAVE
class Nave : public Inanimado
{
public:
	Nave(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x,y, w, h}, "Nave") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Nave() {};
};

//==============================================================================================
//CHATARRA
class Chatarra : public Inanimado
{
public:
	Chatarra(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, w,h }, "chatarro") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Chatarra() {};
};

//==============================================================================================
//SELECTOR DE ZONA
class  SelectorZona : public Inanimado
{
public:
	SelectorZona(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorZona") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorZona() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new SelecZonaMenu(pJuego));
	}
};

//==============================================================================================
//SELECTOR DE Cambio
class  SelectorCambio : public Inanimado
{
public:
	SelectorCambio(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorPersonaje") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorCambio() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new Cambio(pJuego, static_cast<Play*>(pJuego->topState())->personaje));
	}
};
	//==============================================================================================
//SELECTOR DE CRAFTEO
class  SelectorCrafteo : public Inanimado
{
public:
	SelectorCrafteo(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 3 }, "SelectorCrafteo") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorCrafteo() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new Crafteo(pJuego));
	}
};
//==============================================================================================
//HISTORIA	
class  VerHistoria : public Inanimado
{
public:
	VerHistoria(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorHistoria") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~VerHistoria() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new Historia(pJuego));
	}
};
//==============================================================================================
//SELECTOR DE Cambio
class  FinZona : public Inanimado
{
public:
	FinZona(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, w, h }, "SelectorCambio") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~FinZona() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {
		pJuego->setFinZona();
	}
};
//==============================================================================================
//Nave
class  NaveJuego : public Inanimado
{
	enum Estado { FASE0 = 0, FASE1 = 1, FASE2 = 2, FASE3 = 3, READY = 4};
	Estado estado = FASE0;
public:
	NaveJuego(Juego * Pj, int x, int y, int w, int h) : Inanimado(Pj, SDL_Rect{ x, y, w, h }, "NaveFase0") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
		estado = (Estado)pJuego->getProgresoNave();
		switch (estado)
		{
		case NaveJuego::FASE0:
			id = "NaveFase0";
			break;
		case NaveJuego::FASE1:
			id = "NaveFase1";
			break;
		case NaveJuego::FASE2:
			id = "NaveFase2";
			break;
		case NaveJuego::FASE3:
			id = "NaveFase3";
			break;
		case NaveJuego::READY:
			id = "NaveFase4";
			break;
		default:
			break;
		}
		changeTexture(id);
		Pj->setNave(this);
	};
	~NaveJuego() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {
		
		if (estado == Estado::READY){
			pJuego->pushState(new FinalJuego(pJuego));
		}
	}
	void changeTexture(string i){
		currentAnim->textura = pJuego->getTextura(i, "idle");
	}
};
//==============================================================================================
//TriggerDisparo
class  TriggerDisparo : public Inanimado
{
public:
	TriggerDisparo(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, w, h }, "Trigger") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		fDef.isSensor = true;
		body->CreateFixture(&fDef);
	};
	~TriggerDisparo() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {
		static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::JUGANDO);
	}
};

//================================================================================================
//TriggerBase
class  TriggerBase : public Inanimado
{
public:
	TriggerBase(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, w, h }, "Trigger") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		fDef.isSensor = true;
		body->CreateFixture(&fDef);
	};
	~TriggerBase() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {
		pJuego->firstPlay = false;
		pJuego->setFinZona();
	}
};

#endif // INANIMADO_H_