#ifndef TABLERO_BLOQUES_H
#define TABLERO_BLOQUES_H

#include "SFML\Graphics.hpp"

enum movimientos{Arriba, Derecha, Abajo, Izquierda, Girar};

class Figura
{
private:
	sf::Vector2i posicion;
	sf::Vector2i dimensiones;
public:
	int bloques[4][4];
public:
	Figura();
	Figura(int modelo);
	~Figura();

	void setPosicion(sf::Vector2i posicion);
	sf::Vector2i* getPosicion();
	sf::Vector2i* getDimensiones();

	Figura girar();
};

class Tablero
{
public:
	int casillas[10][15];
public:
	Figura* figuraActual;
	Figura* figuraProxima;

	int puntuacion;
public:
	Tablero();
	~Tablero();

	Figura* nuevaFigura(); // Borra la figura actual, saca la figura proxima, y genera una nueva figura proxima. Devuelve un puntero a la nueva figura actual.
	void borrarOAnadirBloquesFigura(Figura* figura, int opcion); // 0 para borrar, 1 para añadir
	int comprobarLimitesTablero(Figura* figura); // Comprueba que la figura se encuentre dentro de los límites del tablero.
	int comprobarColision(Figura* figura); // Devuelve 1 si uno de los bloques de la figura colisiona con un bloque del tablero.
	int moverFiguraActual(int movimientos); // Intenta mover la figura actual según las instrucciones. Devuelve 1 si el movimiento es ilegal.
	int limpiarLineas();
};

#endif