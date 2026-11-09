#include "LearnOpenGLLayer.h"


/*

TODO:
    - Autoloading textures and shaders in assetmanager
    - Default Models into asset manager? ie assetManager.get("cube") returns a ref to a cube model


*/
LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL")
{
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    delete m_Cube;
}

void LearnOpenGLLayer::OnAttach()
{
    InitCamera(glm::vec3{ 0,0,3.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,-1.0f });
    m_Cube = new Pixel::Cube(*m_AssetManager, "cube", "Texture", { "WoodContainer" });

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
    Pixel::RenderCommand rc;
    for (unsigned int i = 0; i < 10; i++)
    {
        //Update Transform for multiple wooden cubes
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, cubePositions[i]);
        transform = glm::rotate(transform, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

        /*
                Build render command
        */

        //Vertex Data
        rc.VAO = m_Cube->m_VAO;
        rc.indicesCount = m_Cube->m_IndicesCount;

        //Shader
        rc.shaderID = m_Cube->m_Shader->ID();

        //MVP Matrices
        rc.transform = transform;
        rc.projection = m_Camera->getProjectionMatrix(Pixel::APP_WIDTH, Pixel::APP_HEIGHT);
        rc.view = m_Camera->GetViewMatrix();

        //Textures
        rc.textureIDs = m_Cube->m_Textures;

        m_Renderer->submit(rc);
    }

    //Send it!
    m_Renderer->flush();
}

void LearnOpenGLLayer::OnDetach()
{
    delete m_Cube;
}

void LearnOpenGLLayer::processInput(Pixel::WindowData* inputs)
{
    //keyPresses
    if (inputs->isKeyPressed[GLFW_KEY_UP])
    {
    }
    else if (inputs->isKeyPressed[GLFW_KEY_DOWN])
    {
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

