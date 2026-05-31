#include <cstdlib>
#include <ctime>
class Dice
{
    private:
        bool seeded;
    public:
        Dice()
        {
            seeded = false;
        }

        int roll()
        {
            if (!seeded)
            {
                srand(time(0));
                seeded = true;
            }
            return (rand() % 6) + 1;
        }
};