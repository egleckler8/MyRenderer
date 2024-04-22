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







    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    float vertices2[] = {
            -0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,1.0f,
            -0.8f,0.2f,0.0f, 0.0f, 1.0f, 0.0f,1.0f,0.0f,
            -0.8f,0.8f,0.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f
    };

    unsigned int indices[] = {
        0,1,3, // first triangle
        1,2,3 // second triangle
    };







    // Create the objects we'll need to draw
    // Vertex buffer object to hold our vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Create a vertex array object
    // to help OpenGL intepret data from our vertices
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Create an element buffer object
    // To help draw our rectangle efficiently using indices
    unsigned int EBO;
    glGenBuffers(1, &EBO);


    unsigned int VBO2;
    glGenBuffers(1, &VBO2);

    // Create a vertex array object
    // to help OpenGL intepret data from our vertices
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);



    // Initialization code
    // Bind vertex array object
    glBindVertexArray(VAO);
    // Copy the vertices array into a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Copy our index array in an element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);
    // then, set the vertex attribute pointers...
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture 1 attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Initialization code
    // Bind vertex array object
    glBindVertexArray(VAO2);
    // Copy the vertices array into a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // then, set the vertex attribute pointers...
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);





    // ************************************
    //      Textures or something
    // ************************************
    Texture2D lavalampTex("lavalamp", "textures/lavalamp.jpg", GL_RGB, 0);
    Texture2D containerTex("container", "textures/container.jpg", GL_RGB, 0);
    Texture2D faceTex("face", "textures/awesomeface.png", GL_RGBA, 1);




    // ************************************
    //      Shaders or something
    // ************************************
    Shader shaderProgram1("Textured", "shaders/v-shader-1", "shaders/f-shader-1");
    Shader shaderProgram2("Basic green", "shaders/v-shader-2", "shaders/f-shader-2");
    Shader shaderProgramMvmt("Mvmt and lighting", "shaders/v-shader-mvmt", "shaders/f-shader-lighting");
    Shader shaders3D("3d", "shaders/v-shader-3", "shaders/f-shader-3");



    // attach textures to shaders?
    // tell the shader program which sampler uniform belongs to which texture unit
    shaders3D.use();
    shaders3D.setIntUniform("texture1", 0);
    shaders3D.setIntUniform("texture2", 1);



    // This will set the light position
    float lightPos[] = {-0.5f, 0.5f, 0.0f};
    shaderProgramMvmt.set3FUniform("lightPos", lightPos);


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


    // THE CAMERA - building a relative coordinate space?

    // We can choose the position...
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -6.0f);

    // It should be pointing at the origin
    glm::vec3 cameraTarget = glm::vec3(0.0f,0.0,0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    // L/R axis
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    // Up/Down axis
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));



    // ********************************
    //          Render loop!
    // ********************************
    while(!glfwWindowShouldClose(window))
    {

        float t = (float)glfwGetTime();

        // Check for key presses?
        camera.Update();

        // Rendering commands:
        glClearColor(0.4f, 0.8f, 0.95f, 1.0f); // state-setting
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // state-using


        // Double texture?
        glActiveTexture(GL_TEXTURE0);
        lavalampTex.use();
        glActiveTexture(GL_TEXTURE1);
        faceTex.use();


        //
        // GOING 3D!!
        //

        // Create our model matrix to put our local coords into world coords
        glm::mat4 modelMat = glm::mat4(1.0f);
        // rotate a little so it's a floor?
        modelMat = glm::rotate(modelMat, glm::radians(-70.0f), glm::vec3(1.0,0.0,0.0));

        // Create our view matrix to move the world into camera space
        // and we gonna spin...
        glm::mat4 viewMat = camera.GetViewMatrix();



        // Projection matrix moves camera space into clip space
        // we'll use a perspective projection matrix so farther things are smaller (real)
        // params are: 1. FoV, 2. aspect ratio, 3. near plane, 4. far plane
        // We usually only do this OUTSIDE of the render loop since the
        // projection matrix usually never changes
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        modelMat = glm::rotate(modelMat, t * glm::radians(50.0f),
                               glm::vec3(0.5f, 1.0f, 0.0f));


        // cubes shaders
        shaders3D.use();
        shaders3D.setMat4FUniform("model", modelMat);
        shaders3D.setMat4FUniform("view", viewMat);
        shaders3D.setMat4FUniform("projection", projMat);

        glBindVertexArray(VAO);


        // Draw HELLA CUBES
        for(int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0,0.0,2) + cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle) + t * i * glm::radians(50.0f), glm::vec3(1.0,0.3,0.5));
            shaders3D.setMat4FUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }


        glBindVertexArray(0);

//        // SMALL ZESTY TRIANGLE
//        shaderProgram2.use();
//
//        // Rotate over time...
//        glm::mat4 trans = glm::mat4(1.0f);
//        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));
//        trans = glm::scale(trans, glm::vec3(sin((float)glfwGetTime()),1.0f,0.0f));
//
//        shaderProgram2.setMat4FUniform("transform", trans);
//
//        containerTex.use();
//
//        // Redner the upper right triangle
//        glBindVertexArray(VAO2);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glBindVertexArray(0);




        // Swap buffers--read up on double-buffering (why we don't see flickering)
        glfwSwapBuffers(window);

    }




    // Clear all the resources used by GLFW before we end
    glfwTerminate();
    return 0;

}