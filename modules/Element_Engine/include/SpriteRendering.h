//Most of the SpriteRendering code is from:
//https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
//this also applies to both sprite_frag.glsl & sprite_vert.glsl
#pragma once
#include <GLM/glm.hpp>
#include <Shader.h>
#include <Texture2D.h>
#include <glm/gtc/matrix_transform.hpp>


struct Sprite
{
    Texture2D::sptr m_Texture = nullptr;
    glm::vec2 m_Position = glm::vec2(0, 0);
    glm::vec2 m_Size = glm::vec2(10, 10);
    float m_Rotation = 0.f;
    glm::vec3 m_Color = glm::vec3(1, 1, 1);
};
class SpriteRenderer
{
public:


    void initRenderData();

    void DrawSprite(Sprite sprite);

    Shader::sptr GetShader()
    {
        return shader;
    }
private:
    static Shader::sptr shader;
    unsigned int quadVAO;

};

