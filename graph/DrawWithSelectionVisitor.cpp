#include "DrawWithSelectionVisitor.h"

#include <graph/Node.h>
#include <opengl/ShaderProgram.h>
#include <opengl/VisualModel.h>
#include <opengl/VisualManager.h>

using namespace gl;

DrawVisitorWithSelection::DrawVisitorWithSelection() : DrawVisitor(),
    m_outlineShader(nullptr),
    m_selected(nullptr)
{
    this->m_outlineShader.reset(ShaderProgram::Create(GLTK::ShaderProgramType::OutLine));

//    Selectable* selected = GLFWApplication::Instance()->selected();
//    if (selected != nullptr) {
//        this->m_selected = selected->visualModel();
//    }
}

void DrawVisitorWithSelection::start()
{
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    DrawVisitor::start();
}

void DrawVisitorWithSelection::forwardNode(const Node* node)
{
    if (this->m_selected != nullptr) {

        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);

            if (visual == this->m_selected) {
                m_outlineShader->bind();
                m_outlineShader->updateDataIfDirty();

                // draw the object with filled primitives
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                // activate stencil buffer test
                glEnable(GL_STENCIL_TEST);
                // deactivate depth buffer test
                glDisable(GL_DEPTH_TEST);
                // set the stencil buffer to write a 1 in every time a pixel is written to the screen
                glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
                // disable color buffer
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

                const Transform& transform = visual->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visual->draw(param);

                // enable color buffer
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                // activate depth buffer test
                glEnable(GL_DEPTH_TEST);
                // deactivate stencil buffer test
                glDisable(GL_STENCIL_TEST);

                m_outlineShader->unbind();
            }
        }
    }

    DrawVisitor::forwardNode(node);
}

void DrawVisitorWithSelection::backwardNode(const Node* node)
{
    if (this->m_selected != nullptr) {

        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);

            if (visual == this->m_selected) {
                m_outlineShader->bind();
                m_outlineShader->updateDataIfDirty();

                // draw the object with thick lines
                glLineWidth(3.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                // activate stencil buffer test
                glEnable(GL_STENCIL_TEST);
                // set the stencil buffer to only allow writing
                // to the screen when the value of the
                // stencil buffer is not 1
                glStencilFunc(GL_NOTEQUAL, 1, 0xFFFFFFFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

                const Transform& transform = visual->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visual->draw(param);

                // deactivate stencil buffer test
                glDisable(GL_STENCIL_TEST);

                glLineWidth(1.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                m_outlineShader->unbind();
            }
        }
    }

    DrawVisitor::backwardNode(node);
}