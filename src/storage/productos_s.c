// src/storage/productos_s.c

#include "../../include/storage/productos_s.h"
#include "../../include/models/model_inventario.h"
#include <stdio.h>
#include <stdlib.h>

/*define statements*/
#define FILENAME "Productos.txt"
#define MAX 100

// Guarda todo el inventario.
int saveProductInText(const Inventario *inv) {
  FILE *file = fopen(FILENAME, "w");

  if (file == NULL) {
    printf("[!] No se pudo abrir el archivo %s \n", FILENAME);
    return -1;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    const Producto *pro = &inv->producto[i];
    fprintf(file, "%s;%s;%.2f;%u\n", pro->id, pro->name, pro->precio,
            pro->stock);
    fprintf(file, "-----------------------------------\n");
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

    int leido =
        sscanf(linea, "%[^;];%[^;];%f;%u", p.id, p.name, &p.precio, &p.stock);
    if (leido == 4) {
      inv->producto[inv->cantidad] = p;
      inv->cantidad++;
    }
  }

  fclose(file);
  printf("[+] %d producto(s) cargados(s) desde %s\n", inv->cantidad, FILENAME);
  return 0;
}
