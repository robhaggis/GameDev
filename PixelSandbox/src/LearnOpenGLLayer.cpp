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
    m_Shader = new Pixel::Shader("../PixelSandbox/res/shaders/basicVert.glsl", "../PixelSandbox/res/shaders/basicFrag.glsl");
}

void LearnOpenGLLayer::OnUpdate()
{
    if (!m_Shader || m_Shader->ID() == 0) {
        PIX_CORE_ERROR("Shader not loaded!");
        return;
    }
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
}
