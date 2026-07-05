#include "../models/model_inventario.h"
#include "../models/model_productos.h"

#ifndef STOCK_H
#define STOCK_H

void generarIdAleatorio(char *id); // ID -> ya conoce su longitud = 8

int validarIdUnico(Inventario *inv, char *id);

Producto crearProduct(const char *name, float precio);
/*
 * Leer los datos de un producto desde la entrada estandar
 * Solucita al usuario que introduzca el nombre y precion del producto
 * @Returna la estuctructa Producto con los datos introducidos.
 * */

/*
 * @Param Todod el Inventario
 * para validad ID*/
Producto leerEntradaUsuario(Inventario *inv);

float utilidadCalc(Producto *p);

Producto buscarProduct();

Producto actualizarProduct();

Producto eliminarProducto();

void listarProductos(void);
#endif // !STOCK_H
