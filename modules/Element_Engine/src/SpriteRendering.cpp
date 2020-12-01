#include <SpriteRendering.h>

Shader::sptr SpriteRenderer::shader = nullptr;




void SpriteRenderer::DrawSprite(Sprite sprite)
{
    shader->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(sprite.m_Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * sprite.m_Size.x, 0.5f * sprite.m_Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(sprite.m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * sprite.m_Size.x, -0.5f * sprite.m_Size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(sprite.m_Size, 1.0f)); // last scale

    shader->SetUniformMatrix("model", model);

    shader->SetUniform("image", 0);

    sprite.m_Texture->Bind(0);


    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    shader = Shader::Create();
    shader->LoadShaderPartFromFile("shader/sprite_vert.glsl", GL_VERTEX_SHADER);
    shader->LoadShaderPartFromFile("shader/sprite_frag.glsl", GL_FRAGMENT_SHADER);
    shader->Link();

    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
      -0.5f, -0.5f, 0.f, 0, 0,
        -0.5f, 0.5f, 0.f, 0, 1,
        0.5f, -0.5f, 0.f, 1, 0,
        -0.5f, 0.5f, 0.f, 0, 1,
        0.5f, 0.5f, 0.f, 1, 1,
        0.5f, -0.5f, 0.f, 1, 0
    };

}
