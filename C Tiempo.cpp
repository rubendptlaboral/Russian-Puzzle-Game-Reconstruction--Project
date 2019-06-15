#include "C Tiempo.h"

// R TIEMPO
	// Constructor
	ReguladorTiempo::ReguladorTiempo(int fps)	{
		this->fps = fps;
		this->frames = 0;
		this->MPF = msPorFrame();
		this->msSobrantes = 0;
	}

	// Getters
	int ReguladorTiempo::getFrames() {
		return frames;
	}
	sf::Clock* ReguladorTiempo::getRelojP()	{
		return &(this->reloj);
	}

	// Mantenimiento
	void ReguladorTiempo::iniciarReloj() {
		this->getCantidadNuevosFrames(); // Conservar ms sobrantes
		reloj.restart();
		this->frames = 0;
	}
	float ReguladorTiempo::msPorFrame() {
		float ms = 1000.0f / fps;
		return ms;
	}

	// Métodos principales
	int ReguladorTiempo::solicitarComenzarCiclo()
	{
		// La función comprueba si ha transcurrido tiempo suficiente para iniciar un nuevo frame.
		// Si es posible, devuelve 1; de lo contrario, devuelve 0
		int comenzarCiclo = 0;
		tiempo = reloj.getElapsedTime();
		if ( tiempo.asMilliseconds() > MPF )
		{
			comenzarCiclo++;
			reloj.restart();
			frames++;
			//cout << frames << endl;
		}
		return comenzarCiclo;
	}
	int ReguladorTiempo::getCantidadNuevosFrames()
	{
		// La función comprueba si ha transcurrido tiempo suficiente para iniciar un nuevo frame.
		// De no ser así, devuelve 0. En caso contrario, devuelve la cantidad de frames que deben actualizarse.
		// La implementación de esta función en el ciclo permitirá que la lógica interna se actualice
		// a tiempo real aunque la cantidad de frames por segundo deba disminuirse.

		tiempo = reloj.getElapsedTime();
		int nuevosFrames = int(( (tiempo.asMilliseconds() + msSobrantes) - frames * MPF ) / MPF) ;
		if ( nuevosFrames )
		{
			if ( int(MPF) )
				msSobrantes = int( (tiempo.asMilliseconds() + msSobrantes) - frames * MPF ) % int(MPF) ;
			frames += nuevosFrames;
		}
		return nuevosFrames;
	}

	// Debug
	void ReguladorTiempo::imprimirTiempoTranscurrido() {
		tiempo = reloj.getElapsedTime();
		cout << tiempo.asMilliseconds() << endl;
	}