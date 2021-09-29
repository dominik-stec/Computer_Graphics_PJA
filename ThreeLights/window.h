#ifndef WINDOW_H
#define WINDOW_H

#include <ctime>

#include "tori.h"
#include "plane.h"
#include "pointlightprogram.h"
#include "sunlightprogram.h"
#include "spotlightprogram.h"
#include "texture.h"
#include "matma.h"

class Window{
 public:
    Window(const char*, int, int);
    void Initialize(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void Resize(int new_width, int new_height);
    void Render(void);
    void KeyPressed(unsigned char key, int x_coord, int y_coord);
    void SpecialKeyPressed(int key, int x_coord, int y_coord);
    void MouseButton(int button, int state, int x_coord, int y_coord);
    void MouseMove(int x_coord, int y_coord);
 private:
    int width_;
    int height_;
    char* title_;

    Tori tori_;
    Plane plane_;

    Texture color_texture_;
    Texture ice_texture_;
    //
    Texture earthmap_texture_;

    PointLightProgram point_program_;
    SpotLightProgram spot_program_;
    SunLightProgram sun_program_;

    enum {POINT_PROGRAM, SUN_PROGRAM, SPOT_PROGRAM} current_program_;

    int x_origin_;
    int y_origin_;

    clock_t last_time_;

    Mat4 view_matrix_;
    Mat4 projection_matrix_;

    void InitGlutOrDie(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void InitGlewOrDie();
    void InitModels();
    void InitTextures();
    void InitPrograms();

    void SetViewMatrix();
    void SetProjectionMatrix();
};


#endif // WINDOW_H

