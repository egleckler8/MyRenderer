#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    GLFWwindow* window = glfwCreateWindow(800,800,"LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Bind the window resize to it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // "In the previous chapter we mentioned that GLAD manages function pointers
    // for OpenGL so we want to initialize GLAD before we call any OpenGL function:"
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
     * a smaller window and we could for example display other elements outside
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
        // positions          // normals           // texture coords
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


    // making cylinder vertices
    // we basically just need a top and bottom circle
    // uhhhh texture coordinates will be weird so lets leave those out for now
    // (r*cos(theta), r*sin(theta), z) for position
    // wait normal is the same, i guess?
    int steps = 25; // number of steps our cylinder mock will take
    int arySize =(3 + 3) * steps * 2;
    float cylinderVertices[] =
    {
        0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,
        0.24869f,1.0f,0.968583f,0.24869f,0.0f,0.968583f,
        0.481754f,1.0f,0.876307f,0.481754f,0.0f,0.876307f,
        0.684547f,1.0f,0.728969f,0.684547f,0.0f,0.728969f,
        0.844328f,1.0f,0.535827f,0.844328f,0.0f,0.535827f,
        0.951057f,1.0f,0.309017f,0.951057f,0.0f,0.309017f,
        0.998027f,1.0f,0.0627905f,0.998027f,0.0f,0.0627905f,
        0.982287f,1.0f,-0.187381f,0.982287f,0.0f,-0.187381f,
        0.904827f,1.0f,-0.425779f,0.904827f,0.0f,-0.425779f,
        0.770513f,1.0f,-0.637424f,0.770513f,0.0f,-0.637424f,
        0.587785f,1.0f,-0.809017f,0.587785f,0.0f,-0.809017f,
        0.368125f,1.0f,-0.929776f,0.368125f,0.0f,-0.929776f,
        0.125333f,1.0f,-0.992115f,0.125333f,0.0f,-0.992115f,
        -0.125333f,1.0f,-0.992115f,-0.125333f,0.0f,-0.992115f,
        -0.368125f,1.0f,-0.929776f,-0.368125f,0.0f,-0.929776f,
        -0.587785f,1.0f,-0.809017f,-0.587785f,0.0f,-0.809017f,
        -0.770513f,1.0f,-0.637424f,-0.770513f,0.0f,-0.637424f,
        -0.904827f,1.0f,-0.425779f,-0.904827f,0.0f,-0.425779f,
        -0.982287f,1.0f,-0.187381f,-0.982287f,0.0f,-0.187381f,
        -0.998027f,1.0f,0.0627906f,-0.998027f,0.0f,0.0627906f,
        -0.951056f,1.0f,0.309017f,-0.951056f,0.0f,0.309017f,
        -0.844328f,1.0f,0.535827f,-0.844328f,0.0f,0.535827f,
        -0.684547f,1.0f,0.728969f,-0.684547f,0.0f,0.728969f,
        -0.481754f,1.0f,0.876307f,-0.481754f,0.0f,0.876307f,
        -0.24869f,1.0f,0.968583f,-0.24869f,0.0f,0.968583f,
        0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,
        0.24869f,0.0f,0.968583f,0.24869f,0.0f,0.968583f,
        0.481754f,0.0f,0.876307f,0.481754f,0.0f,0.876307f,
        0.684547f,0.0f,0.728969f,0.684547f,0.0f,0.728969f,
        0.844328f,0.0f,0.535827f,0.844328f,0.0f,0.535827f,
        0.951057f,0.0f,0.309017f,0.951057f,0.0f,0.309017f,
        0.998027f,0.0f,0.0627905f,0.998027f,0.0f,0.0627905f,
        0.982287f,0.0f,-0.187381f,0.982287f,0.0f,-0.187381f,
        0.904827f,0.0f,-0.425779f,0.904827f,0.0f,-0.425779f,
        0.770513f,0.0f,-0.637424f,0.770513f,0.0f,-0.637424f,
        0.587785f,0.0f,-0.809017f,0.587785f,0.0f,-0.809017f,
        0.368125f,0.0f,-0.929776f,0.368125f,0.0f,-0.929776f,
        0.125333f,0.0f,-0.992115f,0.125333f,0.0f,-0.992115f,
        -0.125333f,0.0f,-0.992115f,-0.125333f,0.0f,-0.992115f,
        -0.368125f,0.0f,-0.929776f,-0.368125f,0.0f,-0.929776f,
        -0.587785f,0.0f,-0.809017f,-0.587785f,0.0f,-0.809017f,
        -0.770513f,0.0f,-0.637424f,-0.770513f,0.0f,-0.637424f,
        -0.904827f,0.0f,-0.425779f,-0.904827f,0.0f,-0.425779f,
        -0.982287f,0.0f,-0.187381f,-0.982287f,0.0f,-0.187381f,
        -0.998027f,0.0f,0.0627905f,-0.998027f,0.0f,0.0627905f,
        -0.951057f,0.0f,0.309017f,-0.951057f,0.0f,0.309017f,
        -0.844328f,0.0f,0.535827f,-0.844328f,0.0f,0.535827f,
        -0.684547f,0.0f,0.728969f,-0.684547f,0.0f,0.728969f,
        -0.481754f,0.0f,0.876307f,-0.481754f,0.0f,0.876307f,
        -0.24869f,0.0f,0.968583f,-0.24869f,0.0f,0.968583f,
    };


//    float topY = 1.0;
//    float bottomY = 0.0;
//    float radius = 1.0;
//    // top circle
//    for (int i = 0; i < steps; i++)
//    {
//        float theta = i * (2 * M_PI) / steps;
//
//        glm::vec3 yeah(radius * cos(theta), 0.0 , radius * sin(theta));
//        glm::vec3 yeahNorm(glm::normalize(yeah));
//
//        // let's just check the positions
//        std::cout   << radius * sin(theta) << "f,"
//                    << topY << "f,"
//                    << radius * cos(theta) << "f,"
//                    << yeahNorm.z << "f,"
//                    << "0.0f,"
//                    << yeahNorm.x << "f,"
//                    << std::endl;
//
//        cylinderVertices[i]     = (float)(radius * cos(theta));           // pos x
//        cylinderVertices[i + 1] = topY;           // pos y
//        cylinderVertices[i + 2] = (float)(radius * sin(theta));             // pos z
//        cylinderVertices[i + 3] = (float)yeahNorm.x;       // normal x
//        cylinderVertices[i + 4] = 0.0;              // normal y
//        cylinderVertices[i + 5] = (float)yeahNorm.z;       // normal z
//
//    }
//    // bottom circle
//    for (int i = 0; i < steps; i++)
//    {
//        double theta = i * (2 * M_PI) / steps;
//
//        glm::vec3 yeah(radius * cos(theta), 0.0 , radius * sin(theta));
//        glm::vec3 yeahNorm(glm::normalize(yeah));
//
//        // let's just check the positions
//        std::cout   << radius * sin(theta) << "f,"
//                    << bottomY << "f,"
//                    << radius * cos(theta) << "f,"
//                    << yeahNorm.z << "f,"
//                    << "0.0f,"
//                    << yeahNorm.x << "f,"
//                    << std::endl;
//
//        cylinderVertices[steps + i]     = (float)(radius * cos(theta));           // pos x
//        cylinderVertices[steps + i + 1] = bottomY; ;           // pos y
//        cylinderVertices[steps + i + 2] = (float)(radius * sin(theta));         // pos z
//        cylinderVertices[steps + i + 3] = (float)yeahNorm.x;       // normal x
//        cylinderVertices[steps + i + 4] = 0;            // normal y
//        cylinderVertices[steps + i + 5] = (float)yeahNorm.z;                // normal z
//
//    }







    // Create the objects we'll need to draw
    // Vertex buffer object to hold our vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Create a vertex array object
    // to help OpenGL intepret data from our cubeVertices
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


    // THE CYLINDER
    unsigned int VBOcyl;
    unsigned int VAOcyl;
    glGenBuffers(1, &VBOcyl);
    glGenVertexArrays(1, &VAOcyl);
    glBindVertexArray(VAOcyl);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcyl);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cylinderVertices), cylinderVertices, GL_STATIC_DRAW);
    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals attrib
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);









    // ************************************
    //      Textures or something
    // ************************************
    Texture2D lavalampTex("lavalamp", "textures/lavalamp.jpg", GL_RGB, 0);
    Texture2D containerTex("container", "textures/container.jpg", GL_RGB, 0);
    Texture2D faceTex("face", "textures/awesomeface.png", GL_RGBA, 1);




    // ************************************
    //      Shaders or something
    // ************************************
    Shader shaders3D("3d", "shaders/v-shader-3", "shaders/f-shader-3");
    Shader lightSrcShader("lighting", "shaders/v-lightsrc-1", "shaders/f-lightsrc-1");
    Shader shader4("version 4", "shaders/v4", "shaders/f4");



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



    // bruh
    glEnable(GL_DEPTH_TEST);



    // ********************************
    //          Render loop!
    // ********************************
    while(!glfwWindowShouldClose(window))
    {

        float t = (float)glfwGetTime();

        // Check for key presses?
        camera.Update();

        // Rendering commands:
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state-setting
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // state-using


        lightPos = glm::vec3(3*cos(t), 1.0f, 3*sin(t));

        // Create our model matrix to put our local coords into world coords
        glm::mat4 modelMat = glm::mat4(1.0f);
        // rotate a little so it's a floor?
        //modelMat = glm::rotate(modelMat, t * glm::radians(30.0f), glm::vec3(1.0,0.5,0.0));

        // Thank god for our camera class ;)
        glm::mat4 viewMat = camera.GetViewMatrix();

        // Projection matrix moves camera space into clip space
        // we'll use a perspective projection matrix so farther things are smaller (real)
        // params are: 1. FoV, 2. aspect ratio, 3. near plane, 4. far plane
        // We usually only do this OUTSIDE of the render loop since the
        // projection matrix usually never changes
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        // Compute the normal mat on the cpu since the inversion operation
        // is expensive in GLSL on the GPU
        // NOTE:
        // Make sure the normal mat is in view space
        // We can do our lighting in view space!
        glm::mat4 modelViewMat = viewMat * modelMat;
        glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelViewMat)));


        // Put the light position into view space
        // turn lightPos into a vec4, so we can translate it when we transform
        // it with the 4x4 viewmat. Important to keep the translation data!
        glm::vec3 lightPosView(viewMat * glm::vec4(lightPos, 1.0f));

        // cubes shaders
        shader4.use();
        shader4.setVec3Uniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shader4.setVec3Uniform("lightColor", lightColor);
        shader4.setVec3Uniform("lightPos", lightPosView);
        shader4.setMat4Uniform("modelViewMat", modelViewMat);
        shader4.setMat4Uniform("projMat", projMat);
        shader4.setMat3Uniform("normalMat", normalMat);

        // Double texture?
        glActiveTexture(GL_TEXTURE0);
        containerTex.use();
        glActiveTexture(GL_TEXTURE1);
        lavalampTex.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);



        // CYLINDER
        glm::mat4 modelMatCyl(1.0f);
        glm::vec3 cylPos(3.0f, 0.0f, 0.0f);
        modelMatCyl = glm::translate(modelMatCyl, cylPos);
        glm::mat4 modelViewMatCyl = viewMat * modelMatCyl;
        glm::mat3 normalMatCyl = glm::mat3(glm::transpose(glm::inverse(modelViewMatCyl)));

        shader4.use();
        shader4.setVec3Uniform("objectColor", glm::vec3(0.3f, 0.9f, 0.2f));
        shader4.setVec3Uniform("lightColor", lightColor);
        shader4.setVec3Uniform("lightPos", lightPosView);
        shader4.setMat4Uniform("modelViewMat", modelViewMatCyl);
        shader4.setMat4Uniform("projMat", projMat);
        shader4.setMat3Uniform("normalMat", normalMatCyl);

        glBindVertexArray(VAOcyl);
        glDrawArrays(GL_TRIANGLES, 0, 50);
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