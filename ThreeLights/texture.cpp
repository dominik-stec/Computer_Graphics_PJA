#include "texture.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdint.h>

using namespace std;


typedef struct TGAHeader
{
  uint8_t  idlength;
  uint8_t  colormap;
  uint8_t  datatype;
  uint8_t  colormapinfo[5];
  uint16_t xorigin;
  uint16_t yorigin;
  uint16_t width;
  uint16_t height;
  uint8_t  bitperpel;
  uint8_t  description;
} TGAHeader;



void Texture::Initialize(const char * filename){
    glGenTextures(1, &texture_);

    // aktywacja
    glBindTexture(GL_TEXTURE_2D, texture_);

    LoadTGAFileOrDie(GL_TEXTURE_2D, filename);

    // parametry interpolacji tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // parametry ekstrapolacji tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

}


void Texture::LoadTGAFileOrDie(GLenum target, const char  * filename){
    TGAHeader*  header;
    GLchar*     buffer;
    size_t      file_size;
    GLuint format;
    GLuint internal_format;

    ifstream file (filename, ios::in|ios::ate|ios::binary);
    if (file.is_open()) {
        file_size = file.tellg();
        buffer = new GLchar [file_size];
        file.seekg (0, ios::beg);
        file.read (buffer, file_size);
        file.close();
    }
    else{ //file was not opened
        cerr<<"Could not open the texture file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

   // Rozmiar jest mniejszy od nagłówka
      if (file_size <= sizeof(TGAHeader)) {
        cerr<<"Too small texture file "<<filename<<endl;
        delete [] buffer;
        exit(EXIT_FAILURE);
      }

      header = (TGAHeader*)buffer;

      // sprawda się plik TGA: nieskompresowany RGB lub RGBA obraz
      if (header->datatype != 2 || (header->bitperpel != 24 && header->bitperpel != 32)){
          cerr<<"Wrong TGA format "<<filename<<endl;
          delete [] buffer;
          exit(EXIT_FAILURE);
      }

      // format tekstury
      format = (header->bitperpel == 24 ? GL_BGR : GL_BGRA);
      internal_format = (format == GL_BGR ? GL_RGB8 : GL_RGBA8);


      // wysyłanie tekstury na GPU
      glTexImage2D(target, 0, internal_format, header->width, header->height, 0, format,
           GL_UNSIGNED_BYTE, (const GLvoid*)(buffer + sizeof(TGAHeader) + header->idlength));

      // zwolnienie pamięci
      delete [] buffer;

}


Texture::~Texture(){
    glDeleteTextures(1, &texture_);
}
