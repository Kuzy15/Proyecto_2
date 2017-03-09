#include "ZonaAccion.h"
#include "Entidad.h"


ZonaAccion::ZonaAccion(Juego* punteroJuego): pJuego(punteroJuego)
{
	niveles.push_back(new Room(pJuego, 0, 0, Direcciones{ false,true,false, false }));
	niveles.push_back(new Room(pJuego, niveles.at(0)->getArea().x, niveles.at(0)->getArea().y + niveles.at(0)->getArea().h, Direcciones{ true,false,true, false }));
	niveles.push_back(new Room(pJuego, niveles.at(1)->getArea().x + niveles.at(1)->getArea().w, niveles.at(1)->getArea().y, Direcciones{ false,false, false,true }));
	nivelActual = niveles.at(0);
}


ZonaAccion::~ZonaAccion()
{
	nivelActual = nullptr;
}

void ZonaAccion::draw(){
	nivelActual->render();

}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	nivelActual->update();
	
}

void ZonaAccion::setNivelActual(){
	//Actualizamos el parametro que indica el nivel en el que estamos
	//y  se lo notificamos a la c�mara.
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	int i = 0;
	bool stop = false;
	while (i < niveles.size()){
		if (niveles[i]->dentroRoom(&pj)){
			nivelActual = niveles[i];
		}
		else {
			niveles[i]->stop();
		}
		i++;
	}
	pJuego->getCamera()->setLimite(nivelActual->getArea());
}

SDL_Rect ZonaAccion::getNivelActual() {

	return nivelActual->getArea();

}