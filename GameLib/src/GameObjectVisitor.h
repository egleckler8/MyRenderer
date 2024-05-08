/**
 * @file GameObjectVisitor.h
 * @author Elijah Gleckler
 *
 * Abstract base visitor for GameObjects
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTVISITOR_H
#define LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTVISITOR_H

class GameObject;
class LightSrcObject;
class PlayerObject;
/**
 * Abstract base visitor for GameObjects
 */
class GameObjectVisitor
{
private:

    // Nothing here to store. Maybe in a subclass...

public:

    /// Default constructor
    GameObjectVisitor() {}

    /// Copy constructor (disabled)
    GameObjectVisitor(const GameObjectVisitor &) = delete;

    /// Assignment operator
    void operator=(const GameObjectVisitor &) = delete;

    // ****************************************************************

    virtual void VisitGameObject(GameObject* gameObject) = 0;
    virtual void VisitLightSrcObject(LightSrcObject* lightSrcObject) = 0;
    virtual void VisitPlayerObject(PlayerObject* playerObject) = 0;



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTVISITOR_H
