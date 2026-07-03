#ifndef PRODUCTOS_S_H
#define PRODUCTOS_S_H

#include "../models/model_inventario.h"
#include "../models/model_productos.h"

int saveProductInText(const Inventario *inv);

int readProductoFromText(Inventario *inv);

#endif // !PRODUCTOS_S_H
