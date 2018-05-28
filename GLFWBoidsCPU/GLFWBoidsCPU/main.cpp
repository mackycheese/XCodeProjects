
//  main.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include <glm/glm.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

bool hsb,smooth;
float xscale,yscale,maxIters;
int type;

void key_callback(GLFWwindow*window,int key,int scancode,int action,int mods){
    if(key==GLFW_KEY_1)maxIters++;
    if(key==GLFW_KEY_2)maxIters--;
    if(action==GLFW_RELEASE)return;
    if(action==GLFW_REPEAT)return;
    if(key==GLFW_KEY_T){
        if(type==0)type=1;
        else if(type==1)type=0;
    }
    if(key==GLFW_KEY_S){
        smooth=!smooth;
    }
    if(key==GLFW_KEY_H){
        hsb=!hsb;
    }
}

int main(int argc, const char * argv[]) {
    type=1;
    hsb=true;
    smooth=true;
    xscale=1;
    yscale=1;
    maxIters=50;
    
    if(!glfwInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    window=glfwCreateWindow(1000, 1000, "Title", 0, 0);
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    
    glfwMakeContextCurrent(window);
    
    ShaderProgram shader;
    shader.vertFileName="shader.vert";
    shader.fragFileName="shader.frag";
    
    shader.compile();
    
    Mesh mesh;
    
    Vertex v1;
    v1.pos=vec3(-1,-1,0);
    v1.texCoords=vec2(0,0);
    v1.col=vec3(1,1,1);
    
    Vertex v2;
    v2.pos=vec3(1,-1,0);
    v2.texCoords=vec2(1,0);
    v2.col=vec3(1,1,1);
    
    Vertex v3;
    v3.pos=vec3(1,1,0);
    v3.texCoords=vec2(1,1);
    v3.col=vec3(1,1,1);
    
    Vertex v4;
    v4.pos=vec3(-1,1,0);
    v4.texCoords=vec2(0,1);
    v4.col=vec3(1,1,1);
    
    mesh.verts.push_back(v1);
    mesh.verts.push_back(v2);
    mesh.verts.push_back(v3);
    mesh.verts.push_back(v4);
    mesh.tris.push_back(0);
    mesh.tris.push_back(1);
    mesh.tris.push_back(2);

    Texture tex;
    int w=512;
    int h=512;
    int nrChannels=1;
    unsigned char* data=stbi_load("grass-top.png",&w,&h,&nrChannels,0);
    

    glfwSetKeyCallback(window, key_callback);
    
    while(!glfwWindowShouldClose(window)){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        xscale=(xpos/500)-1;
        yscale=(ypos/500)-1;
        
        glfwMakeContextCurrent(window);
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        shader.setBool("doHSB", hsb);
        shader.setBool("doSmooth",smooth);
        shader.setFloat("xOffScale",xscale);
        shader.setFloat("yOffScale", yscale);
        shader.setFloat("maxIters", maxIters);
        shader.setInt("fractalType", type);
        
        mesh.drawMesh(shader);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader.del();
    
    glfwTerminate();
}