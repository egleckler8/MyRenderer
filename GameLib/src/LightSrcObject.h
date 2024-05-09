/**
 * @file LightSrcObject.h
 * @author Elijah Gleckler
 *
 * GameObject that has a light source, like a torch
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_LIGHTSRCOBJECT_H
#define LEARNING_OPENGL_GAMELIB_SRC_LIGHTSRCOBJECT_H

#include <memory>
#include "GameObject.h"

class LightSource;
/**
 *  * GameObject that has a light source, like a torch
 */
class LightSrcObject : public GameObject
{
private:

    /// Light source object associated with this GameObject
    LightSource* mLightSource = nullptr;

public:

    /**
     * Constructor
     * @param renderData Data for object model
     * @param hitbox Hitbox
     * @param lightSrc Pointer to the light source
     */
    LightSrcObject(std::unique_ptr<RenderObject> renderData,
                   glm::vec3 position, glm::vec3 hitbox,
                   std::pair<float, glm::vec3> rotation,
                   std::unique_ptr<LightSource> lightSrc)
                   :
                   GameObject(std::move(renderData), position, hitbox, rotation)
                   {
                        // Unpack the unique_ptr and take the raw ptr
                        mLightSource = std::move(lightSrc).get();
                        // The unique_ptr is moved to the constructor and
                        // destroyed when it then falls out of scope.
                   }

    /// Default constructor (disabled)
    LightSrcObject() = delete;

    /// Copy constructor (disabled)
    LightSrcObject(const LightSrcObject &) = delete;

    /// Assignment operator
    void operator=(const LightSrcObject &) = delete;

    // ****************************************************************

    /**
     * Get a pointer to the light source. Make a copy of the member ptr
     *
     * Maybe I could make this more airtight (against nullptr) later...
     *
     * @return Pointer to this object's light source
     */
    LightSource* GetLightSource() { return mLightSource; }



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_LIGHTSRCOBJECT_H
