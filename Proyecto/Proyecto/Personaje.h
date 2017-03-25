#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Entidad.h"
class Personaje :
	public Entidad
{
public:
	Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~Personaje();

	void virtual update();
	int getVidas() { return stats.vida; };
	void restaVidas(int numero) { stats.vida -= numero; };
	
	/*Struct de los ATRIBUTOS. En la constructora de cada personaje, hay que inicializar los atributos con los que empieza.*/
	struct atributos {

		//Atributos		//L�mite por arriba						//L�mite por abajo
		int vida;       static const int vidaLim = 10;         static const int vidaMin = 0;
		int vidaMax;	static const int vidaMaxLim = 10;	   static const int vidaMaxMin = 0;
		int da�o;		static const int da�oLim = 20;	       static const int da�oMin = 1;
		int velMov;		static const int velMovLim = 1200;	   static const int velMovMin = 700;
		int velAtq;		static const int velAtqLim = 10;	   static const int velAtqMin = 1;

		//Sobrecarga del operador que controla que no se sobrepase por arriba ni por abajo.
		 struct atributos& operator+=(atributos const &a) {
			 //Controlamos que no se le pueda a�adir mas del l�mite ni quitar menos que el m�nimo.
			 if (vida + a.vida <= vidaLim) vida += a.vida;
			 else  if (vida + a.vida < vidaMin) vida = vidaMin;

			 if (vidaMax + a.vidaMax <= vidaMaxLim) vidaMax += a.vidaMax;
			 else if (vidaMax + a.vidaMax < vidaMaxMin) vidaMax = vidaMaxMin;

			 if (da�o + a.da�o <= da�oLim) da�o += a.da�o;
			 else if (da�o + a.da�o < da�oMin) da�o = da�oMin;

			 if (velMov + a.velMov <= velMovLim) velMov += a.velMov;
			 else  if (velMov + a.velMov < velMovMin) velMov = velMovMin;

			 if (velAtq + a.velAtq <= velAtqLim) velAtq += a.velAtq;
			 else  if (velAtq + a.velAtq < velAtqMin) velAtq = velAtqMin;

			return *this;
		}
	};

	//M�todo que utilizan los objetos para sumar sus stats a los del jugador.
	void applyEffect(atributos &nwEffect) {
		stats += nwEffect;
	}

protected:
	atributos stats;
	//Tal vez no nos haga falta un vector de objetos.
	vector<Objeto*> inventario;
	vector<std::string> dropPool;


};

#endif