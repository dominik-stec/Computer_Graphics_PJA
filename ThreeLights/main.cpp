#include "window.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>



const int kMajorGLVersion = 4;
const int kMinorGLVersion = 3;

Window window("Oswietlenie w OpenGL", 800, 600);

void Resize (int new_width, int new_height){
    window.Resize(new_width, new_height);
}

void Render(){
    window.Render();
}


void KeyPressed(unsigned char key, int x_coord, int y_coord){
    window.KeyPressed(key, x_coord, y_coord);
}

void SpecialKeyPressed(int key, int x_coord, int y_coord){
    window.SpecialKeyPressed(key, x_coord, y_coord);
}


void MouseMove(int x_coord, int y_coord){
    //window.MouseMove(x_coord, y_coord);
}


void MouseButton(int button, int state, int x_coord, int y_coord) {
    //window.MouseButton(button, state, x_coord, y_coord);
}


int main(int argc, char* argv[]){
    window.Initialize(argc, argv, kMajorGLVersion, kMinorGLVersion);

    glutReshapeFunc(Resize);
    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyPressed);
    glutSpecialFunc(SpecialKeyPressed);
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMove);

    glutMainLoop();

    exit(EXIT_SUCCESS);
}

