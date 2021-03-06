#include "Sierra.h"


Sierra::Sierra(Juego* punteroJuego, int x, int y, int dir) : Enemigo(punteroJuego, {x,y,128,81}, "Sierra", 1000)
{
	stats.da�o = 20;
	stats.velMov = 4.2;
	direccion = dir;
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idle");
	col = false;

	fDef.density = 2500.0f;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::ESCENARIO | Juego::JUGADOR |  Juego::ESCENARIO_NOCOL;
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->CreateFixture(&fDef);
	isKillable = false;

	
}


Sierra::~Sierra()
{
}


void Sierra::move(){
	if (direccion == 0){

		b2Vec2 velFloat;
		velFloat.x = stats.velMov;
		velFloat.y = 0;
		if (col){
			stats.velMov = -stats.velMov;
			col = false;
		}
		body->SetLinearVelocity(velFloat);
	}

	else 
	{
		b2Vec2 velFloat;
		velFloat.x = 0;
		velFloat.y = stats.velMov;
		if (col){
			stats.velMov = -stats.velMov;
			col = false;
		}
		body->SetLinearVelocity(velFloat);
	}
}


void Sierra::update(){
	//Cambiar a metodo animaci�n
	currentAnim->ActualizarFrame();
	Enemigo::update();
	
}

void Sierra::comportamiento(){
	move();
}

void Sierra::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){
	if (b2 != nullptr){
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO ||
			b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO_NOCOL)
			col = true;
	}
}


void Sierra::activate(){
	destruido = false;
	body->SetActive(true);
}


void Sierra::deactivate(){
	if (this != nullptr){
		destruido = true;
		body->SetActive(false);
	}
}


void Sierra::setPos(float x, float y){
	//spamear en la posicio del boss
	body->SetTransform(b2Vec2{ x, y}, 0);
}