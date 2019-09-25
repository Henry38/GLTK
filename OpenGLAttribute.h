#ifndef OPENGLATTRIBUT_H
#define OPENGLATTRIBUT_H

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <array>
#include <memory>


namespace gl {

enum AttributName
{
    ClearColor,
    CullFace,
    DepthFunc,
    DepthMask,
    DepthTest,
    Viewport,
    Count
};

/**
 * @brief The OpenGL class
 */
template <AttributName N>
struct OpenGL
{
    using Type = void;
};

template<>
struct OpenGL<ClearColor>
{
    using Type = std::array<GLfloat,4>;

    static Type Get()
    {
        Type value;

        glGetFloatv(GL_COLOR_CLEAR_VALUE, value.data());

        return value;
    }
    static void Set(Type value)
    {
        glClearColor(value[0],value[1],value[2],value[3]);
    }
};

template<>
struct OpenGL<CullFace>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_CULL_FACE, &value);

        return value;
    }
    static void Set(Type value)
    {
        if(value == GL_TRUE)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
    }
};

template<>
struct OpenGL<DepthFunc>
{
    using Type = GLenum;

    static Type Get()
    {
        int value;

        glGetIntegerv(GL_DEPTH_FUNC, &value);

        return Type(value);
    }
    static void Set(Type value)
    {
        glDepthFunc(value);
    }
};

template<>
struct OpenGL<DepthMask>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_DEPTH_WRITEMASK, &value);

        return value;
    }
    static void Set(Type value)
    {
        glDepthMask(value);
    }
};

template<>
struct OpenGL<DepthTest>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_DEPTH_TEST, &value);

        return value;
    }
    static void Set(Type value)
    {
        if(value == GL_TRUE)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }
};

template<>
struct OpenGL<Viewport>
{
    using Type = std::array<GLint,4>;

    static Type Get()
    {
        Type value;

        glGetIntegerv(GL_VIEWPORT, value.data());

        return value;
    }
    static void Set(Type value)
    {
        glViewport(value[0],value[1],value[2],value[3]);
    }
};

class OpenGLStateMachine;

/**
 * @brief The BaseOpenGLAttribut class
 */
class BaseOpenGLAttribut
{
public:
    using SPtr = std::shared_ptr< BaseOpenGLAttribut >;
};

/**
 * @brief The OpenGLAttribut class
 */
template< AttributName N >
class OpenGLAttribut : public BaseOpenGLAttribut
{
    friend class OpenGLStateMachine;

public:
    using Type = typename OpenGL<N>::Type;
    using SPtr = std::shared_ptr< OpenGLAttribut<N> >;

public:
    OpenGLAttribut(const Type& value) :
        m_value(value)
    {
    }

public:
    Type value() const
    {
       return this->m_value;
    }

private:
    void setValue(const Type& value)
    {
        this->m_value = value;
    }

public:
    static SPtr Create(const Type& value)
    {
        return SPtr(new OpenGLAttribut<N>(value));
    }

private:
    Type m_value;

};

}  // namespace gl

#endif
