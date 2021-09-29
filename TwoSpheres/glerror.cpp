#include "glerror.h"

#include <iostream>

using namespace std;

void GLAPIENTRY OpenglCallbackFunction(GLenum /*source*/,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei /*length*/,
                                       const GLchar* message,
                                       void* /*user_param*/){

    cout << "---------------------opengl-callback-start------------" << endl;
    cout << "message: "<< message << endl;
    cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_MARKER:
        cout << "MARKER";
        break;
    case GL_DEBUG_TYPE_OTHER:
        cout << "OTHER";
        break;
    }
    cout << endl;

    cout << "id: "<<id << endl;
    cout << "severity: ";
    switch (severity){
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
        break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
        break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
        break;
        case  GL_DEBUG_SEVERITY_NOTIFICATION:
            cout << "NOTIFICATION";
        break;
    }
    cout << endl;
cout << "---------------------opengl-callback-end--------------" << endl;
}

