#include "HUD.h"
#include "Jugable.h"


HUD::HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim): pjuego(punteroJuego)
{
	id = objectId;
	anim = objectAnim;// Para las vidas esto tiene que ser: "Cuatro", solo al principio.

	animacion.numFrames = 0;
	animacion.textura = pjuego->getTextura(id, anim);// No se si el nombre este tiene que tener longitud 4, 
	//porque en juego initMedia() se hace substr de una cadena de 4 caracteres.
	animacion.rect = nullptr;

	sprite = new SDL_Rect(spritePar);
}


HUD::~HUD()
{

	delete sprite;
	sprite = nullptr;
}

void HUD::draw(Objeto* personaje){

	int n;

	n = static_cast<Jugable*>(personaje)->getStats().vida;
	
	switch (n){
		
	case 4:// Tengo que ver como hacer para cuando se suman vidas que se vuelva a poner "Cuatro"
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.rect,90);
		break;
	case 3:
		id = "Battery3";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.rect,90);
		break;
	case 2:
		id = "Battery2";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.rect,90);
		break;
	case 1:
		id = "Battery1";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.rect, 90);
		break;
	}

}