#include <iostream>
#include <fstream>
#include <random>
#include "GLFW/glfw3.h"
#include "nlohmann/json.hpp"

#include <GraphicsLib/api.h>
#include <GameLib/api.h>



const int SCREEN_WIDTH = 1600; ///< Chosen by me
const int SCREEN_HEIGHT = 900; ///< Chosen by me


std::vector<std::unique_ptr<PointLight>>
    GetManyPtLights(Scene& scene, int num, float max_radius);


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


    // Sunlight?
    std::ifstream fLight1("../resources/json/sun.json");
    auto data1 = json::parse(fLight1);
    auto theSun = lightFactory.CreateDirectionalLight(data1.at("data"));
    //scene.SetDirectionalLight(theSun.get());



     // Testing the behavior thing
     // ugly way of getting the backpack...
     auto& backpack = objects[1];
     auto testBhvr = std::make_unique<TestBehavior>(backpack.get());
     backpack->SetBehavior(std::move(testBhvr));


    // It's wayyyy too big....
    auto& sponza = objects[2];
    sponza->GetRenderData()->SetScale(glm::vec3(0.05));


    // Skybox?? (not working rn...)
    Skybox skybox("../resources/textures/skybox");
    scene.SetSkybox(&skybox);


    // Set up pipeline by telling it the window to render to
    GBuffer gbuffer(window);

    // Camera initial position
    auto cam = window.GetCamera();
    cam->SetPosition(glm::vec3(0.0, 3.0, 0.0));




    // Let's add a bunch of random point lights:
    auto ptLights = GetManyPtLights(scene, 1, 100.0);
    for (auto& light : ptLights)
    {
        scene.AddPointLight(light.get());
    }


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

    }


    return 0;


}




/**
 * Add a bunch of point lights to the scene for fun.
 * All centered around 0,0 in random spherical coords,
 * but only the dome ya dig
 * @param scene scene to add to
 */
std::vector<std::unique_ptr<PointLight>>
    GetManyPtLights(Scene& scene, int num, float max_radius)
{

    std::vector<std::unique_ptr<PointLight>> stuff;

    // Randomness:
    std::random_device randDev;
    std::mt19937  gen(randDev());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    // All the same attenuation
    AttenuationCoefficients attenCoeffs;
    attenCoeffs.constant = 1.0;
    attenCoeffs.linear = 0.09;
    attenCoeffs.quadratic = 0.032;

    for(int i = 0; i < num; ++i)
    {
        // Random colors
        glm::vec3 albedo(dist(gen), dist(gen), dist(gen));
        glm::vec3 spec(dist(gen));
        PhongColors phongColors;
        phongColors.ambient = glm::vec3(0.25) * albedo;
        phongColors.diffuse = glm::vec3(0.6) * albedo;
        phongColors.specular = spec;

        // Random position (spherical coords?)
        float r = max_radius * dist(gen);
        float theta = 2.0 * M_PI * dist(gen);
        float phi = M_PI_2 * dist(gen);

        // Convert to normal
        float x = r * sin(phi) * cos(theta);
        float y = r * cos(phi);
        float z = r * sin(phi) * sin(theta);

        glm::vec3 pos(x, y, z); // weird coords, ugh
        std::cout << "Light at: (" << x << ',' << y << ',' << z << ')' << std::endl;

        // Make a point light & set the pos
        auto ptLight = std::make_unique<PointLight>(phongColors, attenCoeffs);
        ptLight->SetPosition(pos);

        stuff.push_back(std::move(ptLight));

    }
    return stuff;
}