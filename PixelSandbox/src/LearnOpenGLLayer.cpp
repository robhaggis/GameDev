#include "LearnOpenGLLayer.h"

LearnOpenGLLayer::LearnOpenGLLayer()
    :Layer("LearnOpenGL")
{
}

LearnOpenGLLayer::~LearnOpenGLLayer()
{
    OnDetach();
}

void LearnOpenGLLayer::OnAttach()
{
    InitCamera(glm::vec3{ 0,0,3.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,-1.0f });
    Pixel::Model* cube = new Pixel::Cube(*m_AssetManager, "cube", "flatColour", { "WoodContainer" });
   
    m_Models.push_back(cube);
}

void LearnOpenGLLayer::OnUpdate()
{
    Pixel::RenderCommand rc;
    for (const Pixel::Model* m : m_Models)
    {
        //Render the cube at the origin
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3{ 0,0,0 });

        //Build the render command
        //Vertex Data
        rc.VAO = m->m_VAO;
        rc.indicesCount = m->m_IndicesCount;
        //Shader
        rc.shader = m->m_Shader;
        //Uniforms
        rc.uniforms.push_back({ "model" ,transform });
        rc.uniforms.push_back({ "projection", m_Camera->getProjectionMatrix(Pixel::APP_WIDTH, Pixel::APP_HEIGHT) });
        rc.uniforms.push_back({ "view", m_Camera->GetViewMatrix() });
        rc.uniforms.push_back({ "rVal", 0.35f });
        rc.uniforms.push_back({ "gVal", 0.16f });
        rc.uniforms.push_back({ "bVal", 0.84f });
        //Textures
        rc.textureIDs = m->m_Textures;

        m_Renderer->submit(rc);
    }

    //Send it!
    m_Renderer->flush();
}

void LearnOpenGLLayer::OnDetach()
{
    for (Pixel::Model* m : m_Models)
    {
        delete m;
    }
    m_Models.clear();
}

void LearnOpenGLLayer::processInput(Pixel::WindowData* inputs)
{
    //keyPresses
    if (inputs->isKeyPressed[GLFW_KEY_UP])
    {
        for (Pixel::Model* m : m_Models)
        {
            m->setShader(m_AssetManager->getShader("flatTexture"));
        }
    }
    else if (inputs->isKeyPressed[GLFW_KEY_DOWN])
    {
        for (Pixel::Model* m : m_Models)
        {
            m->setShader(m_AssetManager->getShader("flatColour"));
        }
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

