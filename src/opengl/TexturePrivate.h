#ifndef GLTK_TEXTUREPRIVATE_H
#define GLTK_TEXTUREPRIVATE_H

// Standard Library
#include <list>
#include <memory>
#include <string>

// Glad
#include <glad/glad.h>


namespace gl {

/**
 * @brief The TexturePrivate class
 */
class TexturePrivate
{

public:
    using SPtr = std::shared_ptr<TexturePrivate>;

public:
    TexturePrivate();
    virtual ~TexturePrivate();

public:
    GLuint getTextureID() const;
    unsigned short getTextureUnit() const;

public:
    virtual void bind() const;
    virtual void unbind() const;

public:
    virtual void load(const std::string& filename) = 0;

private:
    static std::list<unsigned short> ActiveTexture;

protected:
    GLuint m_textureId;
    unsigned short m_textureUnit;

};

}   // namespace gl

#endif
