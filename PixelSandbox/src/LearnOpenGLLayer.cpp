#include "LearnOpenGLLayer.h"

LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL")
{
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    delete m_Shader;
}



void LearnOpenGLLayer::OnAttach()
{
    vertices = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left git
    };

   indices = {  // note that we start from 0!
       0, 1, 3,  // first Triangle
       1, 2, 3   // second Triangle
    };
}

void LearnOpenGLLayer::OnUpdate()
{
    m_Shader->setUniform("colourIn", 1.0f);
    m_Shader->setUniform("xOffset", 0.25f);

    m_Renderer->submit(vertices, indices);
    m_Renderer->flush(m_Shader->ID());
}

void LearnOpenGLLayer::OnDetach()
{
}
