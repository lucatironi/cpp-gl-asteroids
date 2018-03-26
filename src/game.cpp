#include <sstream>

#include <irrKlang.h>
using namespace irrklang;

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "game_object.hpp"
#include "post_processor.hpp"
#include "text_renderer.hpp"

SpriteRenderer    *Renderer;
PostProcessor     *Effects;
ISoundEngine      *SoundEngine = createIrrKlangDevice();
TextRenderer      *Text;

GLfloat ShakeTime = 0.0f;
int MaxScore = 10000;
int PlayerScore = 0;

Game::Game(GLuint windowWidth, GLuint windowHeight, GLuint framebufferWidth, GLuint framebufferHeight)
    : State(GAME_MENU), Keys(),
      WindowWidth(windowWidth), WindowHeight(windowHeight),
      FramebufferWidth(framebufferWidth), FramebufferHeight(framebufferHeight)
{
}

Game::~Game()
{
    delete Renderer;
    delete Effects;
    delete Text;
    SoundEngine->drop();
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("../src/shaders/sprite.vs", "../src/shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("../src/shaders/post_processing.vs", "../src/shaders/post_processing.fs", nullptr, "postprocessing");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->WindowWidth), static_cast<GLfloat>(this->WindowHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->FramebufferWidth, this->FramebufferHeight);
    Text = new TextRenderer(this->WindowWidth, this->WindowHeight);
    Text->Load("../assets/Roboto-Bold.ttf", 42);

    // Configure game objects
}

void Game::ProcessInput(GLfloat deltaTime)
{
    if (this->State == GAME_ACTIVE)
    {
        
    }
    if (this->State == GAME_MENU || this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            this->Reset();
            this->State = GAME_ACTIVE;
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
        }
    }
}

void Game::Update(GLfloat deltaTime)
{
    if (this->State == GAME_ACTIVE)
    {
        // Update objects
        
        // Check for collisions
        this->DoCollisions();
        // Reduce shake time
        if (ShakeTime > 0.0f)
        {
            ShakeTime -= deltaTime;
            if (ShakeTime <= 0.0f)
                Effects->Shake = false;
        }
        // Check loss condition
        
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN)
    {
        Effects->BeginRender();
            // Render Game Objects
        Effects->EndRender();
        Effects->Render(glfwGetTime());

        std::stringstream ss;
        ss << "Score: " << PlayerScore;
        Text->RenderText(ss.str(), 5.0f, 5.0f, 0.25f);
    }
    if (this->State == GAME_MENU || this->State == GAME_WIN)
        Text->RenderText("Press ENTER to start", 310.0f, this->WindowHeight / 2 - 25.0f, 0.5f);
    if (this->State == GAME_WIN) {
        Text->RenderText("You Won!", 310.0f, this->WindowHeight / 2 + 25.0f, 0.75f);
    }
}

void Game::Reset()
{
    PlayerScore = 0;
}

// Collision detection
GLboolean CheckCollision(GameObject &one, GameObject &two);

void Game::DoCollisions()
{
}

GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
                      two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
                      two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}