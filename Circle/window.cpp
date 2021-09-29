#include "window.h"

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "glerror.h"

Window::Window(const char * title, int width, int height){
    title_ = (char*) title;
    width_ = width;
    height_ = height;
}

void Window::Initialize(int argc, char * argv[], int major_gl_version, int minor_gl_version){

    InitGlutOrDie(argc, argv, major_gl_version, minor_gl_version);
    InitGlewOrDie();


    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    InitModels();
    InitPrograms();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

    glutInitDisplayMode(/*GLUT_DEPTH|*/ GLUT_DOUBLE | GLUT_RGBA);

    int window_handle = glutCreateWindow(title_);

    if( window_handle < 1) {
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
		return;
		//exit(EXIT_FAILURE);
    }


}

void Window::InitGlewOrDie(){
    GLenum glew_init_result;
    glewExperimental = GL_TRUE;
    glew_init_result = glewInit();

    if (GLEW_OK != glew_init_result) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
		return;
		//exit(EXIT_FAILURE);
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
    //triangle_.Initialize();
    star_.Initialize();
    starlines_.Initialize();
    circle_.Initialize();
	circlelines_.Initialize();
}

void Window::InitPrograms(){
    program_.Initialize();
}

void Window::Resize(int new_width, int new_height){
    width_ = new_width;
    height_ = new_height;
    glViewport(0, 0, width_, height_);
    glutPostRedisplay();
}

void Window::KeyPressed(unsigned char key, int /*x_coord*/, int /*y_coord*/){
    switch (key){
      case 27:
        glutLeaveMainLoop();
      break;
      case ' ':
		//powiekszyc numer wyswietlnej figury
		figure_ = (figure_ + 1) % 4;
		glutPostRedisplay();
	  break;
      default:
      break;
    }
}


void Window::Render(){
    glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

	//triangle_.Draw(program_);
	switch(figure_) {
		case 0: 
			star_.Draw(program_);
			break;
		case 1:
			starlines_.Draw(program_);
			break;
		case 2:
			circle_.Draw(program_);
			break;
		case 3:
			circlelines_.Draw(program_);
			break;
		default:
		break;
    }
	
    glutSwapBuffers();
//    glutPostRedisplay();

}

