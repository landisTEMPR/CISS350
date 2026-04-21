#include <iostream>
#include <vector>
#include "raylib.h"
#include "includes/particle.h"


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
  p.set_rad(5);
  p.set_vX(5);
  p.set_vY(5);

  std::vector<Particle*> particles;
  for (int i = 0; i < NUM_PARTICLES; i++)
  {
    int x = rand() % WIN_WIDTH;
    int y = rand() % WIN_HEIGHT;
    int rad = 5;
    int vx = (rand() % 5) - 2;
    int vy = (rand() % 5) - 2;
    particles.push_back(new Particle(x, y, rad, vx, vy));
  }
  
  while(!WindowShouldClose())
  {
    // Event Handling
    if (IsKeyPressed(KEY_SPACE))
    {
      useBruteForce = !useBruteForce;
    }
      // Update
      for (Particle* p : particles)
      {
        p->UpdateParticle(useBruteForce, particles);
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
