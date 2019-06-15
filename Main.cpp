#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tablero y Bloques.h"
#include "C Tiempo.h"
#include "C Graficos.h"
#include "C Partida.h"
	
#define FPS 60

int main()
{
	// Carga de recursos
	sf::Texture textTablero;
	textTablero.loadFromFile("Graficos/Tablero.png",sf::IntRect(0,0,210,310));
	sf::Texture textBloque;
	textBloque.loadFromFile("Graficos/Bloque.png",sf::IntRect(0,0,20,20));
	sf::Font font;
	font.loadFromFile("Connection.otf");

	string direccionOST[3] = { "Musica/Katyusha.wav" , "Musica/Farewell of Slavianka.wav" , "Musica/Korobeniki.wav" };
	
	// Clases principales
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(400,400),"Tetris");

	ReguladorTiempo rTiempo = ReguladorTiempo(FPS);
	CGraficos cGraficos = CGraficos(&window,0,&rTiempo,&textTablero,&textBloque,&font);
	ControladorPartida cPartida = ControladorPartida(&cGraficos, &rTiempo, velocidades[0], direccionOST);

	// Comenzar partida
	cPartida.funcionPrincipal();
}