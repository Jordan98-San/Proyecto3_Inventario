#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define LONGITUD_ID 8
#define MAX_NAME 100
#define MAX_CATEGORIA 100

typedef struct {
  char codigo[LONGITUD_ID + 1]; // Omitir el '\0'' con el +1
  char nombre[MAX_NAME];        // El nombre tiene un tamanio maximo de 100
  char categoria[MAX_CATEGORIA];
  float precioVenta;
  float precioCompra;
  unsigned int cantidad;
  float utilidad;
} Producto;

#endif // PRODUCTOS_H
