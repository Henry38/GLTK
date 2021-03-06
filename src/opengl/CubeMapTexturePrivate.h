#ifndef GLTK_CUBEMAPTEXTUREPRIVATE_H
#define GLTK_CUBEMAPTEXTUREPRIVATE_H

#include <TexturePrivate.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The CubeMapTexturePrivate class
 */
class CubeMapTexturePrivate : public TexturePrivate
{

public:
    using SPtr = std::shared_ptr<CubeMapTexturePrivate>;

public:
    virtual void bind() const;
    virtual void unbind() const;

public:
    virtual void load(const std::string& filename);
    virtual void load(const std::string& left, const std::string& right, const std::string& bottom, const std::string& top, const std::string& back, const std::string& front);

};

}   // namespace gl

#endif
