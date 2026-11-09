#include "LearnOpenGLLayer.h"


/*

TODO:
    - Switch Back to Indexed Rendering
    - Abstraction of RenderCommand?
    - Autoloading textures and shaders in assetmanager
    - Default Models into asset manager?


*/
LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL"), m_Shader(nullptr)
{
    
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    delete m_Shader;
    delete m_Camera;
}

void LearnOpenGLLayer::OnAttach()
{

    InitCamera(glm::vec3{ 0,0,3.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,-1.0f });

    std::vector<f32> vertices = {
        // Back face (-Z)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3

        // Front face (+Z)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7

        // Left face (-X)
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 11

        // Right face (+X)
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 12
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 13
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 14
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 15

         // Bottom face (-Y)
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 16
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 17
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 18
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 19

         // Top face (+Y)
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 20
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 21
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 22
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // 23
    };

      std::vector<ui32> indices = {
        0,  1,  2,   2,  3,  0,  // Back face
        4,  5,  6,   6,  7,  4,  // Front face
        8,  9,  10,  10, 11, 8,  // Left face
        12, 13, 14,  14, 15, 12, // Right face
        16, 17, 18,  18, 19, 16, // Bottom face
        20, 21, 22,  22, 23, 20  // Top face
    };

    m_Shader = m_AssetManager->getShader("Texture");
    m_WoodenCube = new Pixel::Model(*m_AssetManager, "cube", vertices, indices, "Texture", { "WoodContainer", "Harvey" });

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
    m_WoodenCube->m_Shader->bind();

    glm::mat4 view = m_Camera->GetViewMatrix();
    m_Shader->setUniform("view", view);

    glm::mat4 proj = m_Camera->getProjectionMatrix(Pixel::APP_WIDTH, Pixel::APP_HEIGHT);
    m_Shader->setUniform("projection", proj);

    //Render Wooden Cubes

    Pixel::RenderCommand rc;
    for (unsigned int i = 0; i < 10; i++)
    {
        //Update Model Matrix for multiple wooden cubes
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, cubePositions[i]);
        transform = glm::rotate(transform, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

        //Build render command
        rc.VAO = m_WoodenCube->m_VAO;
        rc.shaderID = m_WoodenCube->m_Shader->ID();
        rc.transform = transform;
        rc.textureIDs = m_WoodenCube->m_Textures;

        m_Renderer->submit(rc);
    }

    m_Shader->setUniform("mixValue", m_mixValue);

    //Send it!
    m_Renderer->flush(view, proj);  //TODO Should the renderer automatically flush at the end of every update loop?
}

void LearnOpenGLLayer::OnDetach()
{
    delete m_WoodenCube;
    delete m_LightCube;
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

