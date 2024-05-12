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
    GameObject* mCarrier;

public:

    // Has default constructor
    Behavior(GameObject* carrier ) : mCarrier(carrier) {}

    /// Copy constructor (disabled)
    Behavior(const Behavior &) = delete;

    /// Assignment operator
    void operator=(const Behavior &) = delete;

    // ****************************************************************

    /**
     * Update the linked object in a unique way?
     * Base class version does nothing.
     * @param dt Time elapsed in seconds
     */
    virtual void Update(double dt) {}



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H
