# Nido · comunidad `nido-colibri`

![Nido CI](../../actions/workflows/nido.yml/badge.svg)

Red social de consola hecha en C++ con un **arbol binario de busqueda** (las cuentas, ordenadas
por @usuario), un **grafo dirigido** en matriz de adyacencia (quien sigue a quien), **recursion**
(recorridos del arbol y DFS para el alcance de un post) y persistencia en `nido.txt`.

Estructura de Datos · Evaluacion C2 · Unidad 4 · 2026-20 · NRC `42964` · Grupo `B` · Ave: colibri

## Equipo

| Integrante | Usuario de GitHub | Rol | Requisitos |
|---|---|---|---|
| Flores Castillo Basiler Emanuel | @Basilercon | Lider (scrum) | Tablero, actas, integracion de PR |
| Fernandez Ramirez Patrick Michael | `<usuario>` | Dev · arbol | R1, R2 |
| Ticona Pacco Alex Royer | `<usuario>` | Dev · grafo | R3, R4 |
| Machaca Apaza Edson Javier | `<usuario>` | Dev · alcance y archivo | R5, R6 |
| Juan Doego Quispe Mollenido | `<usuario>` | QA y documentacion | R7, pruebas, informe |

Tablero del equipo: `<enlace a GitHub Projects>` · Presentacion: `<enlace>`

## Como compilar y ejecutar

1. Abrir `nido.cpp` en Dev-C++ y compilar (F11). Si aparece un aviso, activar C++11 en
   Herramientas > Opciones del compilador.
2. Ejecutar y escribir `ayuda`.
3. Para guardar la salida de una secuencia: `nido.exe < pruebas\secuencia.txt > pruebas\salida.txt`

## Pruebas automaticas (GitHub Actions)

En cada push, GitHub compila el programa, ejecuta `pruebas/secuencia.txt` y revisa que cada linea
de `pruebas/esperado.txt` aparezca en la salida.

- `pruebas/secuencia.txt` ya tiene la secuencia oficial de la ficha del Grupo B (27 ordenes).
- `pruebas/esperado.txt` por ahora solo tiene el punto de control de la ficha
  (`Seguidores de @delta (2): @faro @cometa`); en la Etapa 2 se agregan las lineas de la traza a mano.

Si la marca sale roja, abran la pestana **Actions** y vean que linea falta. En la v0.1 sale roja
porque R1 a R7 aun no estan implementados.

## Versiones

| Etiqueta | Entrega | Contenido |
|---|---|---|
| v0.1 | E1 | Equipo, repositorio, tablero y acuerdos |
| v0.5 | E2 | Diseno, traza a mano y los requisitos de la etapa 2 |
| v1.0 | E3 | R1 a R7, informe, pruebas, presentacion |
