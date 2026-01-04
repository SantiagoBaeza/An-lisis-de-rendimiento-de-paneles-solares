[⬅️ Volver a "Proyectos en C y C++"](https://github.com/SantiagoBaeza/C-y-C-/tree/main)

# Análisis de rendimiento de paneles solares

Este proyecto implementa un programa en C que analiza el rendimiento de dos paneles solares conectados en serie, a partir de datos almacenados en un archivo binario `.dat`.  
El programa permite recorrer los datos de cada panel en orden, calcular el rendimiento de cada muestra, y mostrar el rendimiento máximo, mínimo y promedio por panel.  
La estructura del archivo incluye un encabezado con información codificada en bits, y paquetes de datos enlazados mediante índices.

---

## Contexto

Este ejercicio fue parte de un examen parcial de la materia **Informática II** en la UTN (2023).  
Se nos proporcionó un archivo binario (`pv_data.dat`) que contenía mediciones de tensión, corriente y radiación solar tomadas cada 10 segundos.  
El objetivo era recorrer los datos de cada panel siguiendo los índices enlazados, calcular el rendimiento de cada muestra usando la fórmula:

![calculo](https://github.com/SantiagoBaeza/An-lisis-de-rendimiento-de-paneles-solares/blob/main/01%20calculo%20a%20realizar.jpg)

y mostrar los valores ordenados junto con estadísticas de rendimiento.

---

## Capturas

- **Captura 01**: Lectura del encabezado y datos iniciales.  

---

## Funcionalidad clave

- Lectura del encabezado binario con máscaras de bits para extraer:
  - Dimensiones del panel (alto y ancho en mm)
  - Cantidad total de paquetes
  - Índices iniciales de cada panel
- Lectura de todos los paquetes en memoria dinámica
- Recorrido ordenado de los datos de cada panel usando `next_index`
- Cálculo de rendimiento por muestra
- Cálculo de rendimiento máximo, mínimo y promedio por panel
- Impresión en consola y escritura en archivo de texto

---

## Tecnologías utilizadas

- Lenguaje C (estándar)
- Librerías: `stdio.h`, `stdlib.h`, `stdint.h`
- Manejo de archivos binarios (`fread`)
- Operaciones con bits (`máscaras y desplazamientos`)
- Memoria dinámica (`malloc`, `free`)

---

## Comentarios finales

Este proyecto está diseñado para ejecutarse en consola y analizar el rendimiento de paneles solares a partir de datos reales.  
El archivo binario [pv_data.dat](https://github.com/SantiagoBaeza/An-lisis-de-rendimiento-de-paneles-solares/blob/main/03%20pv_data.dat) está disponible en este repositorio para que cualquier persona pueda realizar pruebas por su cuenta.  
De esta manera, es posible compilar el programa, ejecutar el análisis y comprobar el recorrido ordenado de los datos y el cálculo de rendimiento.

Este ejercicio fue una excelente práctica para reforzar el manejo de estructuras, punteros, archivos binarios y operaciones con bits en C.

---

> 🧩 Estos espacios están en construcción y se actualizan de forma frecuente.
