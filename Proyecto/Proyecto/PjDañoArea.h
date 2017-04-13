#pragma once
#include "Jugable.h"
class PjDa�oArea :
	public Jugable
{
public:
	PjDa�oArea(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~PjDa�oArea();

	void reactivarMele(){
		atamele = true;
	}

protected:
		
	void ataqueMele();
	virtual void update();
	bool atamele = true;
	bool destroyBody = false;


	b2Shape* st;
	b2BodyDef bdt;
	b2Body* bt;
	b2FixtureDef fdt;
};

