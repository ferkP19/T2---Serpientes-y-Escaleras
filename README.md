# T2---Serpientes-y-Escaleras

## De que trata
Es una pequeña simulación del juego de "Serpientes y Escaleras" donde el usario puede parametrizar la configuración 
del juego, es decir, el usario puede elegir el numero de casillas, turnos, jugadores, de serpientes, de escaleras
y asi..., también esta la opción de elegir el modo de juego: M = Manual, A = Automático. Quiere decir que si
elegimos el modo manual, el usario puede configurarlo a su gusto, encambio si escoge el modo automático,
el usario no podra elegir nada de lo previo y el juego arrojara la configuración automática.

## Cómo compilarlo?
Se necesita tener instalado el compilador de g++ y de ahi compilar el siguiente comando:
**g++ -std=c++17 main.cpp -o snake3**
y ejecutar así:
**./snake3**

## Cómo se juega?
Al inciar la simulación se le pide al usario configurar el juego con los siguientes parámetros:
**Casillas** = 30 (por defecto ya son 20)
**Serpientes** = 2 (por defecto ya son 2)
**Escaleras** = 2 (por defecto ya son 2)
**Penalty** = 3 (casillas que se retroceden por defecto)
**Reward** = 4 (casillas que se avanzan por defecto)
**Turns** = 10 (turnos máximos)
**Type** = M (modo de juego)

En el modo manual el usario presiona **ENTER** para lanzar el dado en cada turno.
El modo automático la simulación corre solita hasta que alguno de los jugadores gane.
Si caes en una casilla con serpiente, retrocedes según como este la penalización.
Si caes en una casilla con escalera, avanzas según como este la recompensa.

## Estructura del código
├── main.cpp       — Crea y arranca el juego
├── snake.h        — Clases base: Casilla, CasillaNormal, CasillaSerpiente,
│                    CasillaEscalera, Dice, Jugador, Board
└── game.h         — Clases de juego: GameMode, ModoManual, ModoAutomatico, Game

## Jerarquía de las clases
Casilla  (abstracta)
├── CasillaNormal
├── CasillaSerpiente
└── CasillaEscalera

GameMode  (abstracta)
├── ModoManual
└── ModoAutomatico
