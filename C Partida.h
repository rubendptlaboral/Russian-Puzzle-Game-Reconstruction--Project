#ifndef C_PARTIDA_H
#define C_PARTIDA_H

#include "SFML\Audio.hpp"
#include "Tablero y Bloques.h"
#include "C Graficos.h"
#include "C Tiempo.h"

// int velocidades[10] = { 60, 54, 48, 42, 36, 30, 24, 18, 12, 6 };
const int velocidades[10] = { 60, 54, 48, 42, 36, 30, 24, 18, 12, 6 };

class ControladorPartida
{
private:
	CGraficos* cGraficos;
	ReguladorTiempo* rTiempo;
	Tablero tablero;

	string* direccionesOST[3];
	sf::Music* musica;

	int velocidad;
public:
	// Constructores y Destructores
	ControladorPartida(CGraficos* cGraficos, ReguladorTiempo* rTiempo, int velocidad, string* direccionesOST);
	~ControladorPartida();

	// Funciones
	int leerInput();
	void actualizarDificultad();
	int menuPausa();
	void menuDerrota();

	// Funcion principal
	void funcionPrincipal();
};

#endif