#ifndef WINDOW_H
#define WINDOW_H

#include <cstring>
#include <ctime>

#include "texturecameraprogram.h"
#include "matma.h"
#include "plane.h"
#include "twospheres.h"
#include "moon.h"
#include "texture.h"

class Window{
 public:
    Window(const char*, int, int);
    void Initialize(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void Resize(int new_width, int new_height);
    void Render(void);
    void KeyPressed(unsigned char key, int x_coord, int y_coord);
    void SpecialKeyPressed(int key, int x_coord, int y_coord);
 private:
    int width_;
    int height_;
    char* title_;
    TextureCameraProgram program_;
    clock_t last_time_;

    Plane plane_;
    TwoSpheres twoSpheres_;
	Moon moon_;

    Texture sky_texture_;
    Texture mercury_texture_;
    Texture venus_texture_;
    Texture earth_texture_;
	Texture mars_texture_;
	Texture jupiter_texture_;
	Texture saturn_texture_;
	Texture uranus_texture_;
	Texture neptune_texture_;
	Texture pluto_texture_;
	Texture moon_texture_;
	
    Mat4 view_matrix_;
    Mat4 projection_matrix_;

    void InitGlutOrDie(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void InitGlewOrDie();
    void InitModels();
    void InitPrograms();
    void InitTextures();
    void SetViewMatrix() const;
    void SetProjectionMatrix() const;

};


#endif // WINDOW_H

