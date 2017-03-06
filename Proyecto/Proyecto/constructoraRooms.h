#include "Room.h"
#include "TileInfo.h"
vector<Tile*> RoomDesdeArchivo(string direccion, b2World * world, int& WID, int& HEI) {
	int MAP_T_WIDTH, MAP_T_HEIGHT;
	vector<Tile*> Tiles;
	ifstream map(direccion);
	map >> MAP_T_WIDTH >> MAP_T_HEIGHT;
	int TOT_Tiles = MAP_T_WIDTH*MAP_T_HEIGHT;
	Tiles.reserve(TOT_Tiles);
	int x = 0, y = 0;
	int tipo = -1;
	for (size_t i = 0; i < TOT_Tiles; i++)
	{
	
		map >> tipo;
		if (tipo >= 0 && tipo < 12) {
			Tiles.push_back(new Tile(x, y, tipo, world));
		}
		x += TILE_WIDTH;
		if (x >= TILE_WIDTH*MAP_T_WIDTH) {
			x = 0;
			y += TILE_HEIGHT;
		}
	}
	WID = MAP_T_WIDTH*TILE_WIDTH;
	HEI = MAP_T_HEIGHT*TILE_HEIGHT;
	return Tiles;
}
vector<Tile*> RoomMinima(b2World * world,int& WID, int& HEI, int xIni,int yIni){
	int Ancho = 16;
	int Alto = 12;
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x=xIni, y=yIni;
	int posY=0, posX=0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX==0||posX==Ancho-1)?((posX==0)?SE:SO):PH , world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho-1) && (posY != Alto / 2)) ? ((posX == 0) ? NE : NO) : PH, world));
		else 
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho -1) && !(posY == Alto / 2 || posY == (Alto / 2)-1)) ? ((posX == 0) ? PV : PV) : S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = xIni;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}
	}
	WID = Ancho*TILE_WIDTH;
	HEI = Alto*TILE_HEIGHT;
	cout << WID << " " << HEI;
	return Tiles;
}
vector<Tile*> RoomCustom(b2World * world,int Ancho,int Alto ,int& WID, int& HEI, int xIni, int yIni,Direcciones LocPuert) {
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x = xIni, y = yIni;
	int posY = 0, posX = 0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? SE : SO) : (LocPuert.Norte && (posX == Ancho / 2 || posX == (Ancho / 2) - 1)) ? S1 : PH, world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho - 1) && (posY != Alto / 2)) ? ((posX == 0) ? NE : NO) : (LocPuert.Sur && (posX == Ancho / 2 || posX == (Ancho / 2) - 1)) ? S1 : PH, world));
		else if (LocPuert.Este && (posY == Alto / 2 || posY == Alto / 2 - 1))
			Tiles.push_back(new Tile(x, y, S1, world));
		else if (LocPuert.Oeste && (posY == Alto / 2 || posY == Alto / 2 - 1))
			Tiles.push_back(new Tile(x, y, S1, world));
		else
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho - 1)&& !((LocPuert.Este||LocPuert.Oeste)&&(posY==Alto/2|| posY == (Alto / 2)-1)))? ((posX == 0) ? PV : PV) :S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = xIni;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}
	}
	WID = Ancho*TILE_WIDTH;
	HEI = Alto*TILE_HEIGHT;
	cout << WID << " " << HEI;
	return Tiles;
}
vector<Tile*> Room2x1(b2World * world, int& WID,int& HEI) {
	int Ancho = 16+5;
	int Alto = 12;
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x = 0, y = 0;
	int posY = 0, posX = 0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? SE : SO) : PH, world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? NE : NO) : PH, world));
		else
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho - 1)) ? ((posX == 0) ? PV : PV) : S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = 0;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}

	}
	WID = Ancho*TILE_WIDTH;
	HEI = y;
	return Tiles;
}