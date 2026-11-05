#include "LearnOpenGLLayer.h"

LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL"), m_Shader(nullptr), m_Camera(nullptr)
{
    m_Camera = new Camera(glm::vec3{ 0,0,3.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,-1.0f });
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    delete m_Shader;
    delete m_Camera;
}

void LearnOpenGLLayer::OnAttach()
{
    std::vector<f32> vertices = {
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

    std::vector<ui32> indices = {3,1,2,1,2,3};

    m_Shader = m_AssetManager->getShader("Texture");
    //Pixel::Texture* texture1 = m_AssetManager->getTexture("WoodContainer");
    //Pixel::Texture* texture2 = m_AssetManager->getTexture("Harvey");

    m_WoodenCube = new Pixel::Model(*m_AssetManager, "cube", vertices, indices, "Texture", { "WoodContainer", "Harvey" });

    m_Renderer->submit(m_WoodenCube);

    m_LightCube = new Pixel::Model(*m_AssetManager, "light", vertices, indices, "Basic", {"White"});


    cubePositions = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
   };
}

void LearnOpenGLLayer::OnUpdate()
{

    //Update View Matrix
    glm::mat4 view = m_Camera->GetViewMatrix();
    m_Shader->setUniform("view", view);

    //Update Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(m_Camera->getFOV()), static_cast<f32>(Pixel::APP_WIDTH) / static_cast<f32>(Pixel::APP_HEIGHT), 0.1f, 100.0f);
    m_Shader->setUniform("projection", projection);

    for (unsigned int i = 0; i < 10; i++)
    {
        //Update Model Matrix for multiple wooden cubes
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
        m_Shader->setUniform("model", model);
        
        //Send it!
        m_Renderer->flush();
    }

    m_Shader->setUniform("mixValue", m_mixValue);
}

void LearnOpenGLLayer::OnDetach()
{
}

void LearnOpenGLLayer::processInput(Pixel::WindowData* inputs)
{
    //keyPresses
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

    //Mouse Click
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_LEFT]) PIX_TRACE("LEFT Click");
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_RIGHT]) PIX_TRACE("Right Click");
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_MIDDLE]) PIX_TRACE("Party button!");
    
    //Camera Move
    if (inputs->isKeyPressed[GLFW_KEY_W])m_Camera->ProcessKeyboard(CameraMovement::FORWARD, inputs->deltaTime);
    if (inputs->isKeyPressed[GLFW_KEY_S])m_Camera->ProcessKeyboard(CameraMovement::BACKWARD, inputs->deltaTime);    
    if (inputs->isKeyPressed[GLFW_KEY_A]) m_Camera->ProcessKeyboard(CameraMovement::LEFT, inputs->deltaTime);
    if (inputs->isKeyPressed[GLFW_KEY_D])m_Camera->ProcessKeyboard(CameraMovement::RIGHT, inputs->deltaTime);
    
    //Camera Look
    m_Camera->ProcessMouseMovement(inputs->mouseXOffset, inputs->mouseYOffset);

    //Camera Zoom
    m_Camera->ProcessMouseScroll(inputs->mouseScrollOffset);
}

