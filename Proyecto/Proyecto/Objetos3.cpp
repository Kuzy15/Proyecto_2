#include "Objetos3.h"
#include "checkML.h"


Objetos3::Objetos3(Juego* pJuego) : Crafteo(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "button", 50, 50, mecanismo, "Mecanismo"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 150, combustible, "Combustible"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 200, fibraCarbono, "FibraCarbono"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 250, moduloComandos, "ModuloComandos"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 300, mensaje, "Eje"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 350, mensaje, "Pantalla"));
	//botones.emplace_back(new Boton(pJuego, "boton", 50, 200, mensaje, "ModuloComados"));
	botones.emplace_back(new Boton(pJuego, "button", 575, 475, salir, "Salir"));
	animacion.loadTextura(pJuego->getTextura(botones[0]->getNombre(), "idle"));

	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));
}


Objetos3::~Objetos3()
{
}

void Objetos3::draw() {

	pJuego->getTextura("HudCraft3", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
	if (botones[activo]->getNombre() == "Eje" || botones[activo]->getNombre() == "Pantalla"){
		pJuego->getTextura("HudCraft", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);
		for (int i = 0; i < botones.size(); i++)
		{
			botones[i]->draw();
		}
		animacion.textura = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 530, 20, 125, 125 }, animacion.currentRect(), 0.0);

		//receta(botones[activo]->getNombre());

		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){

			Texto.loadTexto(pJuego->getRender(), "0");
			Texto.draw(pJuego->getRender(), 650, 50);
		}
		else{
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 650, 50);
			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
		}
	
	}

	else if (botones[activo]->getNombre() != "Salir"){
		animacion.textura = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 530, 20, 125, 125 }, animacion.currentRect(), 0.0);

		receta(botones[activo]->getNombre());

		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){
			
			Texto.loadTexto(pJuego->getRender(), "0");
			Texto.draw(pJuego->getRender(), 650, 50);
		}
		else{
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 650, 50);
			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
		}
	}
	else{
		pJuego->getTextura("HudCraft", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);
		for (int i = 0; i < botones.size(); i++)
		{
			botones[i]->draw();
		}
	}

}

void Objetos3::update() {



	botones[activo]->normal();
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < botones.size() - 1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	botones[activo]->aumentar();
	if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
		botones[activo]->accion();
	}

}


void Objetos3::salir(Juego* pJuego) {


	pJuego->popState();


}

void Objetos3::combustible(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Petroleo") && pjuego->getBaul()->getCantidad("Petroleo") >= 1) &&

		(pjuego->getBaul()->findItem("Refinador") && pjuego->getBaul()->getCantidad("Refinador") >= 1)){

		pjuego->getBaul()->insertItem("Combustible", 1);
		pjuego->getBaul()->removeItem("Petroleo", 1);
		pjuego->getBaul()->removeItem("Refinador", 1);

	}

}
void Objetos3::mecanismo(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Engranajes") && pjuego->getBaul()->getCantidad("Engranajes") >= 1) &&

		(pjuego->getBaul()->findItem("Eje") && pjuego->getBaul()->getCantidad("Eje") >= 1) &&
		
		(pjuego->getBaul()->findItem("Fusible") && pjuego->getBaul()->getCantidad("Fusible") >= 1)){

		pjuego->getBaul()->insertItem("Mecanismo", 1);
		pjuego->getBaul()->removeItem("Engranajes", 1);
		pjuego->getBaul()->removeItem("Eje", 1);
		pjuego->getBaul()->removeItem("Fusible", 1);

	}
}
void Objetos3::fibraCarbono(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Carbono") && pjuego->getBaul()->getCantidad("Carbono") >= 1) &&

		(pjuego->getBaul()->findItem("Madera") && pjuego->getBaul()->getCantidad("Madera") >= 1)){//y algo	que dropea el 1er boss...

		pjuego->getBaul()->insertItem("FibraCarbono", 1);
		pjuego->getBaul()->removeItem("Carbono", 1);
		pjuego->getBaul()->removeItem("Madera", 1);

	}
}

void Objetos3::moduloComandos(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Pantalla") && pjuego->getBaul()->getCantidad("Pantalla") >= 1) &&

		(pjuego->getBaul()->findItem("Circuito") && pjuego->getBaul()->getCantidad("Circuito") >= 2)){

		pjuego->getBaul()->insertItem("ModuloComandos", 1);
		pjuego->getBaul()->removeItem("Pantalla", 1);
		pjuego->getBaul()->removeItem("Circuito", 2);

	}

}

void Objetos3::mensaje(Juego* pjuego){

	std::cout << "lo dropea un boss";
}


void Objetos3::receta(std::string obj){
	if (obj == "Mecanismo"){
		animacion.textura = pJuego->getTextura("Engranajes", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Eje", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Fusible", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "Combustible"){
		animacion.textura = pJuego->getTextura("Petroleo", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Petroleo", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Refinador", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "FibraCarbono"){
		animacion.textura = pJuego->getTextura("Carbono", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Madera", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
		/*animacion.textura = pJuego->getTextura("Madera", "idle"); otra cosa del boss
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, animacion.currentRect(), 0.0);*/
	}

	else if (obj == "ModuloComandos"){
		animacion.textura = pJuego->getTextura("Pantalla", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Circuito", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Circuito", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

}