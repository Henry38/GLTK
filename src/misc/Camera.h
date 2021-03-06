#ifndef GLTK_CAMERA_H
#define GLTK_CAMERA_H

// Glm
#include <glm/glm.hpp>


namespace gl {

/**
 * @brief The Camera class
 */
class Camera
{

public:
    Camera();
    virtual ~Camera();

public:
    glm::vec3 right() const;
    glm::vec3 up() const;
    glm::vec3 direction() const;

    glm::vec3 eye() const;
    void setEye(const glm::vec3& eye);

    glm::vec3 target() const;
    void setTarget(const glm::vec3& target);

    float fovy() const;
    void setFovy(float fovy);

    float aspectRatio() const;
    void setAspectRatio(float aspectRatio);

    float near() const;
    void setNear(float near);

    float far() const;
    void setFar(float far);

public:
    const glm::mat4& model() const;
    const glm::mat4& view() const;
    const glm::mat4& projection() const;

    const glm::mat4& mvp() const;
    const glm::mat3& normal() const;

public:
    void translate(const glm::vec3& dir);
    void rotate(float theta, float phi);
    void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);
    void perspective(float fovy, float aspect, float zNear, float zFar);
    void orthographic(float left, float right, float bottom, float top, float zNear, float zFar);

public:
    glm::mat4 projectionROI(float bounds[4]) const;

private:
    bool isMvpDirty() const;
    void setMvpDirty(bool dirty) const;

    bool isNormalDirty() const;
    void setNormalDirty(bool dirty) const;

private:
    enum ProjectionType {
        Perspective,
        Orthograhic
    };

private:
    ProjectionType m_projectionType;

    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
    float m_fovy;
    float m_aspectRatio;
    float m_zNear;
    float m_zFar;

    glm::vec3 m_eye;
    glm::vec3 m_target;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_proj;

    mutable glm::mat4 m_mvp;
    mutable glm::mat3 m_normal;

    mutable bool m_mvpDirty;
    mutable bool m_normalDirty;

};

}   // namespace gl

#endif
