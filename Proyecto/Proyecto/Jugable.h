#ifndef JUGABLE_H_
#define JUGABLE_H_

#include "Personaje.h"
class Jugable :
	public Personaje
{
public:
	Jugable(Juego* punteroJuego, SDL_Rect spritePar,string objectId);
	virtual ~Jugable();

	void virtual update();

	Personaje::atributos getStats() { return stats; };
	virtual void onColisionEnter(Objeto* obj = nullptr);
	void quitarInmunidad(){
		inmune = false;
	}

protected:
	//Booleanas para el control del movimiento, utilizadas en el movControl;
	//Mueve.
	void move();
	//Recoge el input de la clase Juego.
	void movControl();
	//Controla que pare suave.
	void afinarMov(int vel, int lim);
	//Acceso inventario
	//void inventario();
	bool lel = true;
	bool inmune = false;
	SDL_TimerID timerInmune;

};
#endif
