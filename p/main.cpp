#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "raylib.h"
#include "particle.h"
#include "quadtree.h"
#include "collision.h"
#include "constants.h"
#include "physics.h"

int NUM_PARTICLES = 1000;
bool useBruteForce = true;
bool pause = false;

void drawHUD(bool useBruteForce, int numParticles, int collisions, int fps)
{
    // panel background — taller to fit physics rows
    DrawRectangle(10, 10, 290, 220, Color{0, 0, 0, 180});
    DrawLine(10,  10, 290,  10, DARKGREEN);
    DrawLine(10, 230, 290, 230, DARKGREEN);
    DrawLine(10,  10,  10, 230, DARKGREEN);
    DrawLine(290, 10, 290, 230, DARKGREEN);

    // FPS
    Color fpsColor = fps >= 50 ? GREEN : fps >= 30 ? YELLOW : RED;
    DrawText(("FPS:        " + std::to_string(fps)).c_str(), 20, 20, 20, fpsColor);

    // mode
    Color modeColor = useBruteForce ? RED : GREEN;
    std::string mode = useBruteForce ? "BRUTE FORCE" : "QUAD TREE";
    DrawText(("MODE:       " + mode).c_str(), 20, 45, 20, modeColor);

    // particle count
    DrawText(("PARTICLES:  " + std::to_string(numParticles)).c_str(), 20, 70, 20, WHITE);

    // collisions
    DrawText(("COLLISIONS: " + std::to_string(collisions)).c_str(), 20, 95, 20, YELLOW);

    // physics toggles
    DrawText(("[G] GRAVITY:   " + std::string(gravityEnabled    ? "ON" : "OFF")).c_str(), 20, 125, 18, gravityEnabled    ? GREEN : GRAY);
    DrawText(("[F] FRICTION:  " + std::string(frictionEnabled   ? "ON" : "OFF")).c_str(), 20, 148, 18, frictionEnabled   ? GREEN : GRAY);

       // hints
    DrawText("[SPACE] toggle mode  [P] pause", 20, 200, 13, GRAY);
}

int main()
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "CISS350 PROJECT");
    SetTargetFPS(60);
    srand(time(0));

    std::vector<Particle*> particles;
    particles.reserve(NUM_PARTICLES);

    // spawn in grid to avoid initial overlap
    int cols = 55;
    int rows = 55;
    float spacingX = WIN_WIDTH  / (float)cols;
    float spacingY = WIN_HEIGHT / (float)rows;

    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        float x = (i % cols) * spacingX + spacingX / 2;
        float y = (i / cols) * spacingY + spacingY / 2;
        int vx = (rand() % 3) + 1;
        int vy = (rand() % 3) + 1;
        if (rand() % 2) vx *= -1;
        if (rand() % 2) vy *= -1;
        particles.push_back(new Particle(x, y, 5, vx, vy));
    }

    QuadTree qt(0, 0, WIN_WIDTH, WIN_HEIGHT);

    while (!WindowShouldClose())
    {
        // inputs / key press
        if (IsKeyPressed(KEY_SPACE)) { useBruteForce  = !useBruteForce; }
        if (IsKeyPressed(KEY_P)) { pause = !pause; }
        if (IsKeyPressed(KEY_G)) { gravityEnabled = !gravityEnabled; }
        if (IsKeyPressed(KEY_F)) { frictionEnabled = !frictionEnabled; }
       
        g_collisionCount = 0;

        if (!pause)
        {
            // per particle physics
            for (Particle* p : particles)
            {
                if (gravityEnabled)  { applyGravity(p); }
                if (frictionEnabled) { applyFriction(p); }
                p->UpdateParticle();
            }

            // rebuild quadtree
            qt.clear();
            for (Particle* p : particles) { qt.insert(p); }

            for (Particle* p : particles) { p->reset_neighbors(); }

            // collision resolution
            if (useBruteForce) { resolveBruteForce(particles); }
            else { resolveQuadTree(qt); }
        }

        // render
        BeginDrawing();
        ClearBackground(BLACK);

        for (Particle* p : particles) { p->RenderParticle(); }

        if (!useBruteForce) { qt.draw(); }

        drawHUD(useBruteForce, NUM_PARTICLES, g_collisionCount, GetFPS());
        EndDrawing();
    }

    for (Particle* p : particles) { delete p; }

    particles.clear();
    CloseWindow();
    return 0;
}
