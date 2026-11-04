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

   m_Shader->use();
   m_Shader->setUniform("texture1", 0);
   m_Shader->setUniform("texture2", 1);

   
   m_Shader->use();
   
}

void LearnOpenGLLayer::OnUpdate()
{
    m_Shader->use();
    m_Renderer->submit(vertices, indices);

    // camera/view transformation
    glm::mat4 view = glm::lookAt(m_CamPos, m_CamPos + m_CamFront, m_CamUp);
    m_Shader->setUniform("view", view);


    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 projection = glm::perspective(glm::radians(m_CamFOV), 960.0f / 540.0f, 0.1f, 100.0f);
        m_Shader->setUniform("projection", projection);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_Shader->setUniform("model", model);

        m_Renderer->flush(m_Shader, m_Texture1, m_Texture2);
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

    if (inputs->isKeyPressed[GLFW_KEY_LEFT])
    {
        m_RotateAngle -= 0.010f;
       
    }
    else if (inputs->isKeyPressed[GLFW_KEY_RIGHT])
    {
        m_RotateAngle += 0.010f;
    }

    //Camera Walk
    f32 cameraSpeed = static_cast<f32>(m_CamWalkSpeeed * inputs->deltaTime);
    if (inputs->isKeyPressed[GLFW_KEY_W])
    {
        m_CamPos += cameraSpeed * m_CamFront;
    }
    if (inputs->isKeyPressed[GLFW_KEY_S])
    {
        m_CamPos -= cameraSpeed * m_CamFront;
    }
    if (inputs->isKeyPressed[GLFW_KEY_A])
    {
        m_CamPos -= glm::normalize(glm::cross(m_CamFront, m_CamUp)) * cameraSpeed;
    }
    if (inputs->isKeyPressed[GLFW_KEY_D])
    {
        m_CamPos += glm::normalize(glm::cross(m_CamFront, m_CamUp)) * cameraSpeed;
    }

    //Mouse Clicks
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_LEFT])
    {
        PIX_TRACE("LEFT Click");
    }
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_RIGHT])
    {
        PIX_TRACE("Right Click");
    }
    if (inputs->isMouseButtonJustPressed[GLFW_MOUSE_BUTTON_MIDDLE])
    {
        PIX_TRACE("Party button!");
    }

    //Mouse Look
    inputs->lastMouseX = inputs->mouseX;
    inputs->lastMouseY = inputs->mouseY;
    
    m_CamYaw += inputs->mouseXOffset * m_MouseLookSensitivity;
    m_CamPitch -= inputs->mouseYOffset * m_MouseLookSensitivity;
    if (m_CamPitch > 89.0f) m_CamPitch = 89.0f;
    if (m_CamPitch < -89.0f)m_CamPitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_CamYaw)) * cos(glm::radians(m_CamPitch));
    direction.y = sin(glm::radians(m_CamPitch));
    direction.z = sin(glm::radians(m_CamYaw)) * cos(glm::radians(m_CamPitch));
    m_CamFront = glm::normalize(direction);

    //Camera Zoom
    m_CamFOV -= (f32)inputs->mouseScrollOffset * m_MouseZoomSensitivity;
    if (m_CamFOV < 1.0f) m_CamFOV = 1.0f;
    if (m_CamFOV > 45.0f) m_CamFOV = 45.0f;   
}

