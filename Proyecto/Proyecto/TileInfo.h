#ifndef TILEINFO_H_
#define TILEINFO_H_

const int TILE_WIDTH = 128, TILE_HEIGHT = 128;
const int TOTAL_TILES = 24;
enum TiposTile
{
	S1 = 0, S2 = 1, S3 = 2, S4 = 3,
	S5 = 4, S6 = 5, S7 = 6, S8 = 7,
	S9 = 8, S10 = 9, S11 = 10, S12 = 11,
	PO = 12, PN=13, PS = 14, PE = 15,
	ENO = 16, ENE = 17, ESE = 18, ESO = 19,
	INO = 20, INE = 21, ISO = 22, ISE = 23,
};
struct Puerta{
	enum Direcciones
	{
		Norte, Este, Sur, Oeste, Sinsitio
	}DirPuerta;
	SDL_Rect posicion;
	SDL_Rect zonaPuerta;
};
#endif