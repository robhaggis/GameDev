#include "AStarDemo.h"

AStarDemoLayer::AStarDemoLayer()
    :Layer("LearnOpenGL"), m_Shader(nullptr)
{
    
}

AStarDemoLayer::~AStarDemoLayer()
{
    delete m_Shader;
    delete m_Camera;
}

void AStarDemoLayer::OnAttach()
{
    InitCamera(glm::vec3{ 0.0f,3,10.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,0 });
   

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
    m_WoodenCube = new Pixel::Model(*m_AssetManager, "cube", vertices, indices, "Texture", { "BlueBorder"});


    f32 cubeSpacing = 0.4f;
    
    f32 yOffset = 3.0f;
    m_Camera->LookAt(glm::vec3{ -0.5f * cubeSpacing, -yOffset, -0.5f * cubeSpacing });
    
   // cubePositions = {
   //     glm::vec3(0.0f,  0.0f,  0.0f),
   //     glm::vec3(2.0f,  5.0f, -15.0f),
   //     glm::vec3(-1.5f, -2.2f, -2.5f),
   //     glm::vec3(-3.8f, -2.0f, -12.3f),
   //     glm::vec3(2.4f, -0.4f, -3.5f),
   //     glm::vec3(-1.7f,  3.0f, -7.5f),
   //     glm::vec3(1.3f, -2.0f, -2.5f),
   //     glm::vec3(1.5f,  2.0f, -2.5f),
   //     glm::vec3(1.5f,  0.2f, -1.5f),
   //     glm::vec3(-1.3f,  1.0f, -1.5f)
   //};

    for (i32 z = -10; z < 10; z++)
    {
        for(i32 x = -10; x < 10; x++)
        {
            cubePositions.emplace_back( glm::vec3{ x * cubeSpacing, -yOffset, z * cubeSpacing } );
        }
    }
    
}

void AStarDemoLayer::OnUpdate()
{
    f32 cubeScale = 0.4f;


    m_WoodenCube->m_Shader->bind();

    glm::mat4 view = m_Camera->GetViewMatrix();
    m_Shader->setUniform("view", view);

    glm::mat4 proj = m_Camera->getProjectionMatrix(Pixel::APP_WIDTH, Pixel::APP_HEIGHT);
    m_Shader->setUniform("projection", proj);

    //Render Wooden Cubes
    for (glm::vec3 c : cubePositions)
    {
        //Update Model Matrix for multiple wooden cubes
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, c);
        //transform = glm::rotate(transform, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
        transform = glm::scale(transform, glm::vec3{ cubeScale });
        m_Renderer->submit(m_WoodenCube, transform);
    }

    m_Shader->setUniform("mixValue", m_mixValue);

    //Send it!
    m_Renderer->flush(view, proj);  //TODO Should the renderer automatically flush at the end of every update loop?
}

void AStarDemoLayer::OnDetach()
{
    delete m_WoodenCube;
}

void AStarDemoLayer::processInput(Pixel::WindowData* inputs)
{
    //keyPresses
    

    //Mouse Click
    
    
    //Camera Move
    
    
    //Camera Look
    m_Camera->ProcessMouseMovement(inputs->mouseXOffset, inputs->mouseYOffset);

    //Camera Zoom
    m_Camera->ProcessMouseScroll(inputs->mouseScrollOffset);
}

