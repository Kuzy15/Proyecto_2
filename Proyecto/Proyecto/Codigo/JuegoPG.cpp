#include "JuegoPG.h"


//Constructora que inicializa todos los atributos de la clase Juego.
JuegoPG::JuegoPG(b2World* mundo) : error(false), gameOver(false), exit(false), score(0), world(mundo)
{
	window.alto = 600; //Tama�o de la ventana.
	window.ancho = 800;
	fondoRect.x = 0; //Posici�n y tama�o de la ventana.
	fondoRect.y = 0;
	fondoRect.w = window.ancho;
	fondoRect.h = window.alto;
	mousePos.x = 0;//Posici�n del raton, inicializaci�n trivial.
	mousePos.y = 0;
	//iniciazi�n de SDL
	if (!initSDL()) {
		error = true;
		std::cout << "Ha ocurrido un error con SDL";
	}
	//Esto es el wall de mexico los estados hundidos
	
	
	//A�adimos al vector del nombre de las texturas los nombres de las im�genes. Tienen que tener un orden concreto.
	nombreTexturas.emplace_back("../Material/TOSTADORA.png");
	nombreTexturas.emplace_back("../Material/gato.png");
	nombreTexturas.emplace_back("../Material/wall.png");
	nombreTexturas.emplace_back("../Material/background.jpg");
	
	b2BodyDef tostBodydef;
	tostBodydef.type = b2_dynamicBody;
	tostBodydef.position.Set(50.0f, 50.0f);

	b2Body* tostBody = world->CreateBody(&tostBodydef);

	b2PolygonShape tostBox;
	tostBox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef fDef;
	fDef.shape = &tostBox;
	fDef.density = 1.0f;
	fDef.friction = 1.0f;
	tostBody->CreateFixture(&fDef);
	tostadora = tostBody;
	r.h = 50;
	r.w = 50;

	b2BodyDef wallBodydef;
	wallBodydef.type = b2_staticBody;
	wallBodydef.position.Set(400.0f, 400.0f);

	b2Body* wallBody = world->CreateBody(&wallBodydef);

	b2PolygonShape wallbox;
	wallbox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef wDef;
	wDef.shape = &wallbox;
	wallBody->CreateFixture(&wDef);
	wall= wallBody; 
	recta.h = 50;// tama�o de la imagen
	recta.w = 50;
	


	b2BodyDef gBodydef;
	gBodydef.type = b2_dynamicBody;
	gBodydef.position.Set(150.0f, 100.0f);

	b2Body* gBody = world->CreateBody(&gBodydef);

	b2PolygonShape gBox;
	gBox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef gDef;
	gDef.shape = &gBox;
	gDef.density = 50000.0f;
	gDef.friction = 1.0f;
	gBody->CreateFixture(&gDef);
	gato = gBody;
	r2.h = 100;
	r2.w = 100;

	dcha = izq = up = down = false;

	for (int i = 0; i < 322; i++) { // init them all to false
		KEYS[i] = false;
	}
	
	//Arrancamos las texturas y los objetos.
	initMedia();
	objetos.push_back(tostadora);
	objetos.push_back(gato);
	objetos.push_back(wall);
	run();	
	
}

JuegoPG::~JuegoPG()
{

	//Liberamos los objetos.
	freeMedia();
	
	//Liberamos SDL.
	closeSDL();
	pWindow = nullptr;
	pRenderer = nullptr;
}


//Devolvemos una textura en funci�n del enumerado que nos pasen.
TexturasSDL* JuegoPG::getTextura(Texturas_t t) {

	
	return texturas[t];
	
};
//Devolvemos el puntero al Render que est� como atributo en la clase.
SDL_Renderer* JuegoPG::getRender() const {

	return pRenderer;

};

//Devolvemos la posici�n actual del mouse, que se actualiza en el onClick.
void JuegoPG::getMousePos(int &mpx, int &mpy)const {

	mpx = mousePos.x;
	mpy = mousePos.y;

};
//M�todo que inicializa las texturas.
void JuegoPG::initMedia() {
	//Creamos las texturas y las metemos en el vector de punteros.
	for (int i = 0; i < nombreTexturas.size(); i++) {
		texturas.emplace_back(new TexturasSDL);
		texturas.at(i)->load(pRenderer, nombreTexturas[i]);
	}

};
//M�todo que libera las texturas.
void JuegoPG::freeMedia() {

	for (int i = 0; i < nombreTexturas.size(); i++) {
		delete texturas.at(i);
		texturas.at(i) = nullptr;
	}
};
//M�todo que inicializa SDL
bool JuegoPG::initSDL() {

	bool success = true; //Initialization flag

						 //Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("GLOBOS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.ancho, window.alto, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRenderer == nullptr) {
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}
	return success;
};
//M�todo que libera SDL
void JuegoPG::closeSDL() {

	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;

	SDL_Quit();
};
//M�todo que controla los eventos.
bool JuegoPG::handle_event() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		
		switch (event.type) {

		case SDL_QUIT:
			salir(); 
			break;
		case SDL_KEYDOWN:
			KEYS[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			KEYS[event.key.keysym.sym] = false;
			break;
		default:
			break;
		}
	} 
	return true;
};

void JuegoPG::handleInput() {

	float32 vel = 0.05f;
	int lim = 3;

	b2Vec2 v = tostadora->GetLinearVelocity();
	
	

	if (KEYS[SDLK_a]) { 
		izq = true;
		if (!(v.x < -lim))
			pos.x -= vel;	
	}
	else
		izq = false;

	if (KEYS[SDLK_d]) { 
		if (!(v.x > lim)){
			pos.x += vel;
		}
		dcha = true;
		
	}
	else
		dcha = false;

	if (KEYS[SDLK_w]) { 
		if (!(v.y < -lim))
			pos.y -= vel;
		up = true;
		
	}
	else
		up = false;

	if (KEYS[SDLK_s]) { 
		if (!(v.y > lim))
			pos.y += vel;
		down = true;
		
	}
	else
		down = false;


	if (!dcha && !izq) {
		if (pos.x != 0) {
			if (pos.x > 0)
				pos.x -= vel*0.75f;
			else
				pos.x += vel*0.75f;
		}
	}
	if (!up && !down) {
		if (pos.y != 0) {
			if (pos.y > 0)
				pos.y -= vel*0.75f;
			else
				pos.y += vel*0.75f;
		}
	}
	if (pos.x >= lim || pos.x <= -lim){
		if (pos.x > 0)
			pos.x = lim;
		else 
			pos.x = -lim;
	}
	if (pos.y >= lim || pos.y <= -lim){
		if (pos.y > 0)
			pos.y = lim;
		else
			pos.y = -lim;
	}

}
//M�todo de consulta de la variable de control 'error'.
bool JuegoPG::getError() {

	return error;

};

void JuegoPG::salir() {

		exit = true;
	
}

void JuegoPG::move(char c) {

	
	
}


void JuegoPG::update(){

	b2Vec2 point;
	point.x = 500;
	point.y = 500;
	world->Step(1.0f/60.0f, 6, 2);
	handleInput();
	tostadora->SetLinearVelocity(pos);
	
}

void JuegoPG::draw(){
	
	SDL_RenderClear(pRenderer);
	
	texturas[3]->draw(pRenderer, fondoRect, &fondoRect);
	b2Vec2 posT;

	for (int i = 0; i < objetos.size(); i++){
		r.x = (int)objetos[i]->GetPosition().x;
		r.y = (int)objetos[i]->GetPosition().y;
		texturas[i]->draw(pRenderer, r, nullptr);
		//[i]->GetUserData();
		//MIRAR TAMA�O CON LA CLASE.
	}
	

	SDL_RenderPresent(pRenderer);

}


void JuegoPG::run() {

	if (!error) {
		cout << "PLAY \n";
		lastUpdate = SDL_GetTicks();
		handle_event();
		while (!exit) {
			update();
			lastUpdate = SDL_GetTicks();
			draw();
			handle_event();
		}
		if (exit) cout << "EXIT \n";
		else if (gameOver) {
			cout << "GAME OVER \n";
		}
	}
};

