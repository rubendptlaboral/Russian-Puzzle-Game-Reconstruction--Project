#include "Tablero y Bloques.h"
#include <time.h>
#include <stdlib.h>

// Clase Figura
	// Constructores y destructores
	Figura::Figura()
	{
		this->posicion = sf::Vector2i(0,0);
		for ( int i = 0 ; i < 4 ; i++ )
			for ( int j = 0 ; j < 4 ; j++ )
				this->bloques[i][j] = 0;
	}
	Figura::Figura(int modelo)
	{
		this->posicion = sf::Vector2i(0,0);
		for ( int i = 0 ; i < 4 ; i++ )
			for ( int j = 0 ; j < 4 ; j++ )
				this->bloques[i][j] = 0;
		switch(modelo)
		{
		case 0:
			this->dimensiones = sf::Vector2i(4,1);
			this->bloques[0][0] = 1;
			this->bloques[1][0] = 1;
			this->bloques[2][0] = 1;
			this->bloques[3][0] = 1;
			break;
		case 1:
			this->dimensiones = sf::Vector2i(3,2);
			this->bloques[0][0] = 1;
			this->bloques[0][1] = 1;
			this->bloques[1][1] = 1;
			this->bloques[2][1] = 1;
			break;
		case 2:
			this->dimensiones = sf::Vector2i(3,2);
			this->bloques[2][0] = 1;
			this->bloques[2][1] = 1;
			this->bloques[1][1] = 1;
			this->bloques[0][1] = 1;
			break;
		case 3:
			this->dimensiones = sf::Vector2i(2,2);
			this->bloques[0][0] = 1;
			this->bloques[0][1] = 1;
			this->bloques[1][1] = 1;
			this->bloques[1][0] = 1;
			break;
		case 4:
			this->dimensiones = sf::Vector2i(3,2);
			this->bloques[1][0] = 1;
			this->bloques[2][0] = 1;
			this->bloques[0][1] = 1;
			this->bloques[1][1] = 1;
			break;
		case 5:
			this->dimensiones = sf::Vector2i(3,2);
			this->bloques[1][0] = 1;
			this->bloques[0][1] = 1;
			this->bloques[1][1] = 1;
			this->bloques[2][1] = 1;
			break;
		case 6:
			this->dimensiones = sf::Vector2i(3,2);
			this->bloques[0][0] = 1;
			this->bloques[1][0] = 1;
			this->bloques[1][1] = 1;
			this->bloques[2][1] = 1;
			break;
		}
	}
	Figura::~Figura()
	{
	}

	// Getters y Setters
	void Figura::setPosicion(sf::Vector2i posicion)
	{
		this->posicion = posicion;
	}
	sf::Vector2i* Figura::getPosicion()
	{
		return &(this->posicion);
	}
	sf::Vector2i* Figura::getDimensiones()
	{
		return &(this->dimensiones);
	}

	// Otras funciones
	Figura Figura::girar()
	{
		Figura a = Figura();

		a.posicion = this->posicion;
		a.dimensiones.x = this->dimensiones.y;
		a.dimensiones.y = this->dimensiones.x;

		int i2 , j2;
		int i1 = 0;
		int j1 = this->dimensiones.y - 1;

		for ( i2 = 0 ; i2 < a.dimensiones.x ; i2++ )
		{
			i1 = 0;
			for ( j2 = 0 ; j2 < a.dimensiones.y ; j2++ )
			{
				a.bloques[i2][j2] = this->bloques[i1][j1];
				i1++;
			}
			j1--;
		}

		return a;
	}

// Clase Tablero
	// Constructores y destructores
	Tablero::Tablero()
	{
		srand(int(time(NULL)));

		for ( int i = 0 ; i < 10 ; i++ )
			for ( int j = 0 ; j < 15 ; j++ )
				this->casillas[i][j] = 0;

		this->figuraActual = 0;
		this->figuraProxima = new Figura(rand()%7);
		this->figuraProxima->setPosicion(sf::Vector2i(3,0));
		if ( this->figuraProxima->getDimensiones()->x == 2 )
			this->figuraProxima->setPosicion(sf::Vector2i(4,0));

		this->puntuacion = 0;
	}
	Tablero::~Tablero()
	{
	}

	// Funciones
	Figura* Tablero::nuevaFigura()
	{
		if ( this->figuraActual != NULL )
			delete this->figuraActual;

		this->figuraActual = figuraProxima;
		this->figuraProxima = new Figura(rand()%7);
		this->figuraProxima->setPosicion(sf::Vector2i(3,0));
		if ( this->figuraProxima->getDimensiones()->x == 2 )
			this->figuraProxima->setPosicion(sf::Vector2i(4,0));

		this->borrarOAnadirBloquesFigura(this->figuraActual, 1);

		return this->figuraActual;
	}
	void Tablero::borrarOAnadirBloquesFigura(Figura* figura, int opcion)
	{
		for ( int i = 0 ; i < figura->getDimensiones()->x ; i++ )
		{
			for ( int j = 0 ; j < figura->getDimensiones()->y ; j++ )
			{
				if ( figura->bloques[i][j] )
				{
					this->casillas[i+figuraActual->getPosicion()->x][j+figuraActual->getPosicion()->y] = opcion;
				}
			}
		}
	}
	int Tablero::comprobarLimitesTablero(Figura* figura)
	{
		int flagPosicionCorrecta = 1;

		if (figura->getPosicion()->x < 0)
			flagPosicionCorrecta = 0;
		else if ((figura->getPosicion()->x + figura->getDimensiones()->x - 1) >= 10)
			flagPosicionCorrecta = 0;
		else if (figura->getPosicion()->y < 0)
			flagPosicionCorrecta = 0;
		else if ((figura->getPosicion()->y + figura->getDimensiones()->y - 1) >= 15)
			flagPosicionCorrecta = 0;

		return flagPosicionCorrecta;
	}
	int Tablero::comprobarColision(Figura* figura)
	{
		int flagColision = 0;
		if ( figura != NULL)
			for ( int i = 0 ; i < figura->getDimensiones()->x ; i++ )
			{
				for ( int j = 0 ; j < figura->getDimensiones()->y ; j++ )
				{
					sf::Vector2i cTablero(i+figura->getPosicion()->x,j+figura->getPosicion()->y);
					if ( figura->bloques[i][j] == 1 && this->casillas[cTablero.x][cTablero.y] == 1 )
					{
						flagColision = 1;
						i = 20;
						j = 20;
					}
				}
			}
		return flagColision;
	}
	int Tablero::moverFiguraActual(int movimientos)
	{
		int flagMovimientoIlegal = 1;
		int i , j;

		if ( this->figuraActual )
		{
			this->borrarOAnadirBloquesFigura(this->figuraActual,0);

			// Crear figura teórica para validar el movimiento.
			Figura nuevaFigura = *this->figuraActual;
			switch ( movimientos )
			{
			case 0:
				break;
			case 1:
				nuevaFigura.setPosicion(sf::Vector2i(nuevaFigura.getPosicion()->x+1,nuevaFigura.getPosicion()->y));
				break;
			case 2:
				nuevaFigura.setPosicion(sf::Vector2i(nuevaFigura.getPosicion()->x,nuevaFigura.getPosicion()->y+1));
				break;
			case 3:
				nuevaFigura.setPosicion(sf::Vector2i(nuevaFigura.getPosicion()->x-1,nuevaFigura.getPosicion()->y));
				break;
			case 4:
				nuevaFigura = nuevaFigura.girar();
				break;
			}
			// Comprobar si el movimiento es legal.
			if ( !(this->comprobarColision(&nuevaFigura)) && this->comprobarLimitesTablero(&nuevaFigura) )
				flagMovimientoIlegal = 0;
			// Mover bloques
			if ( !flagMovimientoIlegal)
			{
				*(this->figuraActual) = nuevaFigura;
			}

			this->borrarOAnadirBloquesFigura(this->figuraActual,1);
		}

		return flagMovimientoIlegal;
	}
	int Tablero::limpiarLineas()
	{
		int lineasALimpiar = 0;
		int posicionLineasLimpiadas[4] = { -1 , -1 , -1 , -1 };
		int bloquesLineaActual = 0;

		int lineasLimpiadas = 0;

		int i , j;

		// Comprobar lineas llenas
		for ( j = 0 ; j < 15 ; j++ )
		{
			bloquesLineaActual = 0;
			for ( i = 0 ; i < 10 ; i++ )
			{
				if (this->casillas[i][j])
					bloquesLineaActual++;
			}
			if ( bloquesLineaActual == 10 )
			{
				lineasALimpiar++;
				posicionLineasLimpiadas[lineasALimpiar-1] = j;
			}
		}

		// Limpiar lineas llenas
			// k = Línea vacía actual
			// l = Línea transportada actual
			// m = Posición en el eje X de la casilla actual

		if ( lineasALimpiar )
		{
			for ( int k = 0 ; k < lineasALimpiar ; k++ )
			{
				for ( int l = posicionLineasLimpiadas[k] ; l > 0 ; l-- )
				{
					for ( int m = 0 ; m < 10 ; m++ )
						this->casillas[m][l] = this->casillas[m][l-1];
				}
				for ( int m = 0 ; m < 10 ; m++ )
						this->casillas[m][0] = 0;

				lineasLimpiadas++;
			}
		}

		return lineasLimpiadas;
	}