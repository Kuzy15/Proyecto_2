#include "Bala.h"
#include "checkML.h"

Bala::Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry, int lanzador) :Entidad(punteroJuego, spritePar, objectId), lanzador(lanzador)
{

	stopBala = false;
	
	_vel = vel * _coefMov;
	x = dirx;
	y = diry;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->SetUserData(this);
	//b2Vec2 velocidad;
	velocidad.x = _vel*x;
	velocidad.y = _vel*y;
	//Capa de colision.
	if (lanzador == 1){
		fDef.filter.categoryBits = Juego::AT_ENEMIGO;
		fDef.filter.maskBits = Juego::ESCENARIO | Juego::ENEMIGO | Juego::JUGADOR;
	}
	else if (lanzador == 0){
		fDef.filter.categoryBits = Juego::AT_JUGADOR;
		fDef.filter.maskBits = Juego::ENEMIGO | Juego::ESCENARIO;
	}

	body->CreateFixture(&fDef);
	body->SetLinearVelocity(velocidad);
	
}
//Constructor para Balas de Aceite meeeen
Bala::Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry, int lanzador,string sensor) :Entidad(punteroJuego, spritePar, objectId), lanzador(lanzador)
{

	_vel = vel * _coefMov;
	x = dirx;
	y = diry;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->SetUserData(this);
	
	
	velocidad.x = _vel*x;
	velocidad.y = _vel*y;
	//Capa de colision.
	if (lanzador == 1){
		fDef.filter.categoryBits = Juego::AT_ENEMIGO;
		fDef.filter.maskBits = Juego::ESCENARIO | Juego::ENEMIGO | Juego::JUGADOR;
	}
	else if (lanzador == 0){
		fDef.filter.categoryBits = Juego::AT_JUGADOR;
		fDef.filter.maskBits = Juego::ENEMIGO | Juego::ESCENARIO;
	}

	body->CreateFixture(&fDef);
	velocidad.x = velocidad.x;
	velocidad.y = velocidad.y;

	body->SetLinearVelocity(velocidad);

}
Bala::~Bala()
{
	/*delete shape;
	shape = nullptr;*/
}

void Bala::update(){
	if (!stopBala){
		Entidad::update();
	}
}

void Bala::resume(){
	stopBala = false;
	body->SetLinearVelocity(velocidad);
}

void Bala::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	destruido = true;

}

int Bala::getLanzador(){
	return lanzador;
}
