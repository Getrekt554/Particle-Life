#include <raymath.h>
#include <raylib.h>

const int SIZE = 2;

class Particle
{
    public:
        Vector2 velocity{0.0, 0.0};
        int color = 0;
        Vector2 position{0.0, 0.0};

        void draw() {
            Color particle_color;
            switch (color) {
                case 0:
                    particle_color = RED;
                    break;
                case 1:
                    particle_color = BLUE;
                    break;
                case 2:
                    particle_color = GREEN;
                    break;
                case 3:
                    particle_color = PURPLE;
                    break;
                case 4:
                    particle_color = YELLOW;
                    break;
                case 5:
                    particle_color = Color{113, 255, 255, 255};
                    break;
                case 6:
                    particle_color = WHITE;
                    break;
                case 7:
                    particle_color = Color{186, 196, 139, 255};
                    break;
                case 8:
                    particle_color = Color{76, 0, 212, 255};
                    break;
                case 9:
                    particle_color = Color{255, 0, 212, 255};
                    break;
                case 10:
                    particle_color = Color{255, 95, 0, 255};
            }

            DrawCircle(position.x, position.y, SIZE, particle_color);

        }
};