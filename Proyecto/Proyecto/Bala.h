#ifndef BALA_H
#define BALA_H

#include "Entidad.h"
class Bala :
	public Entidad
{
	float32 _vel;
	int direccion; //1 arriba ,2 derechas, 3 abjo y 4 adivinalo
public:
	Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId,float32 vel,int dir);
	~Bala();
	virtual void onColisionEnter(Objeto* contactObject);
};
#endif
