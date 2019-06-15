#ifndef C_GRAFICOS_H
#define C_GRAFICOS_H

#include <stdlib.h>
#include "SFML\Graphics.hpp"
#include "C Tiempo.h"
#include "Tablero y Bloques.h"

class CGraficos
{
private:
	sf::RenderWindow* window;
	Tablero* tablero;
	ReguladorTiempo* rTiempo;
	sf::Texture* textTablero;
	sf::Texture* textBloque;
	sf::Sprite spriteTablero;
	sf::Sprite spriteBloque;
	sf::Font* font;
public:
	// Constructores y destructores
	CGraficos(sf::RenderWindow* window , Tablero* tablero , ReguladorTiempo* rTiempo , sf::Texture* textTablero , sf::Texture* textBloque, sf::Font* font);
	~CGraficos();

	// Getters y Setters
	void setTablero(Tablero* tablero);
	sf::RenderWindow* getWindow();

	// Funciones
	void imprimirTablero();
	void imprimirBloques();
	void imprimirBarraPartida();

	void imprimirPantalla();

	void imprimirMenuPausa();
	void imprimirMenuDerrota();
};

#endif