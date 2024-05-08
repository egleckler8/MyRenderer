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
    std::unique_ptr<LightSource> mLightSource = nullptr;

public:

    /**
     * Constructor
     * @param renderData Data for object model
     * @param hitbox Hitbox
     * @param lightSrc Pointer to the light source
     */
    LightSrcObject(std::unique_ptr<RenderObject> renderData, glm::vec3 hitbox,
                    std::unique_ptr<LightSource> lightSrc)
                    : GameObject(std::move(renderData), hitbox), mLightSource(std::move(lightSrc)) {}

    /// Default constructor (disabled)
    LightSrcObject() = delete;

    /// Copy constructor (disabled)
    LightSrcObject(const LightSrcObject &) = delete;

    /// Assignment operator
    void operator=(const LightSrcObject &) = delete;

    // ****************************************************************

    /**
     * Get a pointer to the light source. Don't want to share
     * this pointer or move it out, so just hand over the
     * raw pointer.
     *
     * Maybe I could make this more airtight (against nullptr) later...
     *
     * @return Pointer to this object's light source
     */
    LightSource* GetLightSource() { return mLightSource.get(); }



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_LIGHTSRCOBJECT_H
