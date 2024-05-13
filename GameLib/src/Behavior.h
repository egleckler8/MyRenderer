/**
 * @file Behavior.h
 * @author Elijah Gleckler
 *
 * Encapsulates the functionality of some behavior.
 * Related back to a GameObject that it will modify
 * when the behavior is told to update.
 *
 * ABSTRACT BASE CLASS!
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H
#define LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H


class GameObject;
/**
 * Encapsulates the functionality of some behavior.
 * Related back to a GameObject that it will modify
 * when the behavior is told to update.
 *
 * ABSTRACT BASE CLASS!
 */
class Behavior
{
private:

    /// Association back to its carrier object...
    /// So the behavior can access & update the object
    GameObject* mExhibitor;

protected:


    /**
     * Get the object who "exhibits" this behavior instance
     *
     * Protected so that only derived classes can access
     * this exhibitor of this Behavior.
     *
     * @return the object who "exhibits" this behavior instance
     */
    GameObject* GetExhibitor() { return mExhibitor; }


public:

    /// Constructor
    Behavior(GameObject* exhibitor) : mExhibitor(exhibitor) {}

    /// Copy constructor (disabled)
    Behavior(const Behavior &) = delete;

    /// Assignment operator
    void operator=(const Behavior &) = delete;

    /// Virtual destructor
    virtual ~Behavior() {}

    // ****************************************************************

    /**
     * Set the game object that will exhibit this behavior
     * @param exhibitor New behavior exhibitor
     */
    void SetExhibitor(GameObject* exhibitor) { mExhibitor = exhibitor; }

    // ****************************************************************

    /**
     * Updates the behavior based on elapsed time
     * @param t Time in seconds
     */
    virtual void Update(double t) = 0;



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_BEHAVIOR_H
