//Most of the SpriteRendering code is from:
//https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
//this also applies to both sprite_frag.glsl & sprite_vert.glsl
#pragma once
#include <GLM/glm.hpp>
#include <Shader.h>
#include <Texture2D.h>
#include <glm/gtc/matrix_transform.hpp>
#include <VertexArrayObject.h>


struct Sprite
{
    Texture2D::sptr m_Texture = nullptr;
    glm::vec2 m_Position = glm::vec2(0, 0);
    glm::vec2 m_Size = glm::vec2(10, 10);
    float m_Rotation = 0.f;
    glm::vec3 m_Color = glm::vec3(1, 1, 1);
};
class SpriteRenderer abstract
{
public:


    static void initRenderData();

    static void DrawSprite(Sprite sprite, glm::mat4 VP);

    static Shader::sptr GetShader()
    {
        return shader;
    }
private:
    static Shader::sptr shader;
    static VertexArrayObject::sptr quadVAO;

};

