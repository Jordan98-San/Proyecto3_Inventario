// model_inventario

#ifndef INVENTRAIO_H
#define INVENTRAIO_H

#include "./model_productos.h"

#define MAX_PRODUCTOS 1000

typedef struct {
  Producto producto[MAX_PRODUCTOS];
  int cantidad; /*Cuantos producto hay en stock */
} Inventario;

#endif // !INVENTRAIO_H
