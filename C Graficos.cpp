#include "C Graficos.h"

	// Constructores y destructores
	CGraficos::CGraficos(sf::RenderWindow* window , Tablero* tablero , ReguladorTiempo* rTiempo , sf::Texture* textTablero , sf::Texture* textBloque, sf::Font* font)
	{
		this->window = window;
		this->tablero = tablero;
		this->rTiempo = rTiempo;
		this->textBloque = textBloque;
		this->textTablero = textTablero;
		this->font = font;

		this->spriteTablero = sf::Sprite(*this->textTablero);
		this->spriteBloque = sf::Sprite(*this->textBloque);
	}
	CGraficos::~CGraficos()
	{
	}
	
	// Getters y Setters
	void CGraficos::setTablero(Tablero* tablero)
	{
		this->tablero = tablero;
	}

	sf::RenderWindow* CGraficos::getWindow()
	{
		return this->window;
	}

	// Funciones
	void CGraficos::imprimirTablero()
	{
		this->window->draw(this->spriteTablero);
	}
	void CGraficos::imprimirBloques()
	{
		for ( int i = 0 ; i < 10 ; i++ )
		{
			for ( int y = 0 ; y < 15 ; y++ )
			{
				if ( tablero->casillas[i][y] )
				{
					this->spriteBloque.setPosition((5+i*20),(5+y*20));
					this->window->draw(spriteBloque);
				}
			}
		}
	}
	void CGraficos::imprimirBarraPartida()
	{
		char arrayPuntuacion[15] = { 0 };
		itoa(this->tablero->puntuacion,arrayPuntuacion,10);

		sf::Text texto1("Siguiente pieza:",*font,20);
		sf::Text texto2("Puntuacion:",*font,20);
		sf::Text texto3(arrayPuntuacion,*font,20);
		sf::Text texto4("Controles:\nA S D\nMover figura\nW\nGirar figura\nP\nPausar partida",*font,20);

		texto1.setPosition(220,10);
		texto2.setPosition(220,110);
		texto3.setPosition(220,130);
		texto4.setPosition(220,210);

		texto1.setColor(sf::Color::White);
		texto2.setColor(sf::Color::White);
		texto3.setColor(sf::Color::White);
		texto4.setColor(sf::Color::White);

		for ( int i = 0 ; i < 4 ; i++ )
		{
			for ( int y = 0 ; y < 2 ; y++ )
			{
				if ( tablero->figuraProxima->bloques[i][y] )
				{
					this->spriteBloque.setPosition((220+i*20),(40+y*20));
					this->window->draw(spriteBloque);
				}
			}
		}

		this->window->draw(texto1);
		this->window->draw(texto2);
		this->window->draw(texto3);
		this->window->draw(texto4);
	}

	void CGraficos::imprimirPantalla()
	{
		if ( this->tablero )
		{
			this->imprimirTablero();
			this->imprimirBloques();
			this->imprimirBarraPartida();
			this->window->display();
			this->window->clear();
		}
	}

	void CGraficos::imprimirMenuPausa()
	{
		this->imprimirTablero();
		this->imprimirBloques();
		this->imprimirBarraPartida();

		sf::RectangleShape rectPausa(sf::Vector2f(200,100));
		rectPausa.setOutlineThickness(10);
		rectPausa.setFillColor(sf::Color::Black);
		rectPausa.setOutlineColor(sf::Color::White);
		rectPausa.setPosition(100,150);

		sf::Text texto("Menu de pausa.\nPulse P de nuevo\npara continuar la\npartida.",*font,15);
		texto.setPosition(110,160);

		this->window->draw(rectPausa);
		this->window->draw(texto);

		this->window->display();
		this->window->clear();
	}

	void CGraficos::imprimirMenuDerrota()
	{
		this->imprimirTablero();
		this->imprimirBloques();
		this->imprimirBarraPartida();

		sf::RectangleShape rectPausa(sf::Vector2f(200,100));
		rectPausa.setOutlineThickness(10);
		rectPausa.setFillColor(sf::Color::Black);
		rectPausa.setOutlineColor(sf::Color::White);
		rectPausa.setPosition(100,200);

		sf::Text texto("Has perdido!\nPulsa P para continuar.",*font,15);
		texto.setPosition(110,210);

		this->window->draw(rectPausa);
		this->window->draw(texto);

		this->window->display();
		this->window->clear();
	}