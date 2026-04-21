#include <iostream>
#include <vector>
#include "raylib.h"
#include "particle.h"


const int WIN_HEIGHT = 720;
const int WIN_WIDTH = 1280;
int NUM_PARTICLES = 1000;
bool useBruteForce = true;


int main()
{
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "CISS350 PROJECT");
  SetTargetFPS(60);
  srand(time(0));

  Particle p;
  p.set_posX(WIN_WIDTH / 2);
  p.set_posY(WIN_HEIGHT / 2);
  p.set_rad(3);
  p.set_vX(5);
  p.set_vY(5);

  std::vector<Particle*> particles;
  // spawn in a grid instead of random to avoid initial overlap
  int cols = 40;
  int rows = 25;
  float spacingX = WIN_WIDTH  / (float)cols;
  float spacingY = WIN_HEIGHT / (float)rows;

  for (int i = 0; i < NUM_PARTICLES; i++)
  { 
    float x = (i % cols) * spacingX + spacingX / 2;
    float y = (i / cols) * spacingY + spacingY / 2;
    int vx = (rand() % 3) + 1;
    int vy = (rand() % 3) + 1;
    if (rand() % 2) { vx *= -1; }
    if (rand() % 2) { vy *= -1; }
    particles.push_back(new Particle(x, y, 5, vx, vy));
  } 
  
  while(!WindowShouldClose())
  {
    // Event Handling
    if (IsKeyPressed(KEY_SPACE))
    {
      useBruteForce = !useBruteForce;
    }
      // Update
      for (int i = 0; i < particles.size(); i++)
      {
        particles[i]->UpdateParticle(useBruteForce, particles, i);
      }
      // Render
      BeginDrawing();
      ClearBackground(BLACK);
      for (Particle* p : particles)
      {
        p->RenderParticle();
      }
      EndDrawing();
  }

    // dealloc memory
    for (Particle* p : particles)
    {
      delete p;
    } 
    particles.clear();
    // close window
    CloseWindow();
    return 0;
}
