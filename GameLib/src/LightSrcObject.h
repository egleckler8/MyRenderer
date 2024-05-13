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

class PointLight;
/**
 *  * GameObject that has a light source, like a torch
 */
class LightSrcObject : public GameObject
{
private:

    /// Light source object associated with this GameObject
    std::unique_ptr<PointLight> mLightSource;

public:

    LightSrcObject(std::unique_ptr<RenderObject> renderData,
                   glm::vec3 position, glm::vec3 hitbox,
                   std::pair<float, glm::vec3> rotation,
                   std::unique_ptr<PointLight> lightSrc);

    /// Default constructor (disabled)
    LightSrcObject() = delete;

    /// Copy constructor (disabled)
    LightSrcObject(const LightSrcObject &) = delete;

    /// Assignment operator
    void operator=(const LightSrcObject &) = delete;

    // ****************************************************************

    void AcceptVisitor(GameObjectVisitor& visitor) override;

    // ****************************************************************

    /**
     * Get a pointer to the light source. Make a copy of the member ptr
     *
     * Maybe I could make this more airtight (against nullptr) later...
     *
     * @return Pointer to this object's light source
     */
    PointLight* GetLightSource() { return mLightSource.get(); }


    void SetPosition(glm::vec3 pos) override;



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_LIGHTSRCOBJECT_H
