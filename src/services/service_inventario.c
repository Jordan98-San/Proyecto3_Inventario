#include "../../include/services/service_inventario.h"
#include <stdio.h>

void inicializarInventario(Inventario *inv) { inv->cantidad = 0; }

/*
 * @Param -> inv->cantidad = Cantidad del inventario
 * @Param -> Producto p= recibe un producto a guardar*/
void agregarProducto(Inventario *inv, Producto producto) {
  if (inv->cantidad >= MAX_PRODUCTOS) {
    printf("[!] Inventario lleno, no se puedo agregar el producto ;%s'\n ",
           producto.nombre);
    return;
  }

  inv->producto[inv->cantidad] = producto;

  inv->cantidad++;

  printf("[+] Producto '%s' agregado (total: %d). \n", producto.nombre,
         inv->cantidad);
}
