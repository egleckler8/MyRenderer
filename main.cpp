#include <iostream>
#include <fstream>
#include "glm.hpp"
#include "GLFW/glfw3.h"
#include "nlohmann/json.hpp"

#include "GraphicsLib/api.h"
#include <GameLib/api.h>





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

    std::ifstream fObj("../resources/json/backpack.json");
    auto data = json::parse(fObj);
    auto backpack = objectFactory.CreateFromJson(data);
    // make it face towards use when we spawn:
    backpack->SetScale(glm::vec3(1.0f, 1.0f, -1.0f));



    LightSourceFactory lightFactory;
    std::ifstream fLight1("../resources/json/sun.json");
    auto data1 = json::parse(fLight1);
    auto theSun = lightFactory.CreateFromJson(data1);

    std::ifstream fLight2("../resources/json/tester.json");
    auto data2 = json::parse(fLight2);
    auto tester = lightFactory.CreateFromJson(data2);


    //tester.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    // Create a scene and add everything
    Scene scene;
    scene.AddRenderObject(backpack);
    scene.AddLightSource(theSun);
    scene.AddLightSource(tester);
    // tester->SetPosition(glm::vec3(1.0f, 0.5f, 0.5f));

    while(true)
    {
        float t = glfwGetTime();

        glm::vec3 pos(3.0*sin(t), 0.0, 3.0*cos(t));
        glm::vec3 axis(1.0f, 0.0f, 0.0f);
        float angle = glm::radians(t * 50.0);
        float scale = sin(t);
        backpack->SetPosition(pos);
        // backpack->SetRotation(angle, axis);
        //backpack.SetScale(scale);

        window.DisplayScene(scene);
    }


    return 0;


}