#include "Monument.hpp"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
Monument::Monument(float x, float y, float z, unsigned texture, unsigned shader) : x(x), y(y), z(z), vertices(*(new std::vector<float>(0))), indices(*(new std::vector<unsigned int>(0))), VAO(0), VBO(0), EBO(0), texture(texture), shader(shader) {}
Monument::Monument() : vertices(*(new std::vector<float>(0))), indices(*(new std::vector<unsigned int>(0))) {}

void Monument::setup() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    unsigned int stride = (3 + 4) * sizeof(float);

    this->generateVertices(this);
    // Bind VAO first
    glBindVertexArray(VAO);

    // Bind and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Bind and upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // UV
    glEnableVertexAttribArray(1);;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};
void Monument::draw() {
    glUseProgram(shader);
    float timeValue = glfwGetTime(); // or similar
    glUniform1f(glGetUniformLocation(shader, "uTime"), timeValue);

    GLint pivotLoc = glGetUniformLocation(shader, "uPivot");
    glm::vec3 pivot = glm::vec3(x, y, z); // Replace with your actual pivot

    // Set the uniform
    glUniform3fv(pivotLoc, 1, glm::value_ptr(pivot));

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "uTex"), 0);  // Link sampler2D to texture unit 0

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
};

void Monument::drawStill() {
    glUseProgram(shader);
    float timeValue = 0; // or similar
    glUniform1f(glGetUniformLocation(shader, "uTime"), timeValue);

    GLint pivotLoc = glGetUniformLocation(shader, "uPivot");
    glm::vec3 pivot = glm::vec3(x, y, z); // Replace with your actual pivot

    // Set the uniform
    glUniform3fv(pivotLoc, 1, glm::value_ptr(pivot));

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "uTex"), 0);  // Link sampler2D to texture unit 0

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
};


void Monument::drawLetter() {
    glUseProgram(shader);
    
    glUniform1i(glGetUniformLocation(shader, "uTex"), 0);  // Link sampler2D to texture unit 0
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

Monument::~Monument(){
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}