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


//    // Create a render data thingy
//    RenderObjectFactory objectFactory("../resources");
//
//    std::ifstream fObj("../resources/json/backpack.json");
//    auto data = json::parse(fObj);
//    auto backpack = objectFactory.CreateFromJson(data);
//    // make it face towards use when we spawn:
//    backpack->SetScale(glm::vec3(1.0f, 1.0f, -1.0f));
//
//    // ROOM????
//    std::ifstream fFloor("../resources/json/floor.json");
//    auto floorData = json::parse(fFloor);
//    auto floor = objectFactory.CreateFromJson(floorData);
//
//    std::ifstream fLant("../resources/json/lantern.json");
//    auto lanternData = json::parse(fLant);
//    auto lantern = objectFactory.CreateFromJson(lanternData);
//    lantern->SetPosition(glm::vec3(4.0f, 4.0f, 4.0f));
//
//
//
//
//
//    std::ifstream fLight2("../resources/json/tester.json");
//    auto data2 = json::parse(fLight2);
//    auto tester = lightFactory.CreateFromJson(data2);
//
//
//    //tester.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
//
//    // Create a scene and add everything
//    Scene scene;
//    scene.AddRenderObject(backpack.get());
//    scene.AddLightSource(theSun.get());
//    scene.AddLightSource(tester.get());
//    scene.AddRenderObject(floor.get());
//    scene.AddRenderObject(lantern.get());
//    // tester->SetPosition(glm::vec3(1.0f, 0.5f, 0.5f));

    std::ifstream f("../resources/json/yeah.json");
    auto data = json::parse(f);


    // Create a render data thingy
    RenderObjectFactory objectFactory("../resources");
    LightSourceFactory lightFactory;

    GameObjectLoader loader(objectFactory, lightFactory);
    auto objects = loader.LoadObjects(data);

    Scene scene;
    SceneBuilderVisitor sbv(&scene);

    for (auto& object : objects)
    {
        object->AcceptVisitor(sbv);
    }


    std::ifstream fLight1("../resources/json/sun.json");
    auto data1 = json::parse(fLight1);
    auto theSun = lightFactory.CreateFromJson(data1);

    scene.AddLightSource(theSun.get());


    while(true)
    {
//        float t = glfwGetTime();
//
//        glm::vec3 pos(3.0*sin(0.5*t), 4.0, 4.0);
//        glm::vec3 axis(0.0f, 1.0f, 0.0f);
//        float angle = glm::radians(t * 10.0);
//        float scale = (sin(0.2 * t) + 1.5) * 0.5;
//        //lantern->SetPosition(pos);
//        lantern->SetRotation(angle, axis);
//        //backpack->SetScale(scale);


        window.DisplayScene(scene);
    }


    return 0;


}