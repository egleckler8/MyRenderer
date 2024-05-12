/**
 * @file Behavior.h
 * @author Elijah Gleckler
 *
 * Encapsulates the functionality of some behavior.
 * Related back to a GameObject that it will modify
 * when the behavior is told to update.
 *
 * Base class has "default" behavior: do nothing on Update
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H
#define LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H



class GameObject;
/**
 * Encapsulates the functionality of some behavior.
 * Related back to a GameObject that it will modify
 * when the behavior is told to update.
 */
class Behavior
{
private:

    /// Assocation back to its carrier object...
    /// So the behavior can access & update the object
    GameObject* mExhibitor;

public:

    // Has default constructor
    Behavior(GameObject* exhibitor) : mExhibitor(exhibitor) {}

    /// Copy constructor (disabled)
    Behavior(const Behavior &) = delete;

    /// Assignment operator
    void operator=(const Behavior &) = delete;

    // ****************************************************************

    /**
     * Set the game object that will exhibit this behavior
     * @param exhibitor New behavior exhibitor
     */
    void SetExhibitor(GameObject* exhibitor) { mExhibitor = exhibitor; }

    // ****************************************************************

    // TODO... do I make behavior abstract?
    // If I make a "if not nullptr" clause in GameObject::Update,
    // it might not be necessary to have a "default/do nothing" behavior
    // On the other hand, GameObject forced constuctor initializes Behavior,
    // and this default constructor is disabled, so we should be fine.
    virtual void Update(double dt);



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H
