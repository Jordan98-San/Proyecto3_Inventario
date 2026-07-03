#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define LONGITUD_ID 8
#define MAX_NAME 100

typedef struct {
  char id[LONGITUD_ID + 1]; // Omitir el '\0'' con el +1
  char name[MAX_NAME];      // El nombre tiene un tamanio maximo de 100
  float precio;
  unsigned int stock;
} Producto;

#endif // PRODUCTOS_H
