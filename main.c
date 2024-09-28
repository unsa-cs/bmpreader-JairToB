#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}


void drawBMPblacknWhite(BMPImage *image){
  glDrawPixels(image->width, image->height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image->data);
}

int main(int argc, char *argv[]) {
  //char filename[] = "Lenna.bmp";

  // Pedir al usuario el nombre del archivo BMP
  //printf("Ingrese el nombre del archivo BMP (con extensión): ");
  //scanf("%255s", filename);

  //image = readBMP(filename);
  //if (!image) return 1;

  // Inicializar GLUT
  argc = 3; // Necesario para evitar problemas con glutInit
  argv[1] = "Lenna.bmp"; // Argumento vacío para GLUT
  argv[2] = "B&W";
  image = readBMP(argv[1]);
  if(argv[2]){
    drawBMPblacknWhite(image);
    image = readBMP(argv[1]);
  }
  
  if (!image) return 1;
  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
