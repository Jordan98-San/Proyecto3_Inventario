
# 📦 Gensokyo SoftInv — Sistema de Inventario en C

Programa de consola en **C** para gestionar el inventario de productos de una bodega,
calcular utilidades y persistir la información en archivos planos (CSV).

> Proyecto académico — **Caso 1: Inventario de productos**.

---

## ✨ Características

- ✅ Registrar productos (con validación de código único)
- ✅ Listar productos con su utilidad calculada
- 🔍 Buscar por código o por subcadena del nombre
- ✏️ Actualizar productos (excepto el código)
- 🗑️ Eliminar productos con confirmación
- 💰 Cálculo de utilidad por producto y total del inventario
- 💾 Persistencia en archivo plano (CSV) con carga y guardado automático

---

## 🗂️ Estructura del proyecto

```text
.
├── include/            # Cabeceras (.h)
│   ├── menu/
│   ├── models/
│   ├── services/
│   └── storage/
├── src/                # Implementaciones (.c)
│   ├── menu/           # Menú principal / interfaz
│   ├── models/         # Structs Producto e Inventario
│   ├── services/       # Lógica: CRUD, utilidades, validaciones
│   ├── storage/        # Lectura/escritura de archivos
│   └── main.c          # Punto de entrada
├── build/              # Ejecutable generado (no se versiona)
├── Makefile            # Compilación con make (Linux/Mac)
├── compilar.bat        # Compilación rápida en Windows
└── README.md
```

### 🧱 Arquitectura por capas

```text
main.c / menú  →  services  →  models
                     ↓
                  storage  →  inventario.csv
```

Cada capa solo conoce a la de abajo mediante sus cabeceras (`.h`), lo que permite
trabajar en módulos independientes.

---

## 🛠️ Compilación

### Linux / macOS (con make)

```bash
make
./build/inventario
```

Limpiar objetos y ejecutable:

```bash
make clean
```

### Windows (CMD, sin make)

```bat
if not exist build mkdir build
gcc -Wall -Wextra -std=c17 -Iinclude src\*.c src\menu\*.c src\models\*.c src\services\*.c src\storage\*.c -o build\inventario.exe
build\inventario.exe
```

O simplemente ejecuta el script incluido:

```bat
compilar.bat
```

> Requiere **gcc** (instalable en Windows vía [MinGW-w64](https://www.mingw-w64.org/) o MSYS2).

---

## 📄 Formato del archivo (CSV)

El inventario se guarda en `inventario.csv` con separador **coma** y cabecera obligatoria:

```csv
codigo,nombre,categoria,precio_compra,precio_venta,cantidad
P001,Cuaderno,Utiles,1.25,2.10,150
P002,Lapicero,Utiles,0.20,0.50,400
```

> La **utilidad** no se almacena: se calcula en memoria al cargar los datos.

---

## 📐 Reglas de negocio

| Campo          | Regla                                         |
|----------------|-----------------------------------------------|
| `codigo`       | Único, alfanumérico sin espacios, largo 1–15  |
| `precio_compra`| Mayor que 0                                   |
| `precio_venta` | Mayor que `precio_compra`                     |
| `cantidad`     | Entero mayor o igual a 0                       |
| Eliminación    | Requiere confirmación                         |
| Actualización  | No permite dejar campos inválidos             |

---

## 👥 Organización del equipo (Git)

El trabajo se divide en **features independientes**, cada uno en su propia rama:

| Persona | Rama                              | Responsabilidad                          |
|---------|-----------------------------------|------------------------------------------|
| A       | `feature/gestion-productos`       | CRUD y validaciones (RF1)                |
| B       | `feature/persistencia-utilidades` | CSV, utilidades y menú (RF2, RF3, RF4)   |

### Flujo de trabajo

```bash
git checkout main && git pull          # actualiza la base
git checkout -b feature/mi-feature     # crea tu rama
# ...trabaja y haz commits...
git add .
git commit -m "feat: descripcion del cambio"
git push -u origin feature/mi-feature  # sube y abre un Pull Request
```

### Reglas de oro

1. `main` siempre debe compilar.
2. Nadie trabaja directo en `main`; todo va por ramas y Pull Requests.
3. No edites el módulo del compañero; si necesitas un cambio en su `.h`, acuérdenlo.
4. Haz `git pull` antes de empezar cada sesión.

---

## 📋 Requisitos técnicos cubiertos

- Arreglos · Estructuras · Funciones · Punteros · Archivos planos
- Código modular separado en archivos `.h` y `.c`

---

## 🧑‍💻 Autores

- **[JORDAN SANCHEZ]**
- **[LUIS OROSCO]**
