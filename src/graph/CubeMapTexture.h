#ifndef GLTK_CUBEMAPTEXTURE_H
#define GLTK_CUBEMAPTEXTURE_H

#include <Texture.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The CubeMapTexture class
 */
class CubeMapTexture : public Texture
{

public:
    using SPtr = std::shared_ptr<CubeMapTexture>;

public:
    CubeMapTexture();
    CubeMapTexture(const std::string& filename);

};

}   // namespace gl

#endif
