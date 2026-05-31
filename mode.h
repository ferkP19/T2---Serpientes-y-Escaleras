#include "snake.h"

class GameMode
{
    protected:
        Board*   board;
        Dice     dado;
        int      casillas;
        int      penalty;
        int      reward;
        int      jugadores;
        int      turns;

    public:
        GameMode(Board* b, int c, int p, int r, int j, int t)
        {
            board   = b;
            casillas   = c;
            penalty = p;
            reward  = r;
            jugadores = j;
            turns   = t;
        }

        virtual void ejecutar() = 0; // polimorfismo volviendose abstracta
        virtual ~GameMode() {}
};


class ModoManual : public GameMode // herencia
{
    public:
        ModoManual(Board* b, int c, int p, int r, int j, int t) : GameMode(b, t, p, r, j, t) {}

        void ejecutar() override
        {
            cout << "\n=== MODO MANUAL ===\n";

            int turno = 0;
            int posJugador = 0;

            while (turno < turns && posJugador < casillas - 1)
            {
                turno++;
                cout << "\nTurno " << turno << " - Presiona ENTER para lanzar el dado \n";
                cin.ignore();

                int roll = dado.roll();
                posJugador = posJugador + roll;

                if (posJugador >= casillas)
                {
                    posJugador = casillas - 1;
                }

                cout << "Dado: " << roll << " | Posicion: " << posJugador << "\n";
                posJugador = board->getCasilla(posJugador)->aplicarEfecto(posJugador);
            }

            if (posJugador >= casillas - 1)
                cout << "\nGanaste!\n";
            else
            {
                cout << "\nSe acabo el limite de turnos\n";
            }
        }
};

class ModoAutomatico : public GameMode
{
    public:
        ModoAutomatico(Board* b, int c, int p, int r, int j, int t) : GameMode(b, c, p, r, p, t) {}

        void ejecutar() override
        {
            cout << "\n=== MODO AUTOMATICO ===\n";

            int turno = 0;
            int posJugador = 0;

            while (turno < turns && posJugador < casillas - 1)
            {
                turno++;

                int roll = dado.roll();
                posJugador = posJugador + roll;

                if (posJugador >= casillas)
                {
                    posJugador = casillas - 1;
                }

                cout << "Turno " << turno << " | Dado: " << roll << " | Posicion: " << posJugador << "\n";

                posJugador = board->getCasilla(posJugador)->aplicarEfecto(posJugador);
            }

            if (posJugador >= casillas - 1)
            {
                cout << "\nGanaste!\n";
            }
            else
            {
                cout << "\nSe acabo el limite de turnos\n";
            }   
        }
};

class Game
{
    private:
        int casillas = 20; // parametros ya predefinidos si se escoge el modo manual
        int serpientes = 2;
        int escaleras = 2;
        int penalty = 3;
        int reward = 4;
        int jugadores = 2;
        int turns = 10;
        char type = 'M';

        Board*    board;
        GameMode* modo;

    public:
        Game()
        {
            board = 0;
            modo  = 0;
        }

        ~Game(){}

        void pedirConfiguracion()
        {
            cout << "\n=== CONFIGURACION DEL JUEGO ===\n";

            cout << "Numero de casillas [" << casillas << "]: "; // me muestra el número de casillas que ya hay predefinidas para tener una idea de cuantos poder agregar
            cin >> casillas;

            cout << "Numero de serpientes [" << serpientes << "]: ";
            cin >> serpientes;

            cout << "Numero de escaleras [" << escaleras << "]: ";
            cin >> escaleras;

            cout << "Penalizacion por serpiente [" << penalty << "]: ";
            cin >> penalty;

            cout << "Recompensa por escalera [" << reward << "]: ";
            cin >> reward;

            cout << "Numero de jugadores [" << jugadores << "]: ";
            cin >> jugadores;

            cout << "Turnos maximos [" << turns << "]: ";
            cin >> turns;

            cout << "Tipo de juego (M=Manual / A=Automatico) [" << type << "]: ";
            cin >> type;
            type = toupper(type);
        }

        void iniciar()
        {
            pedirConfiguracion();

            board = new Board(casillas);

            // Agregar serpientes y escaleras en posiciones aleatorias
            for (int i = 0; i < serpientes; i++)
            {
                int pos = rand() % (casillas - 2) + 1;
                board->agregarSerpiente(pos, penalty);
            }
            for (int i = 0; i < escaleras; i++)
            {
                int pos = rand() % (casillas - 2) + 1;
                board->agregarEscalera(pos, reward);
            }

            if (type == 'A')
                modo = new ModoAutomatico(board, casillas, penalty, reward, jugadores, turns);
            else
                modo = new ModoManual(board, casillas, penalty, reward, jugadores, turns);

            modo->ejecutar(); 
        }
};
