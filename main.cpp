#define _CRT_SECURE_NO_WARNINGS
 
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

//GLM biblioteke
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Monument.hpp"
#include "GenerateObelisk.hpp"
#include "GenerateMonument2.hpp"
#include "GenerateReverseFurstum.hpp"
#include "Global.hpp"
#include "GenerateBase.hpp"
#include "GenerateFurstum.hpp"
#include "GeneratePole.hpp"
#include "GenerateSquare.hpp"
#include "GenerateFloor.hpp"
#include "GenerateWall.hpp"

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);
unsigned int loadLetterTexture(const char* path) {
    unsigned int t = loadImageToTexture(path);
    glBindTexture(GL_TEXTURE_2D, t);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return t;
}
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Debug Message: " << message << std::endl;
}

int main(void)
{
    
    if (!glfwInit())
    {
        std::cout<<"GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }
    glEnable(GL_DEBUG_OUTPUT);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::vector<unsigned int> letterTextures = std::vector<unsigned int>();
    
    
    GLFWwindow* window;
    unsigned int wWidth = 1400;
    unsigned int wHeight = 800;
    const char wTitle[] = "[SV-38 2021]";
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }
    
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }
    glEnable(GL_DEBUG_OUTPUT);



    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROMJENLJIVE I BAFERI +++++++++++++++++++++++++++++++++++++++++++++++++

    
    
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
    
    int pressed = 0;

    letterTextures.push_back(loadLetterTexture("alphabet/M.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/A.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/R.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/K.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/O.png"));
    
    letterTextures.push_back(loadLetterTexture("alphabet/K.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/U.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/V.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/I.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/Z.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/I.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/CH.png"));

    letterTextures.push_back(loadLetterTexture("alphabet/S.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/V.png"));

    letterTextures.push_back(loadLetterTexture("alphabet/slash.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/3.png"));

    letterTextures.push_back(loadLetterTexture("alphabet/8.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/2.png"));

    letterTextures.push_back(loadLetterTexture("alphabet/0.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/2.png"));
    letterTextures.push_back(loadLetterTexture("alphabet/1.png"));

    unsigned int cobbleTexture = loadImageToTexture("cobble.png");

    unsigned int obeliskTexture = loadImageToTexture("rocks.png");
    unsigned int marbleTexture = loadImageToTexture("marble.png");
    glBindTexture(GL_TEXTURE_2D, obeliskTexture); //Podesavamo teksturu
    unsigned int unifiedShader = createShader("basic.vert", "basic.frag");
    unsigned int letterShader = createShader("letter.vert", "basic.frag");

    glUseProgram(unifiedShader);
    unsigned uTexLoc = glGetUniformLocation(unifiedShader, "uTex");
    glUniform1i(uTexLoc, 0);
    glUseProgram(0);

    glUseProgram(unifiedShader);
    unsigned uTexLoc2 = glGetUniformLocation(unifiedShader, "uTex");
    glUniform1i(uTexLoc2, 0);
    glUseProgram(0);

    unsigned int whiteTexture = loadImageToTexture("white.png");
    glBindTexture(GL_TEXTURE_2D, obeliskTexture); //Podesavamo teksturu
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    Monument obelisk = Monument(2, -5, 2, marbleTexture, unifiedShader);
    Monument obeliskBase = Monument(2, -5, 0, obeliskTexture, unifiedShader);
    obeliskBase.generateVertices = &generateBaseVertices;
    obeliskBase.setup();
    std::vector<Monument*> letters = std::vector<Monument*>();
    float x = -25.0f;
    float y = 0;
    for (int i = 0; i < 21; i++) {
        x += 25.0f;
        if (i == 5 || i == 17) {
            x += 25.0f;
        }
        if (i == 12) {
            x = 0;
            y = 25.0f;
        }
        Monument* M = new Monument(x, y, 0, letterTextures[i], letterShader);
        M->generateVertices = &generateSquareVertices;
        M->setup();
        letters.push_back(M);
    }
    

    obelisk.generateVertices = &generateObeliskVertices;
    obelisk.setup();
    
    Monument floor = Monument(0, 0, 0, cobbleTexture, unifiedShader);
    floor.generateVertices = &generateFloorVertices;
    floor.setup();

    Monument wall = Monument(0, 0, 0, cobbleTexture, unifiedShader);
    wall.generateVertices = &generateWallVertices;
    wall.setup();


    Monument monument2 = Monument(-3, -4, 1, marbleTexture, unifiedShader);
    monument2.generateVertices = &generateMonument2Vertices;
    monument2.setup();
    
    std::vector<Monument> ReverseFurstum = std::vector<Monument>();
    Monument base = Monument(2, 0, 0, obeliskTexture, unifiedShader);
    base.generateVertices = &generateBaseVertices;
    Monument furstum1 = Monument(2, 0, 1, whiteTexture, unifiedShader);
    Monument furstum2 = Monument(2, 0, 2, whiteTexture, unifiedShader);
    Monument furstum3 = Monument(2, 0, 3, whiteTexture, unifiedShader);
    furstum1.generateVertices = &generateReverseFurstumVertices;
    furstum2.generateVertices = &generateReverseFurstumVertices;
    furstum3.generateVertices = &generateReverseFurstumVertices;
    furstum1.setup();
    furstum2.setup();
    furstum3.setup();
    base.setup();
    

    Monument bottomFurstum = Monument(-2, 0, 0, marbleTexture, unifiedShader);
    Monument pole = Monument(-2, 0, 0, whiteTexture, unifiedShader);
    Monument topFurstum = Monument(-2, 0, 4, marbleTexture, unifiedShader);
    
    bottomFurstum.generateVertices = &generateFurstumVertices;
    pole.generateVertices = &generatePoleVertices;
    topFurstum.generateVertices = &generateReverseFurstumVertices;

    bottomFurstum.setup();
    pole.setup();
    topFurstum.setup();
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++            UNIFORME            +++++++++++++++++++++++++++++++++++++++++++++++++

    glm::mat4 model = glm::mat4(1.0f); //Matrica transformacija - mat4(1.0f) generise jedinicnu matricu
    unsigned int modelLoc = glGetUniformLocation(unifiedShader, "uM");
    unsigned int modelLoc2 = glGetUniformLocation(letterShader, "uM");


    glm::mat4 view; //Matrica pogleda (kamere)
    view = glm::lookAt(glm::vec3(2.0f, 5.0f, 5.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // lookAt(Gdje je kamera, u sta kamera gleda, jedinicni vektor pozitivne Y ose svijeta  - ovo rotira kameru)
    unsigned int viewLoc = glGetUniformLocation(unifiedShader, "uV");

    
    glm::mat4 projectionP = glm::perspective(glm::radians(90.0f), (float)wWidth / (float)wHeight, 0.1f, 100.0f); //Matrica perspektivne projekcije (FOV, Aspect Ratio, prednja ravan, zadnja ravan)
    glm::mat4 projectionO = glm::ortho(0.0f, (float)wWidth, (float)wHeight, 0.0f, -1.0f, 1.0f);
    unsigned int projectionLoc = glGetUniformLocation(unifiedShader, "uP");
    unsigned int projectionLoc2 = glGetUniformLocation(letterShader, "uP");


    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++ RENDER LOOP - PETLJA ZA CRTANJE +++++++++++++++++++++++++++++++++++++++++++++++++
    glUseProgram(unifiedShader); //Slanje default vrijednosti uniformi
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); //(Adresa matrice, broj matrica koje saljemo, da li treba da se transponuju, pokazivac do matrica)
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionP));

    glUseProgram(letterShader); //Slanje default vrijednosti uniformi
    glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model)); //(Adresa matrice, broj matrica koje saljemo, da li treba da se transponuju, pokazivac do matrica)
    glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projectionO));



    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCullFace(GL_BACK);//Biranje lica koje ce se eliminisati (tek nakon sto ukljucimo Face Culling)
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    
    while (!glfwWindowShouldClose(window))
    {
        float sTime = glfwGetTime();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        //Testiranje dubine
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && pressed == 0)
        {
             //Ukljucivanje testiranja Z bafera
            glUseProgram(unifiedShader); //Slanje default vrijednosti uniformi
            view = glm::lookAt(glm::vec3(2.0f, 5.0f, 5.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // lookAt(Gdje je kamera, u sta kamera gleda, jedinicni vektor pozitivne Y ose svijeta  - ovo rotira kameru)
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            pressed = 10;
        }

        //Odstranjivanje lica (Prethodno smo podesili koje lice uklanjamo sa glCullFace)
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && pressed == 0)
        {
            glUseProgram(unifiedShader); //Slanje default vrijednosti uniformi
            view = glm::lookAt(glm::vec3(-2.0f, 5.0f, 5.0f), glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // lookAt(Gdje je kamera, u sta kamera gleda, jedinicni vektor pozitivne Y ose svijeta  - ovo rotira kameru)
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            pressed = 10;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && pressed == 0)
        {
            glUseProgram(unifiedShader); //Slanje default vrijednosti uniformi
            view = glm::lookAt(glm::vec3(2.0f, -9.0f, 5.0f), glm::vec3(2.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // lookAt(Gdje je kamera, u sta kamera gleda, jedinicni vektor pozitivne Y ose svijeta  - ovo rotira kameru)
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            pressed = 10;
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && pressed == 0)
        {
            glUseProgram(unifiedShader); //Slanje default vrijednosti uniformi
            view = glm::lookAt(glm::vec3(-3.0f, -9.0f, 5.0f), glm::vec3(-3.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // lookAt(Gdje je kamera, u sta kamera gleda, jedinicni vektor pozitivne Y ose svijeta  - ovo rotira kameru)
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            pressed = 10;
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Osvjezavamo i Z bafer i bafer boje
        

        glCullFace(GL_BACK);
        
        floor.drawStill();
        obeliskBase.draw();
        obelisk.draw();
        monument2.draw();
        furstum1.draw();
        furstum2.draw();
        furstum3.draw();
        base.draw();
        bottomFurstum.draw();
        pole.draw();
        topFurstum.draw();


        
        
        glCullFace(GL_FRONT);
        
        floor.drawStill();
        //wall.drawStill();
        obeliskBase.draw();
        obelisk.draw();
        monument2.draw();
        furstum1.draw();
        furstum2.draw();
        furstum3.draw();
        base.draw();
        bottomFurstum.draw();
        pole.draw();
        topFurstum.draw();


        for (int i = 0; i < letters.size(); i++) {
            letters[i]->drawLetter();
        }

        if (pressed > 0)
            pressed--;

        glfwSwapBuffers(window);
        float timeTaken = sTime - glfwGetTime();
        if (timeTaken < 1.0f / 60.0f)
            glfwWaitEventsTimeout(1.0f / (60.0f - timeTaken));
        glfwPollEvents();
    }

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++ POSPREMANJE +++++++++++++++++++++++++++++++++++++++++++++++++

    glDeleteProgram(unifiedShader);
    glDeleteProgram(letterShader);

    glfwTerminate();
    return 0;
}

unsigned int compileShader(GLenum type, const char* source)
{
    std::string content = "";
    std::ifstream file(source);
    std::stringstream ss;
    if (file.is_open())
    {
        ss << file.rdbuf();
        file.close();
        std::cout << "Uspjesno procitao fajl sa putanje \"" << source << "\"!" << std::endl;
    }
    else {
        ss << "";
        std::cout << "Greska pri citanju fajla sa putanje \"" << source << "\"!" << std::endl;
    }
     std::string temp = ss.str();
     const char* sourceCode = temp.c_str();

    int shader = glCreateShader(type);
    
    int success;
    char infoLog[512];
    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            printf("VERTEX");
        else if (type == GL_FRAGMENT_SHADER)
            printf("FRAGMENT");
        printf(" sejder ima gresku! Greska: \n");
        printf(infoLog);
    }
    return shader;
}
unsigned int createShader(const char* vsSource, const char* fsSource)
{
    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    program = glCreateProgram();

    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Objedinjeni sejder ima gresku! Greska: \n";
        std::cout << infoLog << std::endl;
    }

    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}
