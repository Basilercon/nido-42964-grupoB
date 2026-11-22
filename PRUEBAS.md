# Pruebas

| ID | Requisito | Orden o secuencia | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|---|
| P01 | R1 | `registrar @kiwi` (dos veces) | La segunda vez: `E: No se pudo registrar @kiwi` | `Registrado: @kiwi (id 10)` y luego `E: No se pudo registrar @kiwi` | OK |
| P02 | R1 | `registrar kiwi` (sin @) | `E: No se pudo registrar kiwi` | `E: No se pudo registrar kiwi` | OK |
| P03 | R2 | `arbol` | `Nodos: 10 \| altura: 4 \| hojas: 4` | `Nodos: 10 \| altura: 4 \| hojas: 4` | OK |
| P04 | R3 | `seguir @a @a` | `E: Una cuenta no puede seguirse a si misma` |  |  |
| P05 | R4 |  |  |  |  |
| P06 | R5 |  |  |  |  |
| P07 | R6 | `guardar`, `salir`, abrir, `cargar`, `arbol` | El mismo preorden, la misma altura y los mismos seguimientos |  |  |
| P08 | R7 | `hola`, `seguir`, `perfil @nadie` | Mensajes de error; el programa sigue |  |  |
| P09 | R1 | `registrar @Kiwi` (mayuscula) | `E: No se pudo registrar @Kiwi` | `E: No se pudo registrar @Kiwi` | OK |
| P10 | R2 | `registrar @lofi` y luego `arbol` | La altura sube de 4 a 5 | `altura: 5` | OK |
Agreguen todas las que necesiten. Incluyan casos con datos invalidos.
