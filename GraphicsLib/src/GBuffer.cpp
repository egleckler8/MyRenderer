/**
 * @file GBuffer.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <glad/glad.h>
#include "GBuffer.h"


/// Hard-coded filepath to the g-buffer vertex shader.
const std::string GBUF_VERT_SHADER_FILEPATH = "../../resources/shaders/gbuf.vert";

/// Hard-coded filepath to the g-buffer fragment shader.
const std::string GBUF_FRAG_SHADER_FILEPATH = "../../resources/shaders/gbuf.frag";



/**
 * Constructor
 * @param width width of the framebuffer in pixels
 * @param height height of the framebuffer in pixels
 */
GBuffer::GBuffer(int width, int height)
{

    glGenFramebuffers(1, &mGBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);

    // We'll use position, normal, and diffuse/specular color maps
    unsigned int positionBuf, normalBuf, diffSpecBuf;

    // Check out how we use GL_RGBA16F as the internal format for
    // the position and normal color buffers--we need high precision!

    // Position color buffer
    glGenTextures(1, &positionBuf);
    glBindTexture(GL_TEXTURE_2D, positionBuf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionBuf, 0);


    // Normal color buffer
    glGenTextures(1, &normalBuf);
    glBindTexture(GL_TEXTURE_2D, normalBuf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalBuf, 0);

    // Diffuse/albedo & specular color buff
    // The RGB part is the diffuse/albedo color and
    // the A part is the specular intensity!
    glGenTextures(1, &diffSpecBuf);
    glBindTexture(GL_TEXTURE_2D, diffSpecBuf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, diffSpecBuf, 0);

    // Tell OpenGL which attachments we'll use
    unsigned int attachments[3] = {
        GL_COLOR_ATTACHMENT0, // position
        GL_COLOR_ATTACHMENT1, // normal
        GL_COLOR_ATTACHMENT2 // color (albedo + spec)
    };
    glDrawBuffers(3, attachments);



    // Depth and stencil buffers
    // Stored in a render buffer
    unsigned int renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // Attach it to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);



    // Make sure it's all good!
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" <<
                  std::endl;



    // "Be sure to unbind the framebuffer to make sure we’re
    // not accidentally rendering to the wrong framebuffer."
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // Initialize the screen-sized quad:


    // the geometry shaders

    // the lighting shaders

}
