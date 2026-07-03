

#ifndef INVENTARIO_SERVICE_H
#define INVENTARIO_SERVICE_H

#include "../../include/models/model_inventario.h"

void inicializarInventario(Inventario *inv);

void agregarProducto(Inventario *inventario, Producto p);

int incrementarStock(Producto *producto, unsigned int cantidad);

int disminuirStrock(Producto *producto, unsigned int cantidad);

#endif // !INVENTARIO_SERVICE_H
