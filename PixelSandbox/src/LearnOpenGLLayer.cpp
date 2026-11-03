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

    //vertices = {
    //    // positions         // texture coords
    //     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
    //    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
    //    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
    //};

     vertices = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    //Pixel::Matrix<f32, 4, 4> rotation;
    //rotation.rotate(Pixel::Vec3f{ 0, 0, 1 }, TORADIANS(m_RotateAngle));

    //Pixel::Matrix<f32, 4, 4> scale;
    //scale.scale(Pixel::Vec3f{ 0.5f,0.5f,0.5f});

    //auto transform = scale * rotation;

    
    Pixel::Matrix<f32, 4, 4> model;
    model.rotate(Pixel::Vec3f{ 1.0f, 1.0f, 0.0f }, TORADIANS(m_RotateAngle));

    Pixel::Matrix<f32, 4, 4> view;
    view.translate(Pixel::Vec3f{ 0.0f,0.0f,-3.0f });

    Pixel::Matrix<f32, 4, 4> proj;
    proj.perspective(TORADIANS(45.0f), (f32)(1920/2) / (f32)(1080/2), 0.1f, 100.0f);

    m_Renderer->submit(vertices, indices);
    m_Shader->setUniform("mixValue", m_mixValue);
    m_Shader->setUniform("model", model.data());
    m_Shader->setUniform("view", view.data());
    m_Shader->setUniform("projection", proj.data());

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

    if (inputs->isKeyPressed[GLFW_KEY_LEFT])
    {
        m_RotateAngle -= 1.0f;
       
    }
    else if (inputs->isKeyPressed[GLFW_KEY_RIGHT])
    {
        m_RotateAngle += 1.0f;
    }

    // Detect press edge (transition from not pressed -> pressed)
    if (inputs->isMouseButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && !m_PrevMouseButtonState[GLFW_MOUSE_BUTTON_LEFT])
    {
        PIX_TRACE("LEFT Click");
    }
    if (inputs->isMouseButtonPressed[GLFW_MOUSE_BUTTON_RIGHT] && !m_PrevMouseButtonState[GLFW_MOUSE_BUTTON_RIGHT])
    {
        PIX_TRACE("Right Click");
    }
    if (inputs->isMouseButtonPressed[GLFW_MOUSE_BUTTON_MIDDLE] && !m_PrevMouseButtonState[GLFW_MOUSE_BUTTON_MIDDLE])
    {
        PIX_TRACE("Party button!");
    }

    // Update previous state for next frame
    for (int i = 0; i < 8; i++)
    {
        m_PrevMouseButtonState[i] = inputs->isMouseButtonPressed[i];
    }

    //PIX_TRACE("MousePos: ({0}, {1}", inputs->mouseX, inputs->mouseY);
}

