#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

#ifndef C_REGULADOR_TIEMPO
#define C_REGULADOR_TIEMPO

class ReguladorTiempo
{
	// Arfefacto que permite regular el ritmo al que se producen nuevos frames
private:
	sf::Time tiempo;
	sf::Clock reloj;
	int fps;
	float MPF; // Milliseconds Por Frame
	int frames;
	int msSobrantes;
public:
	// Constructor
	ReguladorTiempo(int fps);

	// Getters
	int getFrames();
	sf::Clock* getRelojP();

	// Mantenimiento
	void iniciarReloj();
	float msPorFrame();

	// Métodos principales
	int solicitarComenzarCiclo();
	int getCantidadNuevosFrames();

	// Debug
	void imprimirTiempoTranscurrido();
};

#endif