#ifndef SCENE_H
#define SCENE_H


namespace gl {

class Camera;
class Node;
class Visitor;

/**
 * @brief The Scene class
 */
class SceneGraph
{

public:
    SceneGraph();
    virtual ~SceneGraph();

public:
    Node* root();
    const Node* root() const;

public:
    void fitView(Camera* camera) const;

public:
    void executeVisitor(Visitor* visitor) const;

private:
    Node* m_rootNode;

};

}   // namespace gl

#endif
