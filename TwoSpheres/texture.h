#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture{
public:
    ~Texture();
    void Initialize(const char *filename);

    operator GLuint() const {return texture_;}

protected:
    GLuint texture_;
    void LoadTGAFileOrDie(GLenum target, const char  * filename);
};



#endif // TEXTURE_H
