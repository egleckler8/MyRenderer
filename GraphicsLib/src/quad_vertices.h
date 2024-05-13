/**
 * @file quad_vertices.h
 * @author Elijah Gleckler
 *
 * When compiles constants for quad
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_VERTICES_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_VERTICES_H

/// Vertices for a 2D quad - winded counterclockwise
constexpr float SQUARE_VERTICES[] = {
    // Position            // Normal           // Texture coords
    -1.0f,  1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,   // Top-left
    1.0f,  1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,   // Top-right
    -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,   // Bottom-left
    1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f    // Bottom-right
};
/// Indices for a 2D quad - winded counterclockwise
constexpr unsigned int SQUARE_INDICES[] = {
    0, 1, 2,
    1, 3, 2
};

/// Vertices for a 3D - winded counterclockwise
constexpr float CUBE_VERTICES[] = {
    // Position            // Normal           // Texture coords
    // Front face
    -1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
    1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
    1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
    -1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
    // Back face
    -1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,  // Bottom-right
    1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,  // Bottom-left
    1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,  // Top-left
    -1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,  // Top-right
    // Left face
    -1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Top-right
    -1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Top-left
    -1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Bottom-left
    -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Bottom-right
    // Right face
    1.0f,  1.0f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Top-left
    1.0f,  1.0f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Top-right
    1.0f, -1.0f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Bottom-right
    1.0f, -1.0f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Bottom-left
    // Top face
    -1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
    1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
    -1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
    // Bottom face
    -1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
    1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
    -1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f   // Bottom-left
};
/// Indices for a 3D quad - winded counterclockwise
constexpr float CUBE_INDICES[] = {
    0, 1, 2, 2, 3, 0,    // Front face
    4, 5, 6, 6, 7, 4,    // Back face
    8, 9, 10, 10, 11, 8, // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};


/// Since the base constructor must be called from initializer list...
std::vector<Vertex> SquareVertices()
{
    // Put the array vertices into a vector...
    // Must remain compatible with Mesh.
    std::vector<Vertex> vertices;

    // Total vertices: 32, total rows: 8 (stride)
    for (int i = 0 ; i < 32; i += 8)
    {
        Vertex vertex;
        // First three are the position
        glm::vec3 position(SQUARE_VERTICES[i], SQUARE_VERTICES[i + 1], SQUARE_VERTICES[i + 2]);
        // Next comes the normal
        glm::vec3 normal(SQUARE_VERTICES[i + 3], SQUARE_VERTICES[i + 4], SQUARE_VERTICES[i + 5]);
        // Last two are tex coords
        glm::vec2 texCoords(SQUARE_VERTICES[i + 6], SQUARE_VERTICES[i + 7]);

        // Fill up the vertex and push it to the vertices
        vertex.position = position;
        vertex.normal = normal;
        vertex.texCoords = texCoords;

        vertices.push_back(vertex);
    }

    return vertices;
}

/// Since the base constructor must be called from initializer list...
std::vector<unsigned int> SquareIndices()
{
    // Do the same with indices, but this is simpler
    std::vector<unsigned int> indices;

    for (int i = 0; i < 6; ++i)
    {
        indices.push_back(SQUARE_INDICES[i]);
    }

    return indices;
}

/// Since the base constructor must be called from initializer list...
std::vector<Vertex> CubeVertices()
{
    // Put the array vertices into a vector...
    // Must remain compatible with Mesh.
    std::vector<Vertex> vertices;

    // Total vertices: 32, total rows: 8 (stride)
    for (int i = 0 ; i < 192; i += 8)
    {
        Vertex vertex;
        // First three are the position
        glm::vec3 position(SQUARE_VERTICES[i], SQUARE_VERTICES[i + 1], SQUARE_VERTICES[i + 2]);
        // Next comes the normal
        glm::vec3 normal(SQUARE_VERTICES[i + 3], SQUARE_VERTICES[i + 4], SQUARE_VERTICES[i + 5]);
        // Last two are tex coords
        glm::vec2 texCoords(SQUARE_VERTICES[i + 6], SQUARE_VERTICES[i + 7]);

        // Fill up the vertex and push it to the vertices
        vertex.position = position;
        vertex.normal = normal;
        vertex.texCoords = texCoords;

        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<unsigned int> CubeIndices()
{
    // Do the same with indices, but this is simpler
    std::vector<unsigned int> indices;

    for (int i = 0; i < 36; ++i)
    {
        indices.push_back(CUBE_INDICES[i]);
    }

    return indices;
}


// Now the Quad constructor can move the vertices into a vector to be
// compatible with the Mesh constructor and initialize its superclass




#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_VERTICES_H
