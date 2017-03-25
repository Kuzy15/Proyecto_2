#include "Helice.h"
#include "ZonaAccion.h"


Helice::Helice(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, {x,y,128,128}, "Sierra", 500)
{

	stats.da�o = 1;
	stats.velAtq = 0;
	stats.velMov = 4;
	stats.vida = 3;

	rng = rand() % 2;

	b2Filter filter;
	filter = body->GetFixtureList()->GetFilterData();

	filter.categoryBits = Juego::ENEMIGO;
	filter.maskBits = Juego::JUGADOR | Juego::AT_JUGADOR;

	body->GetFixtureList()->SetFilterData(filter);
}
void Helice::onColisionEnter(Objeto* contactObject) {
	

	if (contactObject != nullptr) {
		if (dynamic_cast<Bala*>(contactObject)) {
			stats.vida--;
			if (stats.vida <= 0) Enemigo::onColisionEnter(contactObject);
		}
	}
}


Helice::~Helice()
{
}


void Helice::move(){

	jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();

	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;

	b2Vec2 posJug = b2Vec2(jugx, jugy);

	b2Vec2 vecDir = posJug - pos;

	b2Vec2 vUnitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

	velFloat.x = vUnitario.x*stats.velMov;
	velFloat.y = vUnitario.y*stats.velMov;

	body->SetLinearVelocity(velFloat);

}

void Helice::disparo(){




	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;

	b2Vec2 posJug = b2Vec2(x, y);
	//Vector para la diferencia entre el vect del jugador y el vect del enemigoPerseguidor
	b2Vec2 vecDir = posJug - pos;

	//Calculamos el vector unitario del vector de direccion.
	b2Vec2 unitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

	velFloat.x = unitario.x;
	velFloat.y = unitario.y;
	SDL_Rect posicion;
	posicion.x = pos.x + sprite->w / 2;
	posicion.y = pos.y + sprite->h / 5;
	posicion.w = 30;
	posicion.h = 30;

	posicion.x += velFloat.x * 70;
	posicion.y += velFloat.y * 70;
	Uint32 lastUpdate = SDL_GetTicks();
	//	cout << contador;
	if (lastUpdate - contador > cadencia) {
		//contador++;
		contador = SDL_GetTicks();
		//cout << " Velx " << velFloat.x << " Vely  " << velFloat.y;
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, "BallTBala", 80.0f, velFloat.x, velFloat.y, 1));
	}

}


void Helice::update(){

	if (!destruido){
		Entidad::update();

		if (distancia()){

			if (rng == 0){
				disparo();
				stop();
			}
			else
				move();
		}
		else
			rng = rand() % 2;
	}

}