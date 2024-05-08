#include <iostream>
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <GraphicsLib/api.h>

const int SCREEN_WIDTH = 1000; ///< Chosen by me
const int SCREEN_HEIGHT = 800; ///< Chosen by me


int main()
{

    // Create window manager...
    WindowManager window(SCREEN_WIDTH, SCREEN_HEIGHT);


    // Get THE camera
    auto camera = window.GetCamera();


    // Create a render data thingy
    RenderObjectFactory objectFactory("../resources");
    auto backpack = objectFactory.Create("../resources/models/backpack/backpack.obj",
                                         "../resources/shaders/v4.vert",
                                         "../resources/shaders/f4.frag");
    // make it face towards use when we spawn:
    backpack.SetScale(glm::vec3(1.0f, 1.0f, -1.0f));

    // A directional light source
    glm::vec3 lightDir(0.5f, -1.0f, 0.0f);
    glm::vec3 sunAmbient(0.1f);
    glm::vec3 sunDiffuse(0.5f);
    glm::vec3 sunSpecular(1.0f);
    auto sunColors = std::make_shared<PhongColors>(sunAmbient, sunDiffuse, sunSpecular);
    DirectionalLight theSun(lightDir, sunColors);

    auto attenCoeffs = std::make_shared<AttenuationCoefficients>(1.0, 0.09, 0.032);

    PointLight tester(sunColors, attenCoeffs);
    tester.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    // Create a scene and add everything
    Scene scene;
    scene.AddEntity(&backpack);
    scene.AddLightSource(&theSun);
    scene.AddLightSource(&tester);
    tester.SetPosition(glm::vec3(1.0f, 0.5f, 0.5f));

    while(true)
    {
        float t = glfwGetTime();

        glm::vec3 pos(3.0*sin(t), 0.0, 3.0*cos(t));
        glm::vec3 axis(1.0f, 0.0f, 0.0f);
        float angle = glm::radians(t * 50.0);
        float scale = sin(t);
        backpack.SetPosition(pos);
        backpack.SetRotation(angle, axis);
        //backpack.SetScale(scale);

        window.DisplayScene(scene);
    }


    return 0;


}