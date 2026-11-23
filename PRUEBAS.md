# Pruebas

| ID | Requisito | Orden o secuencia | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|---|
| P01 | R1 | `registrar @kiwi` (dos veces) | La segunda vez: `E: No se pudo registrar @kiwi` | `Registrado: @kiwi (id 10)` y luego `E: No se pudo registrar @kiwi` | OK |
| P02 | R1 | `registrar kiwi` (sin @) | `E: No se pudo registrar kiwi` | `E: No se pudo registrar kiwi` | OK |
| P03 | R2 | `arbol` | `Nodos: 10 \| altura: 4 \| hojas: 4` | `Nodos: 10 \| altura: 4 \| hojas: 4` | OK |
| P04 | R3 | `seguir @faro @faro` | `E: Una cuenta no puede seguirse a si misma` | `E: Una cuenta no puede seguirse a si misma` | OK |
| P05 | R4 | `mutuos @cometa` y `popular` | Los que se siguen ida y vuelta con @cometa; la cuenta con mas seguidores | `Mutuos de @cometa (2): @delta @sushi` y `Popular: @cometa con 5 seguidores` | OK |
| P06 | R5 | `alcance @sushi` (orden 8) | `Alcance de @sushi: @cometa @faro @cactus @byte @delta @cuy @mango \| alcanzados: 7` | Igual | OK |
| P07 | R6 | `guardar`, `salir`, abrir, `cargar`, `arbol` | El mismo preorden, la misma altura y los mismos seguimientos | `Cargado: 11 cuentas y 17 seguimientos \| altura 5` y el mismo preorden | OK |
| P08 | R7 | `hola`, `seguir`, `perfil @nadie` | Mensajes de error; el programa sigue | `hola: orden no encontrada (escribe ayuda)` / `Uso: seguir @a @b` / `E: No existe @nadie` | OK |
| P09 | R1 | `registrar @Kiwi` (mayuscula) | `E: No se pudo registrar @Kiwi` | `E: No se pudo registrar @Kiwi` | OK |
| P10 | R2 | `registrar @lofi` y luego `arbol` | La altura sube de 4 a 5 | `altura: 5` | OK |
| P11 | R3 | `seguir @iglu @faro`, `seguidores @faro`, `dejar @iglu @faro` | @iglu aparece como seguidor y luego se quita | `@iglu sigue a @faro` / `Seguidores de @faro (3): @cactus @byte @iglu` / `@iglu dejo de seguir a @faro` | OK |
| P12 | R3 | `seguir @zz @faro` (cuenta que no existe) | `E: No existe @zz` | `E: No existe @zz` | OK |
| P13 | R3 | `seguir @sushi @lofi` dos veces (ordenes 15 y 16) | La segunda vez: `E: @sushi ya sigue a @lofi` | Igual | OK |
| P14 | R3 | `dejar @orbita @faro` (no lo sigue) | `E: @orbita no sigue a @faro` | Igual | OK |
| P15 | R4 | `popular` (orden 7) | `Popular: @cometa \| seguidores: 5` | Igual | OK |
| P16 | R5 | `llega @sushi @byte` y `llega @delta @iglu` (ordenes 9 y 10) | `si` y `no` | `Un post de @sushi llega a @byte: si` / `Un post de @delta llega a @iglu: no` | OK |
| P17 | R5 | `alcance @sushi` despues de `dejar @cometa @sushi` (orden 18) | `Alcance de @sushi: @cuy @mango \| alcanzados: 2` | Igual | OK |
| P18 | R5 | `alcance @orbita` (nadie la sigue) | `Alcance de @orbita: (nadie) \| alcanzados: 0` | Igual | OK |
| P19 | R5 | `llega @faro @faro` | `E: Elijan dos cuentas distintas` | Igual | OK |
| P20 | R6 | `cargar` sin haber guardado | `E: No existe nido.txt` | Igual | OK |
| P21 | R7 | `reporte` (orden 22) | `Cuentas: 11 \| seguimientos: 17 \| pares mutuos: 1` y `Arbol: altura 5 \| hojas 4` | Igual | OK |
| P22 | R7 | `salir` (orden 27) | `Nodos liberados: 11. Hasta pronto.` | Igual | OK |

Secuencia oficial completa: `nido.exe < pruebas\secuencia.txt > pruebas\salida.txt`. La salida esta en `pruebas/salida.txt` y el archivo que genera `guardar` en `pruebas/nido.txt`. Las 27 ordenes coinciden con la traza a mano del capitulo 2.4.

Agreguen todas las que necesiten. Incluyan casos con datos invalidos.
