#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Lightsource
{
public:
    Lightsource(glm::vec3 lightPos, glm::vec3 lightColor){
        this->lightPos = lightPos;
        this->lightColor = lightColor;
    }
    Lightsource(){
        this->lightPos = glm::vec3(0.0f);
        this->lightColor = glm::vec3(0.0f);
    }

    glm::vec3 lightPos;
    glm::vec3 lightColor;
};

class Lightarray{
public:
    int counter;
    Lightsource* arr;

    Lightarray(){
        counter = 0;
        arr = new Lightsource[20];
        for(int i = 0; i < 20; i++)
            arr[i] = Lightsource(glm::vec3(0.0f), glm::vec3(0.0f));
    };

    Lightarray(Lightsource light){
        counter = 1;
        arr = new Lightsource[20];
        for(int i = 1; i < 20; i++)
            arr[i] = Lightsource(glm::vec3(0.0f), glm::vec3(0.0f));
    };

    ~Lightarray(){
        delete arr;
    }

    void addSource(Lightsource light){
        if(counter < 20){
            arr[counter] = light;
            counter++;
        }
        return;
    }
};


#endif // LIGHTSOURCE_H
