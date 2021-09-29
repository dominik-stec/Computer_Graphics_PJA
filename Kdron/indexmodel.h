#ifndef INDEXMODEL_H
#define INDEXMODEL_H

#include <GL/glew.h>

class IndexModel{
public:
    ~IndexModel();
protected:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint index_buffer_;
};


#endif // INDEXMODEL_H
