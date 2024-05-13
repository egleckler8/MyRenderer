/**
 * @file TestBehavior.h
 * @author Elijah Gleckler
 *
 * Little test behavior whose Update
 * will make the object move
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_TESTBEHAVIOR_H
#define LEARNING_OPENGL_GAMELIB_SRC_TESTBEHAVIOR_H

#include "Behavior.h"

/**
 * Little test behavior whose Update
 * will make the object move
 */
class TestBehavior : public Behavior
{
private:


public:

    /// Constructor
    TestBehavior(GameObject* exhibitor) : Behavior(exhibitor) {}

    /// Default constructor (disabled)
    TestBehavior() = delete;

    /// Copy constructor (disabled)
    TestBehavior(const TestBehavior &) = delete;

    /// Assignment operator
    void operator=(const TestBehavior &) = delete;


    void Update(double t) override;

};

#endif //LEARNING_OPENGL_GAMELIB_SRC_TESTBEHAVIOR_H
