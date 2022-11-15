#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "affichage.h"
#include "point.h"
#include "polygone.h"
#include "graphics.h"
#include "linmath.h"
#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"

const int fenetreWidth = 600;
const int fenetreHeight = 500;

// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


// Trace un segment entre deux points a et b
void Affichage::segment(const Point & a, const Point & b)
{
    line(a.x(), a.y(), b.x(), b.y());
}


// trace le polygone P dans une fenêtre graphique OpenGL et Winbgi
void Affichage::trace(const Polygone &P)
{
    traceAvecWinbgi(P);
    traceAvecOpenGL(P);
}

void Affichage::traceAvecWinbgi(const Polygone& P) {
    Sommet* s = P.premier();

    do
    {
        segment(s->coordonnees(), s->suivant()->coordonnees());
        s = s->suivant();

    } while (s != P.premier());
}

void Affichage::traceAvecOpenGL(const Polygone& P) {

    glfwSetErrorCallback(error_callback);

    // Initialize GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(fenetreWidth, fenetreHeight, "Window OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, fenetreWidth, fenetreHeight);

    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    /*const GLint mvp_location = shaderProgram.GetUniformLocation("MVP");
    const GLint vpos_location = shaderProgram.GetAttribLocation("vPos");
    const GLint vcol_location = shaderProgram.GetAttribLocation("vCol");*/

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);

    /*VAO1.VertexAttribPointer(vpos_location, 2, (void*)offsetof(GLfloat, pos));
    VAO1.VertexAttribPointer(vpos_location, 3, (void*)offsetof(GLfloat, col));*/


    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    /*GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/

    /*GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);*/


    /*glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));*/

    while (!glfwWindowShouldClose(window))
    {
        /*int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);*/
        glClear(GL_COLOR_BUFFER_BIT);

        /*mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);*/

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        // glBindVertexArray(vertex_array);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
