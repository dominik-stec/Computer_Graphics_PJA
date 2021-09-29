#include "window.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cstring>

#include "glerror.h"
#include "material.h"
#include "light.h"

const char* kPointLightVertexShader="PointLight.vertex.glsl";
const char* kPointLightFragmentShader="PointLight.fragment.glsl";
const char* kSunLightVertexShader="SunLight.vertex.glsl";
const char* kSunLightFragmentShader="SunLight.fragment.glsl";
const char* kSpotLightVertexShader="SpotLight.vertex.glsl";
const char* kSpotLightFragmentShader="SpotLight.fragment.glsl";


const char* kColorTextureFile="texture.tga";
const char* kIceTextureFile="ice.tga";
//
const char* kEarthmapTextureFile="earthmap.tga";

const int kPlaneM=40;
const int kPlaneN=40;

const int kTorusM=64;
const int kTorusN=32;
const GLfloat kTorusR=2.5f;
const GLfloat kTorusr=0.5f;


const Material  kYellowMaterial={
    {0.2f, 0.2f, 0.2f, 1.0f}, //Ambient
    {1.0f, 1.0f, 0.0f, 1.0f}, //Diffuse
    {0.6f, 0.6f, 0.6f, 1.0f}, //Specular
    {0.0f, 0.0f, 0.0f, 1.0f}, //Emission
    60.0f
  };

const Material kBlueMaterial={
    {0.2f, 0.2f, 0.2f, 1.0f}, //Ambient
    {0.1f, 1.0f, 0.1f, 1.0f}, //Diffuse
    {0.6f, 0.6f, 0.6f, 1.0f}, //Specular
    {0.0f, 0.0f, 0.0f, 1.0f}, //Emission
    90.0f
  };

const Material  kIceMaterial={
    {0.4f, 0.4f, 0.4f, 1.0f}, //Ambient
    {0.95f, 0.95f, 0.99f, 1.0f}, //Diffuse
    {0.99f, 0.99f, 0.99f, 1.0f}, //Specular
    {0.0f, 0.0f, 0.0f, 1.0f}, //Emission
    10.0f
  };
  
 //
 const Material  kEarthmapMaterial={
    {0.4f, 0.4f, 0.4f, 1.0f}, //Ambient
    {0.95f, 0.95f, 0.99f, 1.0f}, //Diffuse
    {0.99f, 0.99f, 0.99f, 1.0f}, //Specular
    {0.0f, 0.0f, 0.0f, 1.0f}, //Emission
    10.0f
  };

const PointLight kPointLight={
    {0.0f, 7.5f, 3.0f, 1.0f}, //position
    {0.1f, 0.1f, 0.1f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f}, //specular
    {0.5f, 0.005f, 0.0125f}	//attenuation
};

const SunLight kSunLight={
    {0.0f, 7.5f, 3.0f, 0.0f}, //position
    {0.1f, 0.1f, 0.1f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f} //specular
};

const SpotLight kSpotLight={
    {0.0f, 7.5f, 3.0f, 1.0f}, //position
    {0.3f, 0.3f, 0.3f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f}, //specular
    {0.5f, 0.005f, 0.0125f},	//attenuation
    {0.0f, -6.0f, -3.0f},	//direction
    20,			//cutoff, degrees
    20			//exponent
};



Window::Window(const char * title, int width, int height){
    title_ = (char*) title;
    width_ = width;
    height_ = height;
    last_time_ = 0;
    tori_.SetInitAngle(15);
    tori_.SetVelocity(-45);
    x_origin_ = y_origin_ = -1;
    current_program_ = POINT_PROGRAM;
}

void Window::Initialize(int argc, char * argv[], int major_gl_version, int minor_gl_version){

    InitGlutOrDie(argc, argv, major_gl_version, minor_gl_version);
    InitGlewOrDie();

    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    InitTextures();

    InitModels();

    InitPrograms();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);

}

void Window::InitGlutOrDie(int argc, char * argv[], int major_gl_version, int minor_gl_version){
    glutInit(&argc, argv);

    glutInitContextVersion(major_gl_version, minor_gl_version);
    glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
    glutInitContextFlags(GLUT_DEBUG);
#endif

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(width_, height_);

    glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE | GLUT_RGBA);

    int window_handle = glutCreateWindow(title_);

    if( window_handle < 1) {
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
        exit(EXIT_FAILURE);
    }


}

void Window::InitGlewOrDie(){
    GLenum glew_init_result;
    glewExperimental = GL_TRUE;
    glew_init_result = glewInit();

    if (GLEW_OK != glew_init_result) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    if(glDebugMessageCallback){
        std::cout << "Register OpenGL debug callback " << std::endl;
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROC) OpenglCallbackFunction, NULL);
        GLuint unused_ids = 0;
        glDebugMessageControl(GL_DONT_CARE,
            GL_DONT_CARE,
            GL_DONT_CARE,
            0,
            &unused_ids,
            GL_FALSE);
    }
    else
        std::cout << "glDebugMessageCallback not available" << std::endl;
#endif

}

void Window::InitModels(){
    tori_.Initialize(kTorusN, kTorusM, kTorusR, kTorusr);
    tori_.SetTexture(color_texture_);
    tori_.SetTextureUnit(GL_TEXTURE0);
    //tori_.SetMaterial(kBlueMaterial);
    tori_.SetMaterial(kEarthmapMaterial);
    
    tori_.SetMaterialPrim(kYellowMaterial);
    //bis
    tori_.SetMaterialBis(kBlueMaterial);

    plane_.Initialize(kPlaneM, kPlaneN);
    plane_.SetTexture(ice_texture_);
    plane_.SetTextureUnit(GL_TEXTURE0);
    plane_.SetMaterial(kIceMaterial);

}

void Window::InitTextures(){
    color_texture_.Initialize(kColorTextureFile);
    ice_texture_.Initialize(kIceTextureFile);
    //
    earthmap_texture_.Initialize(kEarthmapTextureFile);
}

void Window::InitPrograms(){
    view_matrix_.Translate(0, 0, -10);
    projection_matrix_ = Mat4::CreateProjectionMatrix(60, (float)width_/(float)height_, 0.1f, 100.0f);

    //point
    point_program_.Initialize(kPointLightVertexShader, kPointLightFragmentShader);
    glUseProgram(point_program_);
    point_program_.SetLight(kPointLight);
    point_program_.SetTextureUnit(0);
    point_program_.SetProjectionMatrix(projection_matrix_);
    point_program_.SetViewMatrix(view_matrix_);

    //sun
    sun_program_.Initialize(kSunLightVertexShader, kSunLightFragmentShader);
    glUseProgram(sun_program_);
    sun_program_.SetLight(kSunLight);
    sun_program_.SetTextureUnit(0);
    sun_program_.SetProjectionMatrix(projection_matrix_);
    sun_program_.SetViewMatrix(view_matrix_);

    //spot
    spot_program_.Initialize(kSpotLightVertexShader, kSpotLightFragmentShader);
    glUseProgram(spot_program_);
    spot_program_.SetLight(kSpotLight);
    spot_program_.SetTextureUnit(0);
    spot_program_.SetProjectionMatrix(projection_matrix_);
    spot_program_.SetViewMatrix(view_matrix_);

    glUseProgram(0);
}

void Window::Resize(int new_width, int new_height){
    width_ = new_width;
    height_ = new_height;
    projection_matrix_ = Mat4::CreateProjectionMatrix(60,
                (float)width_/(float)height_, 0.1f, 100.0f);
    SetProjectionMatrix();
    glViewport(0, 0, width_, height_);
    glutPostRedisplay();
}

void Window::KeyPressed(unsigned char key, int /*x_coord*/, int /*y_coord*/){
    switch (key){
    case 27:
      glutLeaveMainLoop();
    break;
    case ' ':
      tori_.ToggleAnimated();
    break;
    default:
    break;
    }
}

void Window::SpecialKeyPressed(int key, int /*x_coord*/, int /*y_coord*/){
    switch (key){
    case GLUT_KEY_LEFT:
      tori_.SlowDown();
    break;
    case GLUT_KEY_RIGHT:
      tori_.SpeedUp();
    break;
    case GLUT_KEY_F1:
      current_program_ = POINT_PROGRAM;
    break;
    case GLUT_KEY_F2:
      current_program_ = SUN_PROGRAM;
    break;
    case GLUT_KEY_F3:
      current_program_ = SPOT_PROGRAM;
    break;
    default:
    break;
    }
}


void Window::SetViewMatrix(){
    glUseProgram(point_program_);
    point_program_.SetViewMatrix(view_matrix_);
    glUseProgram(spot_program_);
    spot_program_.SetViewMatrix(view_matrix_);
    glUseProgram(spot_program_);
    spot_program_.SetViewMatrix(view_matrix_);
    glUseProgram(0);
}

void Window::SetProjectionMatrix(){
    glUseProgram(point_program_);
    point_program_.SetProjectionMatrix(projection_matrix_);
    glUseProgram(spot_program_);
    spot_program_.SetProjectionMatrix(projection_matrix_);
    glUseProgram(sun_program_);
    sun_program_.SetProjectionMatrix(projection_matrix_);
    glUseProgram(0);
}


void Window::MouseMove(int x_coord, int y_coord){	// this will only be true when the left button is down
    float delta_x_angle=0;
    float delta_y_angle=0;
    if (x_origin_ >= 0 && y_origin_ >=0) {
        // update deltaAngle
        delta_x_angle = (x_coord - x_origin_) * 0.1f;
        delta_y_angle = (y_coord - y_origin_) * 0.1f;
        x_origin_=x_coord;
        y_origin_=y_coord;

        // update camera's direction
        view_matrix_.RotateAboutY(delta_x_angle);
        view_matrix_.RotateAboutX(delta_y_angle);
        SetViewMatrix();
        glutPostRedisplay();
   }
}


#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif

void Window::MouseButton(int button, int state, int x_coord, int y_coord) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
          // when the button is released
          if (state == GLUT_UP) {
              x_origin_ = -1;
              y_origin_ = -1;
          }
          else  {// state = GLUT_DOWN
              x_origin_ = x_coord;
              y_origin_ = y_coord;
          }
    }
    else if ( button == GLUT_WHEEL_UP ){
        view_matrix_.Translate(0, 0, -0.1f);
        SetViewMatrix();
        glutPostRedisplay();
    }
    else if( button == GLUT_WHEEL_DOWN ){
        view_matrix_.Translate(0, 0, 0.1f);
        SetViewMatrix();
        glutPostRedisplay();
    }
}



void Window::Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    clock_t now = clock();
    if (last_time_ == 0) last_time_ = now;
    tori_.Move((float)(now - last_time_) / CLOCKS_PER_SEC);
    last_time_ = now;

    switch (current_program_){
    case POINT_PROGRAM:
        tori_.Draw(point_program_);
        plane_.Draw(point_program_);
    break;
    case SUN_PROGRAM:
        tori_.Draw(sun_program_);
        plane_.Draw(sun_program_);
    break;
    case SPOT_PROGRAM:
        tori_.Draw(spot_program_);
        plane_.Draw(spot_program_);
    break;
    }
    glutSwapBuffers();
    glutPostRedisplay();

}


