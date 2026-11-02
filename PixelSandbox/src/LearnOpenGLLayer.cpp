#include "LearnOpenGLLayer.h"

LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL"), m_Shader(nullptr)
{
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    delete m_Shader;
}



void LearnOpenGLLayer::OnAttach()
{

    m_Shader = m_AssetManager->getShader("Texture");
    m_Texture1 = m_AssetManager->getTexture("WoodContainer");
    m_Texture2 = m_AssetManager->getTexture("Harvey");

    vertices = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

   indices = {  // note that we start from 0!
       0, 1, 3,  // first Triangle
       1, 2, 3   // second Triangle
    };

   m_Shader->use();
   m_Shader->setUniform("texture1", 0);
   m_Shader->setUniform("texture2", 1);
}

void LearnOpenGLLayer::OnUpdate()
{

    m_Renderer->submit(vertices, indices);
    m_Shader->setUniform("mixValue", m_mixValue);
    if (m_Shader != nullptr)
    {
        
        m_Renderer->flush(m_Shader, m_Texture1, m_Texture2);
    }
    else
    {
        PIX_CORE_WARN("No Shader Set for layer '{0}'", GetName());
    }
}

void LearnOpenGLLayer::OnDetach()
{
}

void LearnOpenGLLayer::processInput(Pixel::InputData* inputs)
{
    if (inputs->isKeyPressed[GLFW_KEY_UP])
    {
        m_mixValue += 0.01f;
        if (m_mixValue > 1.0f) m_mixValue = 1.0f;
    }
    else if (inputs->isKeyPressed[GLFW_KEY_DOWN])
    {
        m_mixValue -= 0.01f;
        if (m_mixValue < 0.0f) m_mixValue = 0.0f;
    }
}

