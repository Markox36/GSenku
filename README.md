# 🟢 GSenku (Peg Solitaire) Resolver

**GSenku** es un "resolver" del clásico juego **Senku (o Peg Solitaire)** desarrollado en **C++**, diseñado para ejecutarse en **consola** con un **visualizador de movimientos**.  
Proyecto desarrollado como parte de una actividad de la **Universidad de Zaragoza**.

## ⚙️ Ejecución

### 📌 Estructura general del comando

```bash
./ejecutable <ruta_tablero> <ruta_movimiento> <retardo> [fichero_salida]
```

- `<ruta_tablero>` → Archivo `.txt` con la definición del tablero.
- `<ruta_movimiento>` → Archivo `.txt` con el conjunto de movimientos permitidos.
- `<retardo>` → Tiempo (en ms) entre movimientos al visualizar en consola.
- `[fichero_salida]` (opcional) → Archivo de salida para guardar la solución.

### 📌 Ejemplo real

```bash
.\bin\mainGSenku .\data\tableros\tableroEuropeo.txt .\data\movimientos\movimientosCompletos.txt 1 sol.txt
```

---

## 📂 Estructura del proyecto

```bash
├── .vscode/             # Configuración de entorno (VS Code)
├── bin/                 # Ejecutables generados
├── data/                # Datos de entrada del juego
│   ├── movimientos/     # Archivos de movimientos disponibles
│   │   ├── movimientosClasicos.txt
│   │   ├── movimientosCompletos.txt
│   │   └── movimientosDiagonal.txt
│   └── tableros/        # Diferentes tableros iniciales
│       ├── tableroEuropeo.txt
│       ├── tableroIngles.txt
│       ├── tableroTriangular.txt
│       └── ...
├── src/                 # Código fuente
│   ├── GSenku.cpp
│   ├── GSenku.hpp
│   └── mainGSenku.cpp
├── LICENSE              # Licencia del proyecto
├── Makefile             # Compilación simplificada
└── README.md            # Este archivo
```

## 📊 Compatibilidad Tableros vs Movimientos

| Tablero           | Movs. clásicos | Movs. diagonal | Movs. completos |
| ----------------- | -------------- | -------------- | --------------- |
| tableroDos        | ✅             | ❌             | ✅              |
| tableroEuropeo    | ❌             | ❌             | ✅              |
| tableroIngles     | ❌             | ❌             | ✅              |
| tableroRaroArriba | ❌             | ❌             | ✅              |
| tableroRombo      | ❌             | ❌             | ✅              |
| tableroTres       | ✅             | ❌             | ✅              |
| tableroTriangular | ❌             | ❌             | ✅              |

## 👥 Colaboradores

- [heeectoor21](https://github.com/heeectoor21)
