#ifndef GAME_H
#define GAME_H
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
  public:
    GameState State;
    GLboolean Keys[1024];
    GLboolean KeysProcessed[1024];
    GLuint WindowWidth, WindowHeight, FramebufferWidth, FramebufferHeight;
    
    Game(GLuint windowWidth, GLuint windowHeight, GLuint framebufferWidth, GLuint framebufferHeight);
    ~Game();
    
    void Init();
    void ProcessInput(GLfloat deltaTime);
    void Update(GLfloat deltaTime);
    void Render();
    void DoCollisions();

    void Reset();
};

#endif