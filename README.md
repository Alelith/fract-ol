# 🚀 Fract-ol - Interactive Fractal Renderer

![Estado](https://img.shields.io/badge/estado-Completado-blue)
![Lenguaje](https://img.shields.io/badge/lenguaje-C-orange)
![Librería%20Gráfica](https://img.shields.io/badge/gráficos-SDL2-yellow)
![Licencia](https://img.shields.io/badge/licencia-GPL3-green)
![Última actualización](https://img.shields.io/github/last-commit/Alelith/fract-ol)

---

## 🧠 Descripción

**Fract-ol** es un renderizador interactivo de fractales de alto rendimiento escrito en C. La aplicación permite visualizar y explorar fractales matemáticos hermosos en tiempo real, con capacidades de zoom suave, esquemas de color dinámicos y renderizado multi-hilo para un rendimiento óptimo.

El proyecto implementa cuatro tipos de fractales diferentes y proporciona una interfaz interactiva para explorar estos objetos matemáticos fascinantes. Es ideal para aprender sobre matemáticas complejas, programación en C y programación de gráficos.

---

## 🧩 Tabla de contenidos

- [Descripción](#-descripción)
- [Características](#-características)
- [Tecnologías utilizadas](#-tecnologías-utilizadas)
- [Arquitectura](#-arquitectura)
- [Estructura del proyecto](#-estructura-del-proyecto)
- [Instalación](#-instalación)
- [Ejecución](#-ejecución)
- [Configuración](#-configuración)
- [Uso o ejemplos](#-uso-o-ejemplos)
- [Capturas o demostración](#-capturas-o-demostración)
- [Documentación](#-documentación)
- [Errores conocidos / ToDo](#-errores-conocidos--todo)
- [Aprendizajes y mejoras futuras](#-aprendizajes-y-mejoras-futuras)
- [Créditos y agradecimientos](#-créditos-y-agradecimientos)
- [Licencia](#-licencia)
- [Autora](#-autora)

---

## 🌟 Características

- ✅ **Renderizado en tiempo real**: Computación de fractales multi-hilo para interacción responsiva
- ✅ **Zoom interactivo**: Zoom centrado en la posición del cursor con rueda del ratón
- ✅ **Esquemas de color dinámicos**: Múltiples paletas de color incluyendo mapeo HSV y efectos psicodélicos
- ✅ **Alto rendimiento**: Renderizado paralelo con 8 workers simultáneos
- ✅ **Matemáticas complejas**: Aritmética de números complejos incluyendo operaciones trigonométricas
- ✅ **Múltiples fractales**: Mandelbrot clásico, Julia, Eye Mandelbrot, Sinh Mandelbrot y Dragon Mandelbrot
- 🔄 **Futuras mejoras**: Optimizaciones de rendimiento para zooms extremos, más variaciones de fractales

---

## ⚙️ Tecnologías utilizadas

| Categoría | Tecnología |
|-----------|-----------|
| **Lenguaje** | C (C99 estándar) |
| **Compilador** | GCC / Clang |
| **Gráficos** | SDL2 (Simple DirectMedia Layer 2) |
| **Parallelismo** | POSIX Threads (pthread) |
| **Matemáticas** | Aritmética de números complejos, cálculos trigonométricos |
| **Herramientas** | Make, Doxygen (documentación) |
| **Sistema Operativo** | Linux (verificado) |

---

## 🏗️ Arquitectura

La aplicación está estructurada en módulos especializados:

### Módulos principales:

**Complex Number Operations** (`src/complex/`):
- Operaciones aritméticas: multiplicación, suma, división, inversión
- Funciones trigonométricas complejas (seno hiperbólico)
- Cálculo de módulo para detección de divergencia

**Fractal Rendering** (`src/fractals/`):
- **Mandelbrot Set**: z = z² + c con c como coordenada del píxel
- **Julia Set**: z_{n+1} = z_n² + c con parámetro c fijo personalizables
- **Eye Mandelbrot**: Variación con iteración z³
- **Sinh Mandelbrot**: Utilizando operaciones de seno hiperbólico
- **Dragon Mandelbrot**: Variación adicional del conjunto de Mandelbrot

**Utilities** (`src/utils/`):
- Gestión de imágenes y buffer de píxeles
- Esquemas de color y mapeo HSV
- Manejo de eventos y entrada del usuario

**Survival Library** (`lib/survival_lib/`):
- Funciones personalizadas de utilidad: manejo de strings, memoria, conversiones
- Printf personalizado con soporte para formato
- Abstracciones de bajo nivel reutilizables

### Flujo de ejecución:
1. Inicialización de SDL2 y creación de ventana
2. Análisis de argumentos para seleccionar tipo de fractal
3. Spawn de threads workers para cálculo paralelo
4. Loop principal de eventos: captura entrada, actualiza zoom/parámetros
5. Renderizado: cada worker calcula sección del fractal
6. Presentación en pantalla y sincronización

```
┌─────────────────────────────────────┐
│      Event Loop (Main Thread)        │
│  - Handle zoom/input              │
│  - Update fractal parameters      │
└──────────────┬──────────────────────┘
               │
               ├─→ [Worker Thread 1] → Compute Fractal Section
               ├─→ [Worker Thread 2] → Compute Fractal Section
               ├─→ [Worker Thread 3] → Compute Fractal Section
               └─→ [Worker Thread 4+] → Compute Fractal Section
               │
               ↓
        ┌─────────────────┐
        │ Render to Screen│
        └─────────────────┘
```

---

## 📂 Estructura del proyecto

```
fract-ol/
├── include/                          # Headers principales
│   ├── fract_ol.h                   # Definiciones y estructuras principales
│   └── survival_lib.h               # Headers de la librería personalizada
├── src/                             # Código fuente
│   ├── main.c                       # Punto de entrada y setup inicial
│   ├── complex/                     # Operaciones con números complejos
│   │   ├── complex_operations.c     # Suma, resta, multiplicación, división
│   │   └── complex_trigonometric.c  # Seno hiperbólico y funciones trigonométricas
│   ├── fractals/                    # Algoritmos de renderizado de fractales
│   │   ├── fractal_render.c         # Motor de renderizado principal
│   │   ├── mandelbrot.c             # Implementación del conjunto de Mandelbrot
│   │   ├── julia.c                  # Implementación del conjunto de Julia
│   │   ├── eye_mandelbrot.c         # Variación Eye (z³)
│   │   ├── sinh_mandelbrot.c        # Variación Sinh
│   │   └── dragon_mandelbrot.c      # Variación Dragon
│   └── utils/                       # Utilidades
│       ├── color.c                  # Paletas de color y mapeo HSV
│       ├── handlers.c               # Manejadores de eventos
│       ├── img_manag.c              # Gestión de buffer de píxeles
│       └── string.c                 # Funciones de string auxiliares
├── lib/
│   └── survival_lib/                # Librería personalizada de utilidades
│       ├── include/
│       │   └── survival_lib.h
│       └── src/
│           ├── check/               # Funciones de validación
│           ├── conversion/          # Conversión de tipos
│           ├── memory/              # Gestión de memoria
│           ├── printf/              # Printf personalizado
│           └── string/              # Funciones de string
├── Makefile                         # Compilación del proyecto
├── Doxyfile                         # Configuración de documentación
├── LICENSE                          # Licencia GPL3
└── README.md                        # Este archivo
```

## 📦 Instalación

### 🔧 Requisitos previos

- **Compilador**: GCC o Clang con soporte para C99
- **Build system**: GNU Make
- **Gráficos**: SDL2 (Simple DirectMedia Layer 2)
- **Sistema operativo**: Linux (o compatible con POSIX Threads)

**Opcional:**
- **Doxygen**: Para generar documentación localmente

#### En Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install build-essential libsdl2-dev
# Opcional - para documentación
sudo apt-get install doxygen
```

#### En Fedora/RHEL:
```bash
sudo dnf install gcc make SDL2-devel
# Opcional - para documentación
sudo dnf install doxygen
```

#### En macOS (con Homebrew):
```bash
brew install sdl2
# Opcional - para documentación
brew install doxygen
```

### 💾 Pasos de instalación

1. **Clonar el repositorio**:
```bash
git clone https://github.com/Alelith/fract-ol.git
cd fract-ol
```

2. **Compilar el proyecto**:
```bash
make
```

3. **Compilar con documentación (opcional)**:
```bash
make docs
```

El ejecutable `fractol` se generará en el directorio raíz.

---

## ▶️ Ejecución

La aplicación se ejecuta desde la línea de comandos especificando el tipo de fractal a renderizar:

```bash
./fractol mandelbrot
./fractol julia <real_part> <imaginary_part>
./fractol eye
./fractol sinh
./fractol dragon
```

### Ejemplos:

```bash
# Renderizar el conjunto de Mandelbrot clásico
./fractol mandelbrot

# Renderizar un conjunto de Julia con parámetros C = 0.285 + 0.01i
./fractol julia 0.285 0.01

# Renderizar variaciones
./fractol eye
./fractol sinh
./fractol dragon
```

### Controles:

| Control | Acción |
|---------|--------|
| **Rueda arriba** | Zoom in (centrado en el cursor) |
| **Rueda abajo** | Zoom out |
| **ESC** | Cerrar la aplicación |
| **Movimiento ratón** | Actualiza información en tiempo real durante zoom |

## ⚙️ Configuración

### Parámetros compilación

El Makefile incluye varios objetivos útiles:

```bash
make              # Compila el proyecto
make clean        # Elimina archivos objeto
make fclean       # Limpieza completa (archivos objeto y ejecutable)
make re           # Limpieza completa y recompilación
make docs         # Genera documentación con Doxygen
```

### Variables del programa

Los siguientes parámetros pueden configurarse en tiempo de compilación (editando `include/fract_ol.h`):

- **WIDTH / HEIGHT**: Dimensiones de la ventana (por defecto: 1920x1440)
- **MAX_ITERATIONS**: Número máximo de iteraciones para calcular divergencia (por defecto: 256)
- **NUM_THREADS**: Número de workers (por defecto: 8)

---

## 🧪 Uso o ejemplos

### Explorando el conjunto de Mandelbrot

1. Ejecutar: `./fractol mandelbrot`
2. Usar la rueda del ratón para hacer zoom
3. Acercar en regiones interesantes para ver la autosimilitud fractal

### Jugando con Julia sets

Diferentes parámetros producen conjuntos visuales completamente distintos:

```bash
# Espiral de fuego
./fractol julia -0.7 0.27015

# Conjunto dentado
./fractol julia -0.4 0.6

# Galaxia
./fractol julia -0.162 1.04
```

### Comparando variaciones

```bash
# Mandelbrot clásico
./fractol mandelbrot

# Mandelbrot con Z³ (Eye)
./fractol eye

# Mandelbrot con seno hiperbólico
./fractol sinh

# Dragon Mandelbrot
./fractol dragon
```

### Workflow típico

1. Seleccionar tipo de fractal
2. Identificar región interesante
3. Hacer zoom gradualmente para explorar detalles
4. Observar cómo diferentes esquemas de color revelan estructuras distintas

---

## 📸 Capturas o demostración

> **📝 Nota**: Se recomienda ejecutar el programa y explorar interactivamente los diferentes fractales. Cada screenshot tiene características únicas según el nivel de zoom y los parámetros utilizados.

### Fractales implementados:

- **Mandelbrot Set**: El clásico conjunto de Mandelbrot con estructura autosimilar infinita
- **Julia Set**: Conjuntos complejos generados por parámetros personalizables
- **Eye Mandelbrot**: Variación visual distintiva con iteración z³
- **Sinh Mandelbrot**: Visualización única usando funciones hiperbólicas
- **Dragon Mandelbrot**: Otra fascinante variación del conjunto clásico

*Captura de pantalla pendiente de actualizar - ejecutar `./fractol mandelbrot` para ver en vivo*

---

## 📖 Documentación

La documentación completa del código está generada con Doxygen. Puedes consultarla en:

🔗 **[Documentación del Código](DOCUMENTATION_URL)** *(pendiente de publicar)*

Para generar la documentación localmente:
```bash
make docs
```

La documentación incluye:
- Descripción detallada de todas las funciones y estructuras
- Diagramas de relaciones entre módulos
- Ejemplos de uso de las APIs internas
- Guía de arquitectura

---

## 🐞 Errores conocidos / ToDo

### Problemas conocidos:

| Severidad | Descripción | Estado |
|-----------|-------------|--------|
| 🟡 Media | Degradación de rendimiento con zooms extremos (>100x) | Abierto - Requiere optimización |

### Mejoras futuras planeadas:

- [ ] Optimización de rendimiento para zooms ultra profundos
- [ ] Más variaciones de fractales (Tricorn, Burning Ship, etc.)
- [ ] Modo grabación de animaciones de zoom
- [ ] Paleta de colores personalizable en tiempo de ejecución
- [ ] Exportación de imágenes en alta resolución
- [ ] Soporte multi-plataforma completo (macOS, Windows)

---

## 🧭 Aprendizajes y mejoras futuras

### 📚 Aprendizajes principales

1. **Programación de Gráficos en C**: Dominio de SDL2 para renderizado en tiempo real
   - Gestión de eventos, buffer de píxeles y sincronización de pantalla
   - Optimización de performance en computación gráfica

2. **Matemáticas de Fractales**: Comprensión profunda de conjuntos de Mandelbrot y Julia
   - Números complejos y aritmética compleja
   - Algoritmos de iteración y detección de divergencia
   - Visualización de estructuras matemáticas infinitas

3. **Programación Concurrente**: Implementación de renderizado paralelo
   - POSIX Threads para computación multi-hilo
   - Sincronización entre threads sin race conditions
   - División eficiente de trabajo computacional

4. **Gestión de Memoria en C**: Prácticas robustas de asignación y liberación
   - Perfilado de memoria bajo carga
   - Optimización de estructuras de datos

### 🚀 Mejoras futuras consideradas

- **Performance**: Investigar SIMD (SSE/AVX) para vectorización de cálculos complejos
- **Más Fractales**: Tricorn, Burning Ship, Newton fractals
- **Interactividad**: Interfaz de parámetros en tiempo real
- **Portabilidad**: Verificar compatibilidad con macOS y Windows
- **Visualización**: Modos 3D, mapeo de profundidad, raytracing fractal

---

## 🤝 Créditos y agradecimientos

- **Matemáticas de Fractales**: Basado en teoría de Benoit Mandelbrot y Gaston Julia
- **SDL2**: Simple DirectMedia Layer - Librería gráfica multiplataforma
- **Referencias**: 
  - [Wikipedia - Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set)
  - [Wikipedia - Julia set](https://en.wikipedia.org/wiki/Julia_set)
  - [SDL2 Documentation](https://wiki.libsdl.org/)

---

## 📜 Licencia

Este proyecto está licenciado bajo la **Licencia GNU General Public License v3 (GPL3)** - ver el archivo [LICENSE](LICENSE) para más detalles.

La licencia GPL3 requiere:
- 📋 Incluir el aviso de licencia y copyright
- 📝 Documentar cambios realizados
- 📦 Disponibilidad de código fuente
- 🔄 Cambios bajo la misma licencia

Cualquier trabajo derivado debe ser distribuido bajo la misma licencia GPL3.

---

## 👩‍💻 Autora

**Lilith Estévez Boeta**

Programadora Backend & Multiplataforma  
📍 Málaga, España  
🔗 [GitHub](https://github.com/Alelith) · [LinkedIn](https://www.linkedin.com/in/alelith/)

---

<p align="center">
  <b>⭐ Si te gusta este proyecto, no olvides dejar una estrella en GitHub ⭐</b>
</p>
