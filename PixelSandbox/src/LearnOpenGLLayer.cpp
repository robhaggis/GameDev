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

   cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
   cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
   cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

   glm::mat4 projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
   m_Shader->use();
   m_Shader->setUniform("projection", projection);
}

void LearnOpenGLLayer::OnUpdate()
{
    m_Shader->use();
    m_Renderer->submit(vertices, indices);

    // camera/view transformation
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    m_Shader->setUniform("view", view);


    for (unsigned int i = 0; i < 10; i++)
    {
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
        m_RotateAngle -= 0.010f;
       
    }
    else if (inputs->isKeyPressed[GLFW_KEY_RIGHT])
    {
        m_RotateAngle += 0.010f;
    }


    f32 cameraSpeed = static_cast<f32>(0.025f * inputs->deltaTime);
    if (inputs->isKeyPressed[GLFW_KEY_W])
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (inputs->isKeyPressed[GLFW_KEY_S])
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (inputs->isKeyPressed[GLFW_KEY_A])
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (inputs->isKeyPressed[GLFW_KEY_D])
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

