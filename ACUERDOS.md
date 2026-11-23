# Acuerdos del equipo · Grupo B · nido-colibri

Si un acuerdo cambia, se actualiza aqui **con fecha**. Nada de borrar: se tacha y se escribe el nuevo.

## Integrantes

1. Flores Castillo Basiler Emanuel
2. Fernandez Ramirez Patrick Michael
3. Ticona Pacco Alex Royer
4. Machaca Apaza Edson Javier
5. Juan Diego Quispe Mollenido

## Roles y reparto

| Integrante | Rol | Requisitos o tareas | Revisa los PR de |
|---|---|---|---|
| Flores Castillo Basiler Emanuel | Lider (scrum) | Tablero, actas, merge a main, etiquetas v0.1/v0.5/v1.0, cap. 4 del informe | Juan Diego Quispe Mollenido |
| Fernandez Ramirez Patrick Michael | Dev · arbol | R1 (buscar, insertar, registrar), R2 (recorridos, contar, altura, hojas) | Ticona Pacco Alex Royer |
| Ticona Pacco Alex Royer | Dev · grafo | R3 (seguir, dejar, seguidores), R4 (mutuos, popular) | Machaca Apaza Edson Javier |
| Machaca Apaza Edson Javier | Dev · alcance y archivo | R5 (difundir DFS, alcance, llega), R6 (guardar, cargar) | Fernandez Ramirez Patrick Michael |
| Juan Diego Quispe Mollenido | QA y documentacion | R7 (reporte, liberar), PRUEBAS.md, revision del informe | Flores Castillo Basiler Emanuel |

Todos participan en el dibujo del arbol y la matriz y en la traza a mano de las ordenes 1 a 10 (Etapa 2).

## Como trabajamos

- Horarios de trabajo y de reunion: reuniones virtuales cortas a las 21:00 del 19/11, 20/11 y 22/11.
- Canal de comunicacion: grupo de WhatsApp del equipo.
- Tiempo maximo para responder un mensaje del equipo: 3 horas (en horario de 08:00 a 23:00).
- Las decisiones se registran en: Issue del tablero, pull request o acta de este archivo.
- Flujo de trabajo: una rama por requisito (`r1-registro`, `r3-seguir`, ...), commits pequeños,
  pull request revisado por la persona indicada en la tabla antes de unir a `main`. Hacer Pull antes de empezar.
- Si no estamos de acuerdo, decidimos asi: se expone cada propuesta con argumentos; si no hay
  consenso, se vota por mayoria simple y el lider desempata.
- Si alguien no puede cumplir una tarea, avisa con esta anticipacion: al menos 12 horas antes del plazo,
  para reasignarla en el tablero.

## Actas de reuniones

### Acta 1 · fecha: 19/11/2026 · medio: virtual
- Asistentes: Flores Castillo Basiler Emanuel, Fernandez Ramirez Patrick Michael, Ticona Pacco Alex Royer,
  Machaca Apaza Edson Javier, Juan Diego Quispe Mollenido
- Temas:
  - Lectura de la consigna de Nido y de la ficha del Grupo B (comunidad nido-colibri).
  - Eleccion de roles y reparto de requisitos R1 a R7.
  - Creacion del repositorio privado `nido-42964-grupoB`, invitaciones y tablero.
- Acuerdos (que · quien · para cuando):
  - Crear el repositorio con el kit, cargar la ficha B y etiquetar v0.1 · Flores · 19/11 23:59
  - Invitar a todos los integrantes y al docente · Flores · 19/11 23:59
  - Aceptar la invitacion al repositorio · todos · 19/11 23:59
  - Crear el tablero con un Issue por requisito (R1 a R7) e informe/presentacion · Flores · 19/11 23:59
  - Dibujar a mano el arbol y la matriz 10 x 10 de la ficha · todos · 20/11 18:00
  - Implementar R1 a R3 en ramas propias · Fernandez (R1, R2), Ticona (R3) · 20/11 22:00
  - Redactar capitulos 1 y 2 del informe con la traza de las ordenes 1 a 10 · Quispe, Machaca · 20/11 22:00

### Acta 2 · fecha: 20/11/2026 · medio: registro del lider (cierre de la Etapa 2)
- Asistentes: Flores Castillo Basiler Emanuel
- Temas:
  - Estado de la entrega E2 (v0.5) al cierre del 20/11.
  - Hecho: capitulos 1 y 2 del informe (`informe/capitulos-1-2.md`), arbol de la ficha en draw.io
    (`informe/arbol-colibri.drawio` y `.png`), traza a mano de las ordenes 1 a 10 · Flores · PR de `informe-cap1-2`.
  - Pendiente: R1 a R3 (no se subieron ramas al repositorio), PR de pruebas (`esperado.txt`, `PRUEBAS.md`),
    foto de la matriz 10 x 10 dibujada a mano.
  - La etiqueta v0.5 se crea con lo que esta en `main` al cierre.
- Acuerdos (que · quien · para cuando):
  - Subir R1 y R2 en su rama con PR · Fernandez · 21/11 12:00
  - Subir R3 en su rama con PR · Ticona · 21/11 12:00
  - Subir `pruebas/esperado.txt` y `PRUEBAS.md` con las lineas de R1 a R3 · Quispe · 21/11 12:00
  - Subir la foto de la matriz 10 x 10 a `informe/` · Machaca · 21/11 12:00
  - Revisar los PR segun la tabla de roles y unirlos a `main` · todos / Flores · 21/11 18:00
  - Avisar al docente del estado de la E2 · Flores · 20/11 23:59

### Acta 3 · fecha: 22/11/2026 · medio: registro del lider (cierre de la Etapa 3)
- Asistentes: Flores Castillo Basiler Emanuel
- Temas:
  - R1 y R2 entregados por Fernandez (PR #11, 21/11) y revisados por Flores.
  - R3 y R4 entregados por Ticona (PR #12, 22/11 20:52), unidos sin revision. En la revision posterior
    se encontraron diferencias con el Anexo en `seguir`, `dejar` y `popular`; las corrigio Flores en el PR #13 (22/11 22:24).
  - Al 22/11 23:00 no habia ramas de R5, R6 ni R7. Machaca no habia aceptado la invitacion al repositorio
    (pendiente desde el 20/11). Machaca y Quispe no respondieron por WhatsApp.
  - Por el plazo de la E3 (23/11 07:00), Flores implemento R5, R6 y R7 (PR #14, 22/11 23:30) y completo
    `pruebas/esperado.txt`, `pruebas/salida.txt`, `pruebas/nido.txt` y `PRUEBAS.md`.
  - Flores hizo los capitulos 3 y 4 del informe y la presentacion.
- Acuerdos (que · quien · para cuando):
  - Avisar al docente que R5, R6, R7 y las pruebas no los hicieron sus responsables · Flores · 23/11 07:00
  - Mantener a Machaca y Quispe en el informe con su rol y su aporte real · Flores · 23/11 07:00
  - Etiqueta v1.0, ZIP y entrega en el aula virtual · Flores · 23/11 07:00
