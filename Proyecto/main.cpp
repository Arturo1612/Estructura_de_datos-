#include "Arma.h"
#include "ArmaAVL.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <algorithm>

using namespace std;

vector<Arma> leerArmas(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<Arma> armas;
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Arma arma;
        string dano_str, durabilidad_str;

        getline(ss, arma.nombre, ',');
        getline(ss, dano_str, ',');
        getline(ss, durabilidad_str, ',');

        arma.dano = stoi(dano_str);
        arma.durabilidad = stoi(durabilidad_str);

        armas.push_back(arma);
    }
    archivo.close();
    return armas;
}

// Función para transformar una cadena a minúsculas
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Función para leer un arma específica desde un archivo
Armas buscarArmaEnArchivo(const string& nombreBuscado, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return Armas(); // Devuelve un objeto Armas vacío si no se pudo abrir el archivo
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int dano, durabilidad;

        // Leer el nombre hasta la coma
        getline(ss, nombre, ',');

        // Convertir ambos nombres a minúsculas para comparación insensible a mayúsculas
        string nombreLower = toLowerCase(nombre);
        string nombreBuscadoLower = toLowerCase(nombreBuscado);

        // Comparar el nombre buscado con el nombre leído
        if (nombreLower == nombreBuscadoLower) {
            // Leer el daño y la durabilidad
            ss >> dano;
            ss.ignore(); // Ignorar la coma
            ss >> durabilidad;

            // Crear y devolver el objeto Armas
            return Armas(nombre, dano, durabilidad);
        }
    }

    // Si no se encuentra, devolver un objeto Armas vacío
    return Armas();
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    string nombreArchivo = "Armas.txt";

    // Verificar si el archivo existe y se puede abrir
    ifstream archivoTest(nombreArchivo);
    if (!archivoTest.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }
    archivoTest.close();

    // Leer las armas desde el archivo
    vector<Arma> armas = leerArmas(nombreArchivo);
    AVL<Armas> arbol;
    string nombreBuscado;
    string nombreArma;

    // Mostrar un menú para que el usuario elija cómo proceder
    int opcion = 0;
    while(opcion != 8) {
        cout << "\nElige una opción:\n";
        cout << "1. Mostrar el contenido original\n";
        cout << "2. Ordenar usando quicksort por mayor daño\n";
        cout << "3. Ordenar usando std::sort por mayor durabilidad\n";
        cout << "4. Insertar un arma en el árbol AVL\n";
        cout << "5. Eliminar un arma del árbol AVL\n";
        cout << "6. Mostrar armas en el árbol AVL (inorder)\n";
        cout<< "7. Mostrar armas en el inventario.txt (preorder)\n";
        cout<< "8. Terminar el programa\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // Para evitar que queden caracteres en el buffer

        if (opcion == 1) {
            // Mostrar las armas en el orden original (como se leyeron del archivo)
            cout << "\n--- Armas en orden original ---\n";
            mostrarArmas(armas);
        } else if (opcion == 2) {
            // Opción 2: Usar quicksort para ordenar por mayor daño
            quicksort(armas, 0, armas.size() - 1);
            cout << "\n--- Armas ordenadas por mayor daño ---\n";
            mostrarArmas(armas);
        } else if (opcion == 3) {
            // Opción 3: Usar std::sort para ordenar por mayor durabilidad
            sort(armas.begin(), armas.end(), compararPorDurabilidad);
            cout << "\n--- Armas ordenadas por mayor durabilidad ---\n";
            mostrarArmas(armas);
        } else if (opcion == 4) {
            // Opción 4: Insertar un arma en el árbol AVL
            cout << "Ingrese el nombre del arma: ";
            getline(cin, nombreBuscado);
            Armas armaEncontrada = buscarArmaEnArchivo(nombreBuscado, nombreArchivo);
            if (armaEncontrada.nombre != "") {
                
                // Agregar el arma encontrada al AVL
                arbol.add(armaEncontrada);
                // Mostrar el recorrido en inorden y preorden del AVL
                cout << "\nRecorrido en inorden:\n" << arbol.inorder() << endl;
                cout << "\nRecorrido en preorden:\n" << arbol.preorder() << endl;
            } else {
                cout << "El arma " << nombreBuscado << " no fue encontrada en el archivo." << endl;
            }
        } else if (opcion == 5) {
            // Opción 5: Eliminar un arma del árbol AVL
            cout << "Ingrese el nombre del arma a eliminar: ";
            getline(cin, nombreBuscado);

            // Primero buscar el arma en el árbol
            Armas armaAEliminar = buscarArmaEnArchivo(nombreBuscado, nombreArchivo);
            if (armaAEliminar.nombre != "") {
                arbol.remove(armaAEliminar);
                cout << "El arma fue eliminada.\n";
                cout << "\nRecorrido en inorden después de eliminar:\n" << arbol.inorder() << endl;
            } else {
                cout << "El arma " << nombreBuscado << " no fue encontrada en el archivo." << endl;
            }
        } else if (opcion == 6) {
            // Opción 6: Mostrar armas en el árbol AVL en inorder
            cout << "\n--- Armas en el árbol AVL (inorder) ---\n";
            cout << arbol.inorder() << endl;
        } else if (opcion == 7){
            cout <<"\n--- Armas en inventario (árbol AVL) en preorden cargadas en el archivo ---\n";
            // Abrir o crear el archivo preorden.txt
            ofstream archivo("inventario.txt");
            if (archivo.is_open()) {
                // Obtener el recorrido en preorden como string
                string recorridoPreorden = arbol.preorder();
                // Escribir el recorrido en el archivo
                archivo << recorridoPreorden;
                cout << "Recorrido en preorden guardado en el archivo inventario.txt." << endl;
                archivo.close();
            } else {
                cout << "No se pudo abrir o crear el archivo preorden.txt." << endl;
            }
        }else if (opcion == 8) {
            // Opción 7: Terminar el programa
            cout << "\n-- Terminando programa --\n";
        } else {
            cout << "Opción no válida." << endl;
            opcion = 7;
        }
    }
    return 0;
}
