/**
 * @file SceneBuilderVisitor.h
 * @author Elijah Gleckler
 *
 * A GameObject visitor that can
 * iterate over a bunch of GameObjects
 * and create a SceneObject.
 *
 * Almost like a Scene factory? Idk.
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_SCENEBUILDERVISITOR_H
#define LEARNING_OPENGL_GAMELIB_SRC_SCENEBUILDERVISITOR_H

#include <memory>

#include "GameObjectVisitor.h"

class Scene;
/**
 * A GameObject visitor that can iterate over a
 * bunch of GameObjects and create a SceneObject.
 */
class SceneBuilderVisitor : public GameObjectVisitor
{
private:

    /// A scene we've created.
    Scene* mScene = nullptr;


public:

    SceneBuilderVisitor(Scene* scene) : mScene(scene) {}

    /// Default constructor (disabled)
    SceneBuilderVisitor() = delete;

    /// Copy constructor (disabled)
    SceneBuilderVisitor(const SceneBuilderVisitor &) = delete;

    /// Assignment operator
    void operator=(const SceneBuilderVisitor &) = delete;

    // ****************************************************************
    // GameObjectVisitor overrides:

    virtual void VisitGameObject(GameObject* gameObject) override;
    virtual void VisitLightSrcObject(LightSrcObject* lightSrcObject) override;
    virtual void VisitPlayerObject(PlayerObject* playerObject) override;




};

#endif //LEARNING_OPENGL_GAMELIB_SRC_SCENEBUILDERVISITOR_H
