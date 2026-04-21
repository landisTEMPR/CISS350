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

int NUM_PARTICLES = 3000;
bool useBruteForce = true;


void drawHUD(bool useBruteForce, int numParticles, int collisions, int fps)
{
  // panel background
  DrawRectangle(10, 10, 290, 130, Color{0, 0, 0, 180});
  DrawLine(10,  10, 290,  10, DARKGREEN); // top
  DrawLine(10, 140, 290, 140, DARKGREEN); // bottom
  DrawLine(10,  10,  10, 140, DARKGREEN); // left
  DrawLine(290, 10, 290, 140, DARKGREEN); // right

  // FPS - color coded
  Color fpsColor = fps >= 50 ? GREEN : fps >= 30 ? YELLOW : RED;
  DrawText(("FPS:        " + std::to_string(fps)).c_str(), 20, 20,  20, fpsColor);

  // mode
  Color modeColor = useBruteForce ? RED : GREEN;
  std::string mode = useBruteForce ? "BRUTE FORCE" : "QUAD TREE";
  DrawText(("MODE:       " + mode).c_str(), 20, 45,  20, modeColor);

  // particle count
  DrawText(("PARTICLES:  " + std::to_string(numParticles)).c_str(), 20, 70,  20, WHITE);

  // collisions
  DrawText(("COLLISIONS: " + std::to_string(collisions)).c_str(), 20, 95,  20, YELLOW);

  // toggle hint
  DrawText("[SPACE] toggle mode", 20, 120, 15, GRAY);
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
    // event handling
    if (IsKeyPressed(KEY_SPACE))
    {
      useBruteForce = !useBruteForce;
    }

    g_collisionCount = 0;

    // update positions and wall collision
    for (Particle* p : particles)
    {
      p->UpdateParticle();
    }
    // rebuild quadtree
    qt.clear();
    for (Particle* p : particles)
    {
      qt.insert(p);
    }

    for (Particle* p : particles)
    {
      p->reset_neighbors();
    }
    // collision resolution
    if (useBruteForce)
    {
      resolveBruteForce(particles);
    }
    else
    {
      resolveQuadTree(qt);
    }

    // render
    BeginDrawing();
    ClearBackground(BLACK);

    for (Particle* p : particles)
    {
      p->RenderParticle();
    }
    if (!useBruteForce)
    {
      qt.draw();  // draw quadtree region borders
    }

    drawHUD(useBruteForce, NUM_PARTICLES, g_collisionCount, GetFPS());

    EndDrawing();
  }

  for (Particle* p : particles)
  {
    delete p;
  }
  particles.clear();

  CloseWindow();
  return 0;
}
