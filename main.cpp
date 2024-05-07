#include <iostream>
#include <GraphicsLib/api.h>

const int SCREEN_WIDTH = 1000; ///< Chosen by me
const int SCREEN_HEIGHT = 800; ///< Chosen by me


int main()
{

    // Create window manager...
    WindowManager window(SCREEN_WIDTH, SCREEN_HEIGHT);


    // Create a camera
    auto camera = std::make_shared<Camera>(window.GetWindow());


    // Create a render data thingy
    auto backpackModel = std::make_shared<Model>("../resources/models/backpack/backpack.obj");
    auto backpackShaders = std::make_shared<Shader>("backpackShaders", "../resources/shaders/v4.vert", "../resources/shaders/f4.frag");
    RenderData backpackData(backpackModel, backpackShaders);


    // A directional light source
    glm::vec3 lightDir(0.3f, -1.0f, 0.0f);
    glm::vec3 sunAmbient(0.5f, 0.5f, 0.5f);
    glm::vec3 sunDiffuse(0.5f, 0.5f, 0.5f);
    glm::vec3 sunSpecular(1.0f, 1.0f, 1.0f);
    auto sunColors = std::make_shared<PhongColors>(sunAmbient, sunDiffuse, sunSpecular);
    DirectionalLight theSun(lightDir, sunColors);


    // Create a scene and add everything
    Scene scene;
    scene.AddEntity(&backpackData);
    scene.AddLightSource(&theSun);

    while(true)
    {
        window.DisplayScene(scene);
    }


    return 0;


}