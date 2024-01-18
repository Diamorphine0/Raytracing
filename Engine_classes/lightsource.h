#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class lightsource
{
public:
    lightsource(glm::vec3 lightPos, glm::vec3 lightColor){
        this->lightPos = lightPos;
        this->lightColor = lightColor;
    }
    lightsource(){
        this->lightPos = glm::vec3(0.0f);
        this->lightColor = glm::vec3(0.0f);
    }

    glm::vec3 lightPos;
    glm::vec3 lightColor;
};

class lightarray{
public:
    int counter;
    lightsource* arr;

    lightarray(){
        counter = 0;
        arr = new lightsource[20];
        for(int i = 0; i < 20; i++)
            arr[i] = lightsource(glm::vec3(0.0f), glm::vec3(0.0f));
    };

    lightarray(lightsource light){
        counter = 1;
        arr = new lightsource[20];
        for(int i = 1; i < 20; i++)
            arr[i] = lightsource(glm::vec3(0.0f), glm::vec3(0.0f));
    };

    ~lightarray(){
        delete arr;
    }

    void addSource(lightsource light){
        if(counter < 20){
            arr[counter] = light;
            counter++;
        }
        return;
    }
};


#endif // LIGHTSOURCE_H
