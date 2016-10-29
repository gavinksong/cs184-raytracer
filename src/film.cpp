#include <stdio.h>
#include <string.h>
#include "film.h"
#include "jpeglib.h"

typedef unsigned char uint8;

uint8* Film::imagebuffer (void) const {
  uint8* buffer = new uint8[this->width * this->height * 3];
  for (int x = 0; x < this->width; x++) {
    for (int y = 0; y < this->height; y++) {
      size_t offset = (y * this->width + x) * 3;
      Vec3 pixel = this->pixels[x][y];
      buffer[offset] = (uint8) (pixel.x * 255);
      buffer[offset+1] = (uint8) (pixel.y * 255);
      buffer[offset+2] = (uint8) (pixel.z * 255);
    }
  }
  return buffer;
};

Film::Film (int width, int height) : width(width), height(height) {
  this->pixels = new Vec3*[width];
  this->numCommits = new float*[width];
  for (int i = 0; i < width; i++) {
    this->pixels[i] = new Vec3[height];
    this->numCommits[i] = new float[height];
    memset (this->numCommits[i], 0, sizeof (float) * height);
  }
};

Film::~Film (void) {
  for (int i = 0; i < this->width; i++) {
    delete [] this->pixels[i];
    delete [] this->numCommits[i];
  }
  delete [] this->pixels;
  delete [] this->numCommits;
};

void Film::commit (const Sample& sample, const Vec3& color) {
  int x = (int)sample.x;
  int y = (int)sample.y;

  Vec3* pixel = &(this->pixels[x][y]);
  float* count = &(this->numCommits[x][y]);

  if (*count++ == 0)
    *pixel = color;
  else
    *pixel = (*pixel * (*count-1) + color) / *count;
};

void Film::writeToJPEG (const char* filename) const {
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * outfile;
  JSAMPROW row_pointer[1];
  int row_stride;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = this->width;
  cinfo.image_height = this->height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);
  jpeg_start_compress(&cinfo, TRUE);

  uint8* image_buffer = this->imagebuffer ();
  row_stride = this->width * 3;

  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  delete image_buffer;
  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
};

Vec3 Film::getColorAt (int x, int y) const {
  return this->pixels[x][y];
};
