# Criba de Eratóstenes en Diferentes Lenguajes de Programación

Este repositorio contiene varias implementaciones de la Criba de Eratóstenes, un algoritmo eficiente para encontrar todos los números primos hasta un límite dado. Las implementaciones están hechas en diferentes lenguajes de programación y con diversas optimizaciones. El objetivo es medir el tiempo de ejecución de cada una y realizar un análisis comparativo.

## Implementaciones

Se han realizado las siguientes implementaciones del algoritmo:

1. **Python (Versión Básica)**  
   Implementación tradicional de la Criba de Eratóstenes en Python puro.

2. **Python con Numpy**  
   Versión optimizada utilizando la librería `numpy`, aprovechando operaciones vectorizadas para mejorar la eficiencia.

3. **C++ (Versión Básica)**  
   Implementación estándar en C++ para evaluar el rendimiento en un lenguaje compilado.

4. **C++ con OpenMP**  
   Implementación en C++ que utiliza paralelización mediante `OpenMP` para aprovechar múltiples núcleos de CPU y mejorar el tiempo de ejecución.

## Objetivo

El propósito de este proyecto es comparar el rendimiento de las diferentes implementaciones en distintos lenguajes de programación y con diferentes optimizaciones. Para ello, se mide el tiempo de ejecución al calcular los números primos hasta un límite \( N \), el cual se define dentro de cada archivo de prueba.

Además, los resultados obtenidos son analizados y resumidos en un informe final que se encuentra en este repositorio.
