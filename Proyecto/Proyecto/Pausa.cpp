#include "Pausa.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
#include "Opciones.h"

Pausa::Pausa(Juego * juego) : MenuJuego(juego)//, pR(nullptr)
{
	pJuego->reproducirEfecto("Multiusos");
	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	botones.emplace_back(new BotonIluminado(pJuego, 300, 250, resume, "Continuar","Continua jugando"));
	botones.emplace_back(new BotonIluminado(pJuego, 300, 350, opciones, "Opciones", "Pues opciones y tal"));
	botones.emplace_back(new BotonIluminado(pJuego, 300, 450, returnMenu, "Salir", "Vuelve al menu"));

	//Para a�adir los botones
}


Pausa::~Pausa()
{
}


void Pausa::resume(Juego * jg){
	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popState();
}

void Pausa::returnMenu(Juego * jg){

	jg->freeEstadoss();
	jg->changeState(new MenuPG(jg));
}

void Pausa::opciones(Juego * jg){
	jg->pushState(new Opciones(jg));
}
