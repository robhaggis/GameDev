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
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // pass transformation matrices to the shader
    m_Shader->setUniform("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    m_Shader->setUniform("view", view);

    //Pixel::Vec3f camPos{ 0.0f,0.0f,3.0f };
    //Pixel::Vec3f camTarget{ 0.0f,0.0f,0.0f };
    //Pixel::Vec3f camDir = camPos - camTarget;
    //camDir = camDir.normalized();

    //Pixel::Vec3f worldUp{ 0.0f,1.0f,0.0f };
    //Pixel::Vec3f camRight = worldUp.cross(camDir);
    //camRight = camRight.normalized();

    //Pixel::Vec3f camUp = camDir.cross(camRight);

    m_Renderer->submit(vertices, indices);
    m_Shader->setUniform("mixValue", m_mixValue);

    glm::vec3 cubePositions[] = {
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


    if (m_Shader != nullptr)
    {
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->setUniform("model", model);
            m_Renderer->flush(m_Shader, m_Texture1, m_Texture2);
        }
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

