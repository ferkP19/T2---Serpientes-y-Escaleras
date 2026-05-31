#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "dice.h"
using namespace std;



class Casilla
{
    protected:
        int position;
    public:
        Casilla(int pos) : position(pos) {}
        virtual int aplicarEfecto(int posActual) = 0;  // clase abstracta
        virtual ~Casilla() {}
};

class CasillaNormal : public Casilla
{
    public:
        CasillaNormal(int pos) : Casilla(pos) {}
        int aplicarEfecto(int posActual) override
        {
            return posActual;  // sin efecto
        }
};

class CasillaSerpiente : public Casilla
{
    private:
        int penalty;
    public:
        CasillaSerpiente(int pos, int p) : Casilla(pos), penalty(p) {}
        int aplicarEfecto(int posActual) override
        {
            cout << "   🐍 ¡Serpiente! retrocedes " << penalty << " casillas.\n";
            int nueva = posActual - penalty;
            return nueva < 0 ? 0 : nueva;
        }
};

class CasillaEscalera : public Casilla
{
    private:
        int reward;
    public:
        CasillaEscalera(int pos, int r) : Casilla(pos), reward(r) {}
        int aplicarEfecto(int posActual) override
        {
            cout << "   🪜 ¡Escalera! avanzas " << reward << " casillas.\n";
            return posActual + reward;
        }
};

class Jugador
{
    private:
        int id;
        int position;
    public:
        Jugador(int i) : id(i), position(0) {}

        int  getPosition() const   { return position; }
        void setPosition(int pos)  { position = pos;  }
        int  getId()       const   { return id;       }
};

class Board
{
    private:
        vector<Casilla*> casillas;

        bool posValida(int pos) const
        {
            return pos >= 0 && pos < (int)casillas.size();
        }

        void reemplazar(int pos, Casilla* nueva)
        {
            delete casillas[pos];
            casillas[pos] = nueva;
        }

    public:
        Board(int sz)
        {
            for (int i = 0; i < sz; i++)
                casillas.push_back(new CasillaNormal(i));
        }

        ~Board()
        {
            for (auto c : casillas) delete c;
        }

        void agregarSerpiente(int pos, int penalty)
        {
            if (posValida(pos))
                reemplazar(pos, new CasillaSerpiente(pos, penalty));
        }

        void agregarEscalera(int pos, int reward)
        {
            if (posValida(pos))
                reemplazar(pos, new CasillaEscalera(pos, reward));
        }

        Casilla* getCasilla(int pos) const
        {
            return casillas[pos];
        }

        int getSize() const { return (int)casillas.size(); }
};