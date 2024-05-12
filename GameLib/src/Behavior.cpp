/**
 * @file Behavior.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <stdexcept>

#include "Behavior.h"


/**
 * Update the linked object in a unique way?
 * Base class version does nothing.
 * @param dt Time elapsed in seconds
 *
 * Throws an error if the exhibitor is null,
 * as it should... We should never encounter
 * this, anyway
 */
void Behavior::Update(double dt)
{
    if (mExhibitor == nullptr)
    {
        throw std::runtime_error("Behavior exhibitor was nullptr.");
    }
}
