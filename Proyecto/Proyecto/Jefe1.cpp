#include "Jefe1.h"
#include "BalaAceite.h"

#include "BalaEnemiga.h"
#include "BalaAmiga.h"
#include "ObjetoClave.h"
#include "ObjetoHistorico.h"


Jefe1::Jefe1(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x, y, 192, 128}, "carstroller", 1000)// pone bomba pero est� claro que no
{
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	estado = Estados::Idle;
	fase = Fases::Fase1;
	contador = 0;// Contador de la en que parte d ela fase te encuentras
	stats.da�o = 10;
	stats.vida = 300;
	stats.velMov = 0;
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idlo");
	body->SetType(b2_staticBody);
}


Jefe1::~Jefe1()
{
	SDL_RemoveTimer(temp);
}


void Jefe1::comportamiento(){
	currentAnim->ActualizarFrame();
	if (!destruido){
		switch (estado)
		{
		case Estados::Idle:
			Idle();
			break;
		case Estados::Ataque1:
			Ataque1();
			break;
		case Estados::Ataque2:
			Ataque2();
			break;
		case Estados::Ataque3:
			Ataque3();
			break;
		case Estados::Ataque4:
			Ataque4();
			break;
		}
	}


}

void Jefe1::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (contactObject != nullptr){
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){

			stats.vida -= static_cast<BalaEnemiga*>(contactObject)->getDanyo();
			//pJuego->reproducirEfecto("scream");
			if (stats.vida <= 150)fase = Fases::Fase2;
			
			if (stats.vida <= 0) muerte();
		}
	}
}


void Jefe1::move(){
	contador++;
	if (contador%=2==0)
		currentAnim->ActualizarFrame();
}
uint32 changeStateCb(Uint32 intervalo, void * param){
	static_cast<Jefe1*>(param)->changeState();
	return 0;
}

void Jefe1::changeState(){// El metodo no es el m�s bonito lo s�
	empezado = false;
	Estados viejo = estado;
	if (estado == Estados::Idle ){
		
		int rdm = rand() % 2;
		if(rdm == 0)estado = Estados::Ataque1;
		if (rdm == 1)
		{
			if(fase == Fases::Fase1)
				estado = Estados::Ataque2;
			else if (fase == Fases::Fase2){
				int rdm2 = rand() % 2;
				if (rdm2 == 0)
					estado = Estados::Ataque2;
				else
					estado = Estados::Ataque3;
			
			}
		}
	
	}
	else estado = Estados::Idle;
	if (estado != viejo){
		currentAnim->restart();
		switch (estado)
		{
		case  Estados::Idle:
			currentAnim = animaciones.at("idlo");
			break;
		case  Estados::Ataque1:
			currentAnim = animaciones.at("atqu");
			break;
		case  Estados::Ataque2:
			currentAnim = animaciones.at("aceite");
			break;
		case  Estados::Ataque3:
			currentAnim = animaciones.at("aceite");
			break;
		case  Estados::Ataque4:
			break;
		default:
			currentAnim = animaciones.at("idlo");
			break;
		}


	}
}

void Jefe1::Idle(){
	if (!empezado){
		empezado = true;
		Uint32 random = (rand() % 2000) + 1000;
	
		temp = SDL_AddTimer(random, changeStateCb, this);
		//timers
		//El timer que se activa mas tarde es el changestate
	}
}

void Jefe1::Ataque1(){
	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(250, changeStateCb, this);
	
		
		//disparaAceite();
		
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, -0.8, 0.3, 15);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 0, 1, 15);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 0.7, 0.8, 15);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 1.5, 0.4, 15);
		


	}
	//timers
	//El timer que se activa mas tarde es el changestate
}


void Jefe1::Ataque2(){
	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(300u, changeStateCb, this);
		float randomx = (rand() % 200) + -100; randomx /= 100;
		float randomy = (rand() % 100); randomy /= 100;
		stats.da�o = 20;
		disparo("BalaN", SDL_Rect{ getX(), getY() + 200, 60, 60 }, randomx, randomy, 20);
		stats.da�o = 10;

	}
}

void Jefe1::Ataque3(){

	


	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(300u, changeStateCb, this);
		/*float randomx = (rand() % 200) + -100; randomx /= 100;
		float randomy = (rand() % 100); randomy /= 100;*/

		jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
		jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();

		b2Vec2 velFloat;
		velFloat.x = 0.0f;
		velFloat.y = 0.0f;

		b2Vec2 posJug = b2Vec2(jugx / PPM, jugy / PPM);

		b2Vec2 vecDir = posJug - pos;

		b2Vec2 vUnitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));


		//disparo("Bala", SDL_Rect{ getX(), getY() + 200, 24, 24 }, randomx, randomy, 10);
		disparaAceite(vUnitario.x, vUnitario.y);
	}
}

void Jefe1::Ataque4(){
	if (!empezado){
		empezado = true;

		//timers
		//El timer que se activa mas tarde es el changestate
	}
}

void Jefe1::disparo(string tipo,SDL_Rect posicion, float dirx, float diry,float velocidad){
	//dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, tipo, velocidad, dirx, diry));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, tipo, velocidad, dirx, diry, stats.da�o));
}
void Jefe1::disparaAceite(float dirx,float diry){
	b2Vec2 objetivo;
	
	SDL_Rect kek{ pos.x * PPM, pos.y * PPM + 200, 24, 24 };

	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaAceite(pJuego, kek, dirx*20.0f, diry*20.0f));
}

void Jefe1::dropItems() {
	if (pJuego->getNumTarjetas() < 4)
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new ObjetoClave(pJuego, { sprite->x,sprite->y,64,64 }));

	int x; int y;
	int pos = rand() % 2;
	if (pos == 0) pos = -1;
	x = rand() % 10 * pos;
	y = rand() % 10 * (pos * -1);
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new ObjetoHistorico(pJuego, { sprite->x + x,sprite->y + y,64,64 }, "Eje", 1));

}
