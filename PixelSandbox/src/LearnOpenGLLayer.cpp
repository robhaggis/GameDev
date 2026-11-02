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
     m_Shader = new Shader(vertexShaderSource, fragmentShaderSource);
}

void LearnOpenGLLayer::OnUpdate()
{
    std::vector<f32> vertices = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
    };

    std::vector<ui32> indices = {  // note that we start from 0!
       0, 1, 3,  // first Triangle
       1, 2, 3   // second Triangle
    };

    m_Renderer->submit(vertices, indices);
    m_Renderer->render(m_Shader->ID());
}

void LearnOpenGLLayer::OnDetach()
{
    delete m_Shader;
}
