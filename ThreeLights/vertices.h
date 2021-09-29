#ifndef VERTICES_H
#define VERTICES_H

typedef struct ColorVertex{
    float position[4];
    float color[4];
} ColorVertex;

typedef struct TextureVertex{
    float position[4];
    float texture[2];
} TextureVertex;

typedef struct SkyTextureVertex{
    float position[4];
    float texture[3];
} SkyTextureVertex;

typedef struct NormalTextureVertex{
    float position[4];
    float texture[2];
    float normal[3];
} NormalTextureVertex;


#endif // VERTICES_H
