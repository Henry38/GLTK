#include "Rendered.h"

#include "GLFWApplication.h"
#include "Message.h"
#include "Node.h"
#include "VisualManager.h"

using namespace gl;

Rendered::Rendered() :
    scene(nullptr),
    camera(nullptr),
    viewport(nullptr),
    framebuffer(nullptr),
    visitor(nullptr)
{

}

bool Rendered::isComplete() const
{
    return (scene != nullptr && camera != nullptr && viewport != nullptr && visitor != nullptr);
}

void Rendered::draw() const
{
    if (!isComplete())
        return;

    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (framebuffer != nullptr) {
        framebuffer->bind();
        width = framebuffer->width();
        height = framebuffer->height();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            msg_warning("Rendered") << "Framebuffer is incomplete";
            return;
        }
    }

    int v_x = viewport->x() * width;
    int v_y = viewport->y() * height;
    int v_width = viewport->rw() * width;
    int v_height = viewport->rh() * height;
    glViewport(v_x, v_y, v_width, v_height);

    VisualManager::UpdateUniformBufferCamera(*camera);

    Node* node = scene->root();
    node->executeVisitor(visitor);

    if (framebuffer != nullptr)
        framebuffer->unbind();
}
