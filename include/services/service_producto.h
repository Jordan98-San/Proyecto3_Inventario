#ifndef STOCK_H
#define STOCK_H

#include "../models/model_inventario.h"
#include "../models/model_productos.h"

void generarIdAleatorio(char *id); // ID -> ya conoce su longitud = 8

int validarIdUnico(Inventario *inv, char *id);

Producto crearProduct(const char *name, float precio);

/*
 * Leer los datos de un producto desde la entrada estandar
 * Solicita al usuario que introduzca el nombre y precio del producto
 * @Retorna la estructura Producto con los datos introducidos.
 * */

/*
 * @Param Todo el Inventario
 * para validar ID
 */
Producto leerEntradaUsuario(Inventario *inv);

float utilidadCalc(Producto *p);

/*
 * Busca un producto por su ID/codigo
 * @Param -> Recibe un producto del inventario
 * @Param -> Un ID esto para comparar.
 */
Producto *buscarPorID(Inventario *inv, char *id);

/*
 * Muestra en pantalla los datos de un producto buscado por codigo.
 * @Param -> Recibe todo el inventario.
 * @Param -> Recibe el codigo que se desea buscar.
 */
void mostrarProductoPorID(Inventario *inv, char *id);

Producto buscarProduct();

Producto actualizarProduct();

Producto eliminarProducto();

void listarProductos(Inventario *inv);

#endif // !STOCK_H