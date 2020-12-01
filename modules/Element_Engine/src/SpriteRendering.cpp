#include <SpriteRendering.h>

Shader::sptr SpriteRenderer::shader = nullptr;
VertexArrayObject::sptr SpriteRenderer::quadVAO = nullptr;



void SpriteRenderer::DrawSprite(Sprite sprite, glm::mat4 VP)
{
    shader->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(sprite.m_Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * sprite.m_Size.x, 0.5f * sprite.m_Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(sprite.m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * sprite.m_Size.x, -0.5f * sprite.m_Size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(sprite.m_Size, 1.0f)); // last scale

    shader->SetUniformMatrix("MVP", VP * model);

    shader->SetUniform("image", 0);

    sprite.m_Texture->Bind(0);


    quadVAO->Render();
}

void SpriteRenderer::initRenderData()
{
    shader = Shader::Create();
    shader->LoadShaderPartFromFile("shader/sprite_vert.glsl", GL_VERTEX_SHADER);
    shader->LoadShaderPartFromFile("shader/sprite_frag.glsl", GL_FRAGMENT_SHADER);
    shader->Link();

    // configure VAO/VBO
   
    float vertices[] = {
      -0.5f, -0.5f, 0.f, 0, 0,
        -0.5f, 0.5f, 0.f, 0, 1,
        0.5f, -0.5f, 0.f, 1, 0,
        -0.5f, 0.5f, 0.f, 0, 1,
        0.5f, 0.5f, 0.f, 1, 1,
        0.5f, -0.5f, 0.f, 1, 0
    };

    VertexBuffer::sptr VBO = VertexBuffer::Create();
    VBO->LoadData(vertices, 30);
    quadVAO = VertexArrayObject::Create();
    quadVAO->AddVertexBuffer(VBO, {
        BufferAttribute (0,3,GL_FLOAT, false, sizeof(float) * 5, 0),
        BufferAttribute (1,2,GL_FLOAT, false, sizeof(float) * 5, sizeof(float)*3)
        });
   
}
