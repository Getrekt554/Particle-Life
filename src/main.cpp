#include <raylib.h>
#include <ctime>
#include <iostream>
#include "calculations.cpp"
#include "particle.cpp"

const int NUM_PARTICLES = 2000;
int SCR_WIDTH = 2560;
int SCR_HEIGHT = 1440;
const double FORCE_SCALE = RMAX * 30.0;

float dt = 0.005;

//attraction matrix
double ATTR_MAT[11][11];

const float FRICTION_HALF_LIFE = 0.040;
double friction_case = pow(0.5, dt / FRICTION_HALF_LIFE);

void randomizeAttrMat() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            // random double between -1.0 and 1.0
            ATTR_MAT[i][j] = -1.0 + 2.0 * (rand() / (double)RAND_MAX);
        }
    }
}

void update_particles(Particle* particles) {
    #pragma omp parallel for
    for (int i = 0; i < NUM_PARTICLES; i++) {
        // Wrap around screen
        if (particles[i].position.x < -SIZE) {
            particles[i].position.x = SCR_WIDTH;
        } else if (particles[i].position.x > SCR_WIDTH + SIZE) {
            particles[i].position.x = 0;
        } else if (particles[i].position.y < -SIZE) {
            particles[i].position.y = SCR_HEIGHT;
        } else if (particles[i].position.y > SCR_HEIGHT + SIZE) {
            particles[i].position.y = 0;
        }

        Vector2 total_force{0.0, 0.0};

        for (int j = 0; j < NUM_PARTICLES; j++) {
            if (j == i) continue;

            double rx = particles[j].position.x - particles[i].position.x;
            double ry = particles[j].position.y - particles[i].position.y;
            double r2 = rx * rx + ry * ry;

            if (r2 > 0 && r2 < RMAX * RMAX) {
                double r = sqrt(r2);
                double f = F(r / RMAX, ATTR_MAT[particles[i].color][particles[j].color]);
                total_force.x += rx / r * f;
                total_force.y += ry / r * f;
            }
        }

        total_force.x *= FORCE_SCALE;
        total_force.y *= FORCE_SCALE;

        particles[i].velocity.x *= friction_case;
        particles[i].velocity.y *= friction_case;
        particles[i].velocity.x += total_force.x * dt;
        particles[i].velocity.y += total_force.y * dt;
    }

    #pragma omp parallel for
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].position.x += particles[i].velocity.x * dt;
        particles[i].position.y += particles[i].velocity.y * dt;
    }
}


int main() {
    srand(time(NULL));
    randomizeAttrMat();

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Particle Life");
    int monitor = 0;
    SCR_WIDTH = GetMonitorWidth(monitor);
    SCR_HEIGHT = GetMonitorHeight(monitor);
    SetWindowSize(SCR_WIDTH, SCR_HEIGHT);


     Particle particles[NUM_PARTICLES];

     for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].position = {(float)(rand() % SCR_WIDTH), (float)(rand() % SCR_HEIGHT)};
        particles[i].color = rand() % 11;
     } 

    while (WindowShouldClose() == false) {
        //update shit
        update_particles(particles);

        //draw
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < NUM_PARTICLES; i++) {
            particles[i].draw();
        }
        EndDrawing();
    }
    CloseWindow();
}