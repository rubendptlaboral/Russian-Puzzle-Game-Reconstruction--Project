#include "C Partida.h"

	// Constructores y Destructores
	ControladorPartida::ControladorPartida(CGraficos* cGraficos, ReguladorTiempo* rTiempo, int velocidad, string* direccionesOST)
	{
		this->cGraficos = cGraficos;
		this->rTiempo = rTiempo;
		this->velocidad = velocidad;
		this->direccionesOST[0] = &direccionesOST[0];
		this->direccionesOST[1] = &direccionesOST[1];
		this->direccionesOST[2] = &direccionesOST[2];

		this->musica = new sf::Music();
		this->musica->openFromFile(*this->direccionesOST[0]);
		this->musica->setLoop(1);
		this->musica->play();

		this->tablero = Tablero();
	}
	ControladorPartida::~ControladorPartida()
	{
	}

	// Funciones
	int ControladorPartida::leerInput()
	{
		int flagInput = 0;

		sf::RenderWindow* window = this->cGraficos->getWindow();
		sf::Event Event;
		while(window->pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				window->close();
				flagInput = -1; // Terminar programa
			}

			if (Event.type == sf::Event::KeyPressed)
			{
				if(Event.key.code == sf::Keyboard::A)
				{
					this->tablero.moverFiguraActual(Izquierda);
					flagInput++;
				}
				if(Event.key.code == sf::Keyboard::S)
				{
					this->tablero.moverFiguraActual(Abajo);
					flagInput++;
				}
				if(Event.key.code == sf::Keyboard::D)
				{
					this->tablero.moverFiguraActual(Derecha);
					flagInput++;
				}
				if(Event.key.code == sf::Keyboard::W)
				{
					this->tablero.moverFiguraActual(Girar);
					flagInput++;
				}
				if(Event.key.code == sf::Keyboard::P)
				{
					if (this->menuPausa())
						flagInput = -1;
				}
			}
		}
		return flagInput;
	}
	void ControladorPartida::actualizarDificultad()
	{
		if ( this->tablero.puntuacion > 45000 )
			this->velocidad = velocidades[9];
		else if ( this->tablero.puntuacion > 36000 )
			this->velocidad = velocidades[8];
		else if ( this->tablero.puntuacion > 28000 )
			this->velocidad = velocidades[7];
		else if ( this->tablero.puntuacion > 21000 )
			this->velocidad = velocidades[6];
		else if ( this->tablero.puntuacion > 15000 )
			this->velocidad = velocidades[5];
		else if ( this->tablero.puntuacion > 10000 )
		{
			if ( this->velocidad > velocidades[4] )
			{
				this->musica->stop();
				delete(this->musica);
				this->musica = new sf::Music;
				this->musica->openFromFile(*this->direccionesOST[2]);
				this->musica->setLoop(1);
				this->musica->play();
			}
			this->velocidad = velocidades[4];
		}
		else if ( this->tablero.puntuacion > 6000 )
			this->velocidad = velocidades[3];
		else if ( this->tablero.puntuacion > 3000 )
		{
			if ( this->velocidad > velocidades[2] )
			{
				this->musica->stop();
				delete(this->musica);
				this->musica = new sf::Music;
				this->musica->openFromFile(*this->direccionesOST[1]);
				this->musica->setLoop(1);
				this->musica->play();
			}
			this->velocidad = velocidades[2];
		}
		else if ( this->tablero.puntuacion > 1000 )
			this->velocidad = velocidades[1];

	}
	int ControladorPartida::menuPausa()
	{
		int flagContinuar = 0;
		int flagCerrar = 0;

		this->musica->pause();
		this->cGraficos->imprimirMenuPausa();

		sf::RenderWindow* window = this->cGraficos->getWindow();
		sf::Event Event;
		while ( flagContinuar == 0 )
		{
			while(window->pollEvent(Event))
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if(Event.key.code == sf::Keyboard::P)
					{
						flagContinuar++;
					}
				}
			}
		}

		this->musica->play();
		this->rTiempo->iniciarReloj();
		return flagCerrar;
	}
	void ControladorPartida::menuDerrota()
	{
		int flagContinuar = 0;

		this->tablero.nuevaFigura();

		this->cGraficos->imprimirMenuDerrota(); // TODO IMPRIMIR MENU DERROTA

		sf::RenderWindow* window = this->cGraficos->getWindow();
		sf::Event Event;

		while ( flagContinuar == 0 )
		{
			while(window->pollEvent(Event))
			{
				if(Event.type == sf::Event::Closed)
				{
					window->close();
					flagContinuar++;
				}

				if (Event.type == sf::Event::KeyPressed)
				{
					if(Event.key.code == sf::Keyboard::P)
					{
						flagContinuar++;
					}
				}
			}
		}
	}

	// Funcion principal
	void ControladorPartida::funcionPrincipal()
	{
		int flagTerminarPartida = 0;
		int framesSiguienteMovimiento = 0;
		int nuevosFrames = 0;

		int p;
		int puntuacionGanada = 0;

		this->tablero.nuevaFigura();
		rTiempo->iniciarReloj();
		this->cGraficos->setTablero(&tablero);

		while ( flagTerminarPartida != -1 )
		{
			flagTerminarPartida = this->leerInput();
			cGraficos->imprimirPantalla();
			nuevosFrames = rTiempo->getCantidadNuevosFrames();
			framesSiguienteMovimiento += nuevosFrames;
			
			if ( framesSiguienteMovimiento >= this->velocidad )
			{
				for ( int i = 0 ; i < framesSiguienteMovimiento ; i++ )
				{
					framesSiguienteMovimiento -= velocidad;
					if ( this->tablero.moverFiguraActual(Abajo) ) // La figura colisiona al moverse una casilla hacia abajo.
					{
						p = this->tablero.limpiarLineas();
						if (this->tablero.comprobarColision(this->tablero.figuraProxima)) // Comprobar derrota
						{
							this->menuDerrota();
							flagTerminarPartida = -1;
						}
						this->tablero.nuevaFigura();
						puntuacionGanada = p*p*100;
						this->tablero.puntuacion += puntuacionGanada;
						actualizarDificultad();
					}
					
				}
			}
		}
	}