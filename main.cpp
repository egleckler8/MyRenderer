#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
 * "Be sure to include GLAD before GLFW. The include file for GLAD includes
 * the required OpenGL headers behind the scenes (like GL/gl.h) so be sure
 * to include GLAD before other header files that require OpenGL (like GLFW)."
 */

// Just to stay organized
#include "MyFunctions.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture2D.h"
#include "LightSource.h"
#include "PointLight.h"
#include "lighting_structs.h"






int main()
{


    // Instantiate the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // "Note that on Mac OS X you need to add <below line> to your initialization code for it to work."
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



    // Next, we're required to create a window object
    GLFWwindow* window = glfwCreateWindow(800,800,"LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Bind the window resize to it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // "In the previous chapter we mentioned that GLAD manages function pointers
    // for OpenGL, so we want to initialize GLAD before we call any OpenGL function:"
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialized GLAD" << std::endl;
        return -1;
    }



    // Tell OpenGL the size of the rendering window
    glViewport(0, 0, 800, 600);
    /*
     * "We could actually set the viewport dimensions at values smaller than
     * GLFW’s dimensions; then all the OpenGL rendering would be displayed in
     * a smaller window, and we could for example display other elements outside
     * the OpenGL viewport."
     *
     * ^^ Adding widgets stuff on the side?
     */

    // Do this before the render loop to set the correct size??
    int fbSizeX, fbSizeY;
    glfwGetFramebufferSize(window, &fbSizeX, &fbSizeY);
    glViewport(0, 0, fbSizeX, fbSizeY);
    // Damn! It worked, nice. It was from here:
    // https://stackoverflow.com/questions/76541033/why-is-my-triangles-been-drawn-in-left-bottom-side-of-the-window







    float cubeVertices[] = {
        // positions                        // normals                      // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };









    // Create the objects we'll need to draw
    // Vertex buffer object to hold our vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Create a vertex array object
    // to help OpenGL interpret data from our cubeVertices
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Create an element buffer object
    // To help draw our rectangle efficiently using indices
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);




    // THE CONTAINER CUBE:
    // Bind vertex array object
    glBindVertexArray(VAO);
    // Copy the cubeVertices array into a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // Copy our index array in an element buffer for OpenGL to use
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);
    // then, set the vertex attribute pointers...
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal vectors attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture 1 attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // THE LIGHT CUBE:
    // Model stuff
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);





    // ************************************
    //      Textures or something
    // ************************************
//    Texture2D lavalampTex("lavalamp", "textures/lavalamp.jpg", GL_RGB, 0);
//    Texture2D containerTex("container", "textures/container.jpg", GL_RGB, 0);
//    Texture2D faceTex("face", "textures/awesomeface.png", GL_RGBA, 1);
    Texture2D diffuseMap("container2-diff", "textures/container2.png", GL_RGBA, false);
    Texture2D specularMap("container2-spec", "textures/container2_specular.png", GL_RGBA, false);





    // ************************************
    //      Shaders or something
    // ************************************
    Shader shaders3D("3d", "shaders/v-shader-3", "shaders/f-shader-3");
    Shader lightSrcShader("lighting", "shaders/v-lightsrc-1", "shaders/f-lightsrc-1");
    auto shader4 = std::make_shared<Shader>("version 4", "shaders/v4.vert", "shaders/f4.frag");



    // World stuff
    glm::vec3 lightPos(2.0f, 1.5f, -2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    /*
     * colors can basically be represented as an RGB vector of
     * how much light of each R,G,B that the object reflects
     *
     * so, we can deadass just multiply a lighting vector with an
     * object/pixel's "true color" vector to get the color in the lighting...
     *
     *
     *
     */



    // attach textures to shaders?
    // tell the shader program which sampler uniform belongs to which texture unit
//    shader4.use();
//    shader4.setIntUniform("texture1", 0);
//    shader4.setIntUniform("texture2", 1);






    // Create an input handler
    Camera camera(window, glm::vec3(0.0f,0.0f,-6.0f));



    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,   0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f,  -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f,  -3.5f),
        glm::vec3(-1.7f,  3.0f,  -7.5f),
        glm::vec3( 1.3f, -2.0f,  -2.5f),
        glm::vec3( 1.5f,  2.0f,  -2.5f),
        glm::vec3( 1.5f,  0.2f,  -1.5f),
        glm::vec3(-1.3f,  1.0f,  -1.5f)
    };



    // Let's try out my new LightSource object!

    // Its Phong stuff
    glm::vec3 ambient(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
    glm::vec3 specular(1.0f, 1.0f, 1.0f);
    auto phongColors = std::make_shared<PhongColors>(ambient, diffuse, specular);

    // Its attenuation stuff
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    auto attenCoeffs = std::make_shared<AttenuationCoefficients>(constant, linear, quadratic);

    PointLight cubeLight = PointLight(phongColors, attenCoeffs, shader4);





    // bruh
    glEnable(GL_DEPTH_TEST);

    // ********************************
    //          Render loop!
    // ********************************
    while(!glfwWindowShouldClose(window))
    {

        auto t = (float)glfwGetTime();

        // Check for key presses?
        camera.Update();

        // Rendering commands:
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // state-setting
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // state-using


        glm::mat4 modelMat = glm::mat4(1.0f);
        glm::mat4 viewMat = camera.GetViewMatrix();
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Compute the normal mat on the cpu since the inversion operation
        // is expensive in GLSL on the GPU
        // NOTE:
        // Make sure the normal mat is in view space
        // We can do our lighting in view space!
        glm::mat4 modelViewMat = viewMat * modelMat;
        glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelViewMat)));

        // cube textures
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.use();
        glActiveTexture(GL_TEXTURE1);
        specularMap.use();

        // cubes shaders
        shader4->use();

        // Material properties
        shader4->setIntUniform("material.diffuse", 0);
        shader4->setIntUniform("material.specular", 1);
        shader4->set1FUniform("material.shininess", 32.0f);

        // Light properties (there are a lot...)
        lightPos = glm::vec3(0.0, 1.0f, -3 - 5*cos(0.5 *t));
        cubeLight.SetPosition(lightPos);
        cubeLight.SetUniforms();

        // yeah
        shader4->setMat4Uniform("viewMat", viewMat);
        shader4->setMat4Uniform("projMat", projMat);
        shader4->setMat3Uniform("normalMat", normalMat);
        glBindVertexArray(VAO);
        for (int i = 0; i < 10; ++i)
        {
            glm::mat4 modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, cubePositions[i]);
            float angle = 20.0f * i;
            modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader4->setMat4Uniform("modelMat", modelMat);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glBindVertexArray(0);



        // Render the light cube
        lightSrcShader.use();

        glm::mat4 lightModel = glm::mat4 (1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lightSrcShader.setMat4Uniform("model", lightModel);
        lightSrcShader.setMat4Uniform("view", viewMat);
        lightSrcShader.setMat4Uniform("projection", projMat);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 36);






        // Swap buffers--read up on double-buffering (why we don't see flickering)
        glfwSwapBuffers(window);

    }




    // Clear all the resources used by GLFW before we end
    glfwTerminate();
    return 0;

}