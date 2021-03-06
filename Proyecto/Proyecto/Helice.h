#pragma once
#include "Enemigo.h"
class Helice :
	public Enemigo
{
public:
	Helice(Juego* punteroJuego, int ,int);
	~Helice();
	void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void move();
	virtual void comportamiento();
	void disparo();

private:

	float jugx;
	float jugy;
	bool visible;
	int cadencia = 1000;
	Uint32 contador = 0;
	int rng;
};
