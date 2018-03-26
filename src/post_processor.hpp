#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "sprite_renderer.hpp"
#include "shader.hpp"

class PostProcessor
{
  public:
    Shader PostProcessingShader;
    Texture2D Texture;
    GLuint Width, Height;
    
    GLboolean Confuse, Chaos, Shake;
    
    PostProcessor(Shader shader, GLuint width, GLuint height);
    ~PostProcessor();
    
    void BeginRender();
    void EndRender();
    void Render(GLfloat time);

  private:
    GLuint MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
    GLuint RBO;        // RBO is used for multisampled color buffer
    GLuint quadVAO;
    
    void initRenderData();
};

#endif