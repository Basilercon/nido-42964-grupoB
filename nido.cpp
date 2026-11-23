/* =============================================================
   Curso      : Estructura de Datos (24UC00428)
   Evaluacion : C2 - Unidad 4 - Semana 15
   Proyecto   : Nido, la red social del campus (kit base)
   Institucion: Universidad Continental
   Docente    : Carlos del Carpio
   Semestre   : 2026-20
   Compilador : Dev-C++ (MinGW / GCC, C++11 o superior)
   NRC        : 42964
   Grupo      : B (comunidad nido-colibri)
   Integrantes: Flores Castillo Basiler Emanuel
                Fernandez Ramirez Patrick Michael
                Ticona Pacco Alex Royer
                Machaca Apaza Edson Javier
                Juan Diego Quispe Mollenido
   ============================================================= */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

const int MAX = 12;
const string ARCHIVO = "nido.txt";

struct NodoUsuario {
    string usuario;
    int    id;
    NodoUsuario *izq, *der;
};

int sigue[MAX][MAX];
NodoUsuario *porId[MAX];
int nUsuarios = 0;

// ===== FICHA ===== (Grupo B, copiada tal cual de la ficha)
const string COMUNIDAD = "nido-colibri";
const int N_U = 10;
string fUsuario[N_U] = {"@faro", "@cometa", "@orbita", "@cactus", "@delta",
                        "@sushi", "@byte", "@cuy", "@mango", "@iglu"};
const int N_S = 16;
string fSigue[N_S][2] = {{"@cometa", "@delta"}, {"@faro", "@cometa"},
                         {"@mango", "@cometa"}, {"@cometa", "@sushi"},
                         {"@delta", "@cometa"}, {"@sushi", "@cometa"},
                         {"@mango", "@sushi"}, {"@cuy", "@sushi"},
                         {"@cuy", "@iglu"}, {"@cactus", "@faro"},
                         {"@faro", "@delta"}, {"@delta", "@byte"},
                         {"@cuy", "@cometa"}, {"@byte", "@faro"},
                         {"@sushi", "@iglu"}, {"@cometa", "@cactus"}};
// =================

NodoUsuario* crearUsuario(string usuario, int id) {
    NodoUsuario *n = new NodoUsuario;
    n->usuario = usuario; n->id = id;
    n->izq = n->der = nullptr;
    return n;
}

bool esUsuarioValido(string u) {
    if (u.size() < 2 || u.size() > 16 || u[0] != '@') return false;
    for (int i = 1; i < (int)u.size(); i++)
        if (!((u[i] >= 'a' && u[i] <= 'z') || (u[i] >= '0' && u[i] <= '9'))) return false;
    return true;
}

void imprimirMarcados(string titulo, bool marca[]) {
    int k = 0;
    for (int x = 0; x < nUsuarios; x++) if (marca[x]) k++;
    cout << titulo << " (" << k << "):";
    if (k == 0) cout << " (nadie)";
    for (int x = 0; x < nUsuarios; x++) if (marca[x]) cout << " " << porId[x]->usuario;
    cout << endl;
}

/* ---------- Arbol binario de busqueda (todo recursivo) ---------- */

// R1a - buscar: devuelve el nodo de la cuenta u, o nullptr si no existe.
// Caso base 1: arbol vacio (r == nullptr). Caso base 2: r->usuario == u (lo encontro).
// Caso recursivo: si u es menor baja por la izquierda; si no, por la derecha.
NodoUsuario* buscar(NodoUsuario *r, string u) {
    if (r == nullptr || r->usuario == u) return r;
    if (u < r->usuario) return buscar(r->izq, u);
    return buscar(r->der, u);
}

// R1b - insertar: cuelga el nodo nuevo en el hueco que le corresponde.
// r va por referencia (*&) para poder cambiar el puntero del padre (o la raiz).
// Caso base 1: hueco (nullptr). Caso base 2: cuenta repetida -> false.
bool insertar(NodoUsuario *&r, NodoUsuario *nuevo) {
    if (r == nullptr) { r = nuevo; return true; }
    if (nuevo->usuario == r->usuario) return false;
    if (nuevo->usuario < r->usuario) return insertar(r->izq, nuevo);
    return insertar(r->der, nuevo);
}

// R1c - registrarUsuario: valida, crea el nodo con el siguiente id, lo inserta y llena porId.
bool registrarUsuario(NodoUsuario *&raiz, string u) {
    if (!esUsuarioValido(u)) return false;
    if (nUsuarios == MAX) return false;
    if (buscar(raiz, u) != nullptr) return false;
    NodoUsuario *nodo = crearUsuario(u, nUsuarios);
    insertar(raiz, nodo);
    porId[nUsuarios] = nodo;
    nUsuarios++;
    return true;
}
// R2a - enorden: izquierda, nodo, derecha (sale alfabetico). Caso base: arbol vacio.
void enorden(NodoUsuario *r) {
    if (r == nullptr) return;
    enorden(r->izq);
    cout << " " << r->usuario;
    enorden(r->der);
}


// R2b - preorden: nodo, izquierda, derecha. Caso base: arbol vacio.
void preorden(NodoUsuario *r) {
    if (r == nullptr) return;
    cout << " " << r->usuario;
    preorden(r->izq);
    preorden(r->der);
}

// R2c - contar: arbol vacio = 0; si no, 1 + los de cada subarbol.
int contar(NodoUsuario *r) {
    if (r == nullptr) return 0;
    return 1 + contar(r->izq) + contar(r->der);
}

// R2d - altura en niveles: vacio = 0; si no, 1 + la altura del subarbol mas alto.
int altura(NodoUsuario *r) {
    if (r == nullptr) return 0;
    int a = altura(r->izq);
    int b = altura(r->der);
    if (a > b) return 1 + a;
    return 1 + b;
}

// R2e - hojas: vacio = 0; nodo sin hijos = 1; si no, suma de los subarboles.
int hojas(NodoUsuario *r) {
    if (r == nullptr) return 0;
    if (r->izq == nullptr && r->der == nullptr) return 1;
    return hojas(r->izq) + hojas(r->der);
}

/* ---------- Grafo dirigido: matriz de adyacencia sigue ---------- */

int contarSiguiendo(int id) {
    int k = 0;
    for (int x = 0; x < nUsuarios; x++) if (sigue[id][x] == 1) k++;
    return k;
}

/* =========================================================================
   MI PARTE - R3a: CONTAR SEGUIDORES
   funcion: Devuelve cuantos seguidores tiene el usuario con ese 'id'.
   Guia : Recorre toda la COLUMNA 'id' en la matriz sigue[x][id]
          contando cada '1' (grado de entrada en el grafo dirigido).
   ========================================================================= */
// R3a - contarSeguidores: cuenta los 1 de la columna id (quienes siguen a id).
int contarSeguidores(int id) {
    int k = 0;
    for (int x = 0; x < nUsuarios; x++) if (sigue[x][id] == 1) k++;
    return k;
}

void difundir(int v, bool visto[], bool imprimir) {
    // R5a: DFS. caso base: v no tiene seguidores sin visitar
    visto[v] = true;
    for (int x = 0; x < nUsuarios; x++) {
        if (sigue[x][v] == 1 && !visto[x]) {
            if (imprimir) cout << " " << porId[x]->usuario;
            difundir(x, visto, imprimir);
        }
    }
}

/* ---------- Archivos y memoria ---------- */

void guardarPreorden(NodoUsuario *r, ofstream &f) {
    // R6a: una linea U por cuenta, en preorden
    if (r == nullptr) return;
    f << "U " << r->usuario << " " << r->id << endl;
    guardarPreorden(r->izq, f);
    guardarPreorden(r->der, f);
}

int liberar(NodoUsuario *r) {
    // R7a: postorden, primero los hijos y despues el nodo
    if (r == nullptr) return 0;
    int k = liberar(r->izq) + liberar(r->der);
    delete r;
    return k + 1;
}

/* ---------- Ordenes ---------- */

void leerOrden(string linea, string &orden, string &a1, string &a2) {
    string t[6]; int n = 0;
    stringstream ss(linea);
    while (n < 6 && ss >> t[n]) n++;
    orden = a1 = a2 = "";
    if (n == 0) return;
    string c = t[0];
    if (c == "signup") c = "registrar";
    else if (c == "whois") c = "perfil";
    else if (c == "users") c = "usuarios";
    else if (c == "tree") c = "arbol";
    else if (c == "follow") c = "seguir";
    else if (c == "unfollow") c = "dejar";
    else if (c == "followers") c = "seguidores";
    else if (c == "following") c = "siguiendo";
    else if (c == "mutuals") c = "mutuos";
    else if (c == "trending") c = "popular";
    else if (c == "reach") c = "alcance";
    else if (c == "reaches") c = "llega";
    else if (c == "save") c = "guardar";
    else if (c == "load") c = "cargar";
    else if (c == "stats") c = "reporte";
    else if (c == "help" || c == "man") c = "ayuda";
    else if (c == "exit" || c == "quit") c = "salir";
    orden = c;
    if (n > 1) a1 = t[1];
    if (n > 2) a2 = t[2];
}

void ayuda() {
    cout << "  ORDEN                   EN INGLES            QUE HACE" << endl;
    cout << "  registrar @u            signup @u            crear una cuenta (ABB: insertar)" << endl;
    cout << "  perfil @u               whois @u             ver una cuenta (ABB: buscar)" << endl;
    cout << "  usuarios                users                cuentas en orden alfabetico (enorden)" << endl;
    cout << "  arbol                   tree                 preorden, nodos, altura y hojas" << endl;
    cout << "  seguir @a @b            follow @a @b         @a empieza a seguir a @b" << endl;
    cout << "  dejar @a @b             unfollow @a @b       @a deja de seguir a @b" << endl;
    cout << "  seguidores @u           followers @u         quienes siguen a @u" << endl;
    cout << "  siguiendo @u            following @u         a quienes sigue @u" << endl;
    cout << "  mutuos @u               mutuals @u           se siguen los dos" << endl;
    cout << "  popular                 trending             cuenta con mas seguidores" << endl;
    cout << "  alcance @u              reach @u             a quienes llega un post de @u (DFS)" << endl;
    cout << "  llega @a @b             reaches @a @b        un post de @a llega a @b?" << endl;
    cout << "  guardar / cargar        save / load          archivo nido.txt" << endl;
    cout << "  reporte                 stats                resumen de la comunidad" << endl;
    cout << "  salir                   exit                 terminar" << endl;
}

int main() {
    NodoUsuario *raiz = nullptr;
    for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) sigue[i][j] = 0;

    for (int i = 0; i < N_U; i++) registrarUsuario(raiz, fUsuario[i]);
    for (int i = 0; i < N_S; i++) {
        NodoUsuario *a = buscar(raiz, fSigue[i][0]);
        NodoUsuario *b = buscar(raiz, fSigue[i][1]);
        if (a != nullptr && b != nullptr) sigue[a->id][b->id] = 1;
    }

    cout << "Nido - comunidad " << COMUNIDAD << " (" << nUsuarios << " cuentas). Escribe ayuda." << endl;

    string linea;
    while (true) {
        cout << "nido@" << COMUNIDAD << ":~$ ";
        if (!getline(cin, linea)) break;
        string orden, a1, a2;
        leerOrden(linea, orden, a1, a2);
        if (orden == "") continue;
        cout << "> " << linea << endl;

        if (orden == "registrar") {
            // R1d - registrar @usuario
            if (a1 == "") cout << "Uso: registrar @usuario" << endl;
            else if (registrarUsuario(raiz, a1))
                cout << "Registrado: " << a1 << " (id " << nUsuarios - 1 << ")" << endl;
            else cout << "E: No se pudo registrar " << a1 << endl;
        }
        else if (orden == "perfil") {
            NodoUsuario *u = buscar(raiz, a1);
            if (u == nullptr) cout << "E: No existe " << a1 << endl;
            else cout << u->usuario << " | id " << u->id << " | seguidores " << contarSeguidores(u->id)
                      << " | siguiendo " << contarSiguiendo(u->id) << endl;
        }
        else if (orden == "usuarios") {
            cout << "Usuarios (enorden):";
            enorden(raiz);
            cout << endl;
        }
        else if (orden == "arbol") {
            cout << "Preorden:";
            preorden(raiz);
            cout << endl;
            cout << "Nodos: " << contar(raiz) << " | altura: " << altura(raiz) << " | hojas: " << hojas(raiz) << endl;
        }
        /* =========================================================================
       R3b: COMANDO SEGUIR (@a empieza a seguir a @b)
       funcion: Crea una arista dirigida de @a hacia @b en la matriz.
      guia : 1) Busca @a y @b en el arbol ABB para sacar sus IDs.
                           2) Valida errores: argumentos vacios, cuentas inexistentes,
                              auto-seguirse (a == b) o seguimiento duplicado (== 1).
                           3) Marca sigue[a->id][b->id] = 1 (fila = quien sigue).
           ========================================================================= */
        else if (orden == "seguir") {
            // R3b
            NodoUsuario *a = buscar(raiz, a1);
            NodoUsuario *b = buscar(raiz, a2);
            if (a1 == "" || a2 == "") cout << "Uso: seguir @a @b" << endl;
            else if (a == nullptr) cout << "E: No existe " << a1 << endl;
            else if (b == nullptr) cout << "E: No existe " << a2 << endl;
            else if (a == b) cout << "E: Una cuenta no puede seguirse a si misma" << endl;
            else if (sigue[a->id][b->id] == 1) cout << "E: " << a1 << " ya sigue a " << a2 << endl;
            else {
                sigue[a->id][b->id] = 1;
                cout << a1 << " ahora sigue a " << a2 << endl;
            }
        }
        /* =========================================================================
          R3c: COMANDO DEJAR (@a deja de seguir a @b)
         función: Elimina una relacion de seguimiento existente en la matriz.
          Guia : Aplica las mismas validaciones que 'seguir', verifica que
                           si lo siga (== 0 da error) y pone sigue[a->id][b->id] = 0.
           ========================================================================= */
        else if (orden == "dejar") {
            // R3c
            NodoUsuario *a = buscar(raiz, a1);
            NodoUsuario *b = buscar(raiz, a2);
            if (a1 == "" || a2 == "") cout << "Uso: dejar @a @b" << endl;
            else if (a == nullptr) cout << "E: No existe " << a1 << endl;
            else if (b == nullptr) cout << "E: No existe " << a2 << endl;
            else if (a == b) cout << "E: Una cuenta no puede seguirse a si misma" << endl;
            else if (sigue[a->id][b->id] == 0) cout << "E: " << a1 << " no sigue a " << a2 << endl;
            else {
                sigue[a->id][b->id] = 0;
                cout << a1 << " dejo de seguir a " << a2 << endl;
            }
        }
        else if (orden == "siguiendo") {
            NodoUsuario *u = buscar(raiz, a1);
            if (u == nullptr) cout << "E: No existe " << a1 << endl;
            else {
                bool marca[MAX] = {false};
                for (int x = 0; x < nUsuarios; x++) if (sigue[u->id][x] == 1) marca[x] = true;
                imprimirMarcados(u->usuario + " sigue a", marca);
            }
        }
        /* =========================================================================
           R3d: COMANDO SEGUIDORES (quienes siguen a @u)
           Para que sirve: Lista los nombres de todos los usuarios que siguen a @u.
           Guia: Recorre la COLUMNA de @u (sigue[x][u->id] == 1), guarda en
                           marca[x] = true los indices y los imprime con porId[x].
           ========================================================================= */
        else if (orden == "seguidores") {
            // R3d - seguidores @u: marca a los x que tienen 1 en la columna de u.
            NodoUsuario *u = buscar(raiz, a1);
            if (u == nullptr) cout << "E: No existe " << a1 << endl;
            else {
                bool marca[MAX] = {false};
                for (int x = 0; x < nUsuarios; x++) if (sigue[x][u->id] == 1) marca[x] = true;
                imprimirMarcados("Seguidores de " + u->usuario, marca);
            }
        }
        /* =========================================================================
            R4a: COMANDO MUTUOS (seguimiento reciproco con @u)
           Para que sirve: Muestra con quienes @u tiene seguimiento de ida y vuelta.
           Guia : Revisa que haya '1' en ambas direcciones de la matriz:
                           sigue[u][x] == 1 (u sigue a x) && sigue[x][u] == 1 (x sigue a u).
           ========================================================================= */
        else if (orden == "mutuos") {
            // R4a - mutuos @u: u sigue a x y x sigue a u.
            NodoUsuario *u = buscar(raiz, a1);
            if (u == nullptr) cout << "E: No existe " << a1 << endl;
            else {
                bool marca[MAX] = {false};
                for (int x = 0; x < nUsuarios; x++)
                    if (sigue[u->id][x] == 1 && sigue[x][u->id] == 1) marca[x] = true;
                imprimirMarcados("Mutuos de " + u->usuario, marca);
            }
        }
        /* =========================================================================
            R4b: COMANDO POPULAR (cuenta con mas seguidores)
           funcion: Encuentra y muestra la cuenta con mayor cantidad de seguidores.
           Guia  : Empieza asumiendo mejor = 0 y compara contarSeguidores(x).
                           Usa '>' estricto para que en empate gane el menor ID
                           (la cuenta registrada primero).
           ========================================================================= */
        else if (orden == "popular") {
            // R4b: con > gana el menor id si hay empate
            if (nUsuarios == 0) cout << "(sin cuentas)" << endl;
            else {
                int mejor = 0;
                for (int x = 1; x < nUsuarios; x++)
                    if (contarSeguidores(x) > contarSeguidores(mejor)) mejor = x;
                cout << "Popular: " << porId[mejor]->usuario << " | seguidores: " << contarSeguidores(mejor) << endl;
            }
        }
        else if (orden == "alcance") {
            // R5b
            NodoUsuario *u = buscar(raiz, a1);
            if (a1 == "") cout << "Uso: alcance @usuario" << endl;
            else if (u == nullptr) cout << "E: No existe " << a1 << endl;
            else {
                bool visto[MAX] = {false};
                cout << "Alcance de " << u->usuario << ":";
                difundir(u->id, visto, true);
                int k = 0;
                for (int x = 0; x < nUsuarios; x++) if (visto[x]) k++;
                if (k - 1 == 0) cout << " (nadie)";
                cout << " | alcanzados: " << k - 1 << endl;
            }
        }
        else if (orden == "llega") {
            // R5c
            NodoUsuario *a = buscar(raiz, a1);
            NodoUsuario *b = buscar(raiz, a2);
            if (a1 == "" || a2 == "") cout << "Uso: llega @a @b" << endl;
            else if (a == nullptr) cout << "E: No existe " << a1 << endl;
            else if (b == nullptr) cout << "E: No existe " << a2 << endl;
            else if (a == b) cout << "E: Elijan dos cuentas distintas" << endl;
            else {
                bool visto[MAX] = {false};
                difundir(a->id, visto, false);
                cout << "Un post de " << a1 << " llega a " << a2 << ": ";
                if (visto[b->id]) cout << "si" << endl;
                else cout << "no" << endl;
            }
        }
        else if (orden == "guardar") {
            ofstream f(ARCHIVO);
            int m = 0;
            guardarPreorden(raiz, f);
            // R6b: seguimientos recorriendo la matriz por filas
            for (int a = 0; a < nUsuarios; a++)
                for (int b = 0; b < nUsuarios; b++)
                    if (sigue[a][b] == 1) {
                        f << "S " << porId[a]->usuario << " " << porId[b]->usuario << endl;
                        m++;
                    }
            f.close();
            cout << "Guardado: " << contar(raiz) << " cuentas y " << m << " seguimientos en " << ARCHIVO << endl;
        }
        else if (orden == "cargar") {
            ifstream f(ARCHIVO);
            if (!f) cout << "E: No existe " << ARCHIVO << endl;
            else {
                int m = 0;
                // R6c: borrar todo y reconstruir desde el archivo
                liberar(raiz);
                raiz = nullptr;
                nUsuarios = 0;
                for (int i = 0; i < MAX; i++) {
                    porId[i] = nullptr;
                    for (int j = 0; j < MAX; j++) sigue[i][j] = 0;
                }
                string tipo;
                while (f >> tipo) {
                    if (tipo == "U") {
                        string usuario; int id;
                        f >> usuario >> id;
                        NodoUsuario *nodo = crearUsuario(usuario, id);
                        insertar(raiz, nodo);
                        porId[id] = nodo;
                        if (id + 1 > nUsuarios) nUsuarios = id + 1;
                    }
                    else if (tipo == "S") {
                        string ua, ub;
                        f >> ua >> ub;
                        NodoUsuario *a = buscar(raiz, ua);
                        NodoUsuario *b = buscar(raiz, ub);
                        if (a != nullptr && b != nullptr) {
                            sigue[a->id][b->id] = 1;
                            m++;
                        }
                    }
                }
                cout << "Cargado: " << contar(raiz) << " cuentas y " << m << " seguimientos | altura "
                     << altura(raiz) << endl;
            }
        }
        else if (orden == "reporte") {
            // R7b
            int s = 0, p = 0;
            for (int a = 0; a < nUsuarios; a++)
                for (int b = 0; b < nUsuarios; b++) {
                    if (sigue[a][b] == 1) s++;
                    if (a < b && sigue[a][b] == 1 && sigue[b][a] == 1) p++;
                }
            cout << "Cuentas: " << nUsuarios << " | seguimientos: " << s << " | pares mutuos: " << p << endl;
            cout << "Arbol: altura " << altura(raiz) << " | hojas " << hojas(raiz) << endl;
        }
        else if (orden == "ayuda") ayuda();
        else if (orden == "salir") break;
        else cout << orden << ": orden no encontrada (escribe ayuda)" << endl;
    }

    int liberados = liberar(raiz);
    raiz = nullptr;
    cout << "Nodos liberados: " << liberados << ". Hasta pronto." << endl;
    return 0;
}
