#include <iostream>
#include <fstream>
#include "GLFW/glfw3.h"
#include "nlohmann/json.hpp"

#include <GraphicsLib/api.h>
#include <GameLib/api.h>



const int SCREEN_WIDTH = 1000; ///< Chosen by me
const int SCREEN_HEIGHT = 800; ///< Chosen by me


int main()
{

    // Create window manager...
    WindowManager window(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::ifstream f("../resources/json/yeah.json");
    auto data = json::parse(f);


    // Create a render data thingy
    RenderObjectFactory objectFactory("../resources");
    LightSourceFactory lightFactory;

    GameObjectLoader loader(objectFactory, lightFactory);
    auto objects = loader.LoadObjects(data);

    Scene scene;
    SceneBuilderVisitor sbv(scene);

    for (auto& object : objects)
    {
        object->AcceptVisitor(sbv);
    }


    std::ifstream fLight1("../resources/json/sun.json");
    auto data1 = json::parse(fLight1);
    auto theSun = lightFactory.CreateDirectionalLight(data1.at("data"));

    scene.SetDirectionalLight(theSun.get());



    // Testing the behavior thing
    // ugly way of getting the backpack...
    auto& backpack = objects[1];

    auto testBhvr = std::make_unique<TestBehavior>(backpack.get());

    backpack->SetBehavior(std::move(testBhvr));




    // Skybox??
    Skybox skybox("../resources/textures/skybox");

    scene.SetSkybox(&skybox);


    GBuffer gbuffer(window);

    // Camera initial position
    auto cam = window.GetCamera();
    cam->SetPosition(glm::vec3(0.0, 1.0, 0.0));

    while(true)
    {
        double t = glfwGetTime();

        for (auto& object : objects)
        {
            object->Update(t);
        }

        // This does the glfw stuff
        window.UpdateWindow();
        // Render...
        gbuffer.RenderScene(scene);

        // Oh, god...
        // glfwSwapBuffers(window.GetWindow());

    }


    return 0;


}