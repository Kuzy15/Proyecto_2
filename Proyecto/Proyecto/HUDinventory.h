#pragma once
#include "HUDbase.h"
#include "Juego.h"
class HUDinventory :
	public HUDbase
{
public:
	HUDinventory(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim, Inventory *);
	virtual ~HUDinventory();

	void draw();

	SDL_Rect * getRect() {
		return sprite;
	}
	

	bool getInvState(){
	
		return mostrar;
	};


private:

	Juego* pjuego;
	Inventory * inventario_;

	Juego::Animacion animacion;

	SDL_Rect* sprite;

	string id;

	string anim;

	bool mostrar = false;
};

