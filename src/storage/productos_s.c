// src/storage/productos_s.c

#include "../../include/storage/productos_s.h"
#include "../../include/models/model_inventario.h"
#include <stdio.h>
#include <stdlib.h>

/*define statements*/
#define FILENAME "Productos.csv"
#define MAX 256

// Guarda todo el inventario.
int saveProductInText(const Inventario *inv) {
  FILE *file = fopen(FILENAME, "w");

  if (file == NULL) {
    printf("[!] No se pudo abrir el archivo %s \n", FILENAME);
    return -1;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    const Producto *pro = &inv->producto[i];
    fprintf(file, "%s;%s;%s ;%.2f;%.2f;%u;%.2f\n", pro->codigo, pro->nombre,
            pro->categoria, pro->precioCompra, pro->precioVenta, pro->cantidad,
            pro->utilidad);
  }

  fclose(file);
  printf("\n[+] %d producto(s) guardado(s) correctamente en %s \n",
         inv->cantidad, FILENAME);
  return 0;
}

int readProductoFromText(Inventario *inv) {
  FILE *file = fopen(FILENAME, "r");

  if (file == NULL) {
    printf("[!] No se pudo abrir el archivo: %s. Inventario Vacio\n", FILENAME);
    inv->cantidad = 0;
    return 0;
  }

  inv->cantidad = 0;
  char linea[MAX];

  while (fgets(linea, sizeof(linea), file) != NULL &&
         inv->cantidad < MAX_PRODUCTOS) {
    Producto p = {0};

    int leido = sscanf(linea, "%[^;];%[^;];%[^;];%f;%f;%u;%f", p.codigo,
                       p.nombre, p.categoria, &p.precioCompra, &p.precioVenta,
                       &p.cantidad, &p.utilidad);
    if (leido == 7) {
      inv->producto[inv->cantidad] = p;
      inv->cantidad++;
    }
  }

  fclose(file);
  printf("[+] %d producto(s) cargados(s) desde %s\n", inv->cantidad, FILENAME);
  return 0;
}
