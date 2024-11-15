#ifndef ARMA_H
#define ARMA_H
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Arma {
    std::string nombre;
    int dano;
    int durabilidad;

    // Sobrecargar el operador < para comparar por daño
    // Complejidad: O(1)
    bool operator<(const Arma& otra) const;

    // Sobrecargar el operador > para comparar por daño
    // Complejidad: O(1)
    bool operator>(const Arma& otra) const;
};

// Declaraciones de funciones
bool compararPorDurabilidad(const Arma& a, const Arma& b);
void mostrarArmas(const std::vector<Arma>& armas);
void imprimirArchivoOriginal(const std::string& nombreArchivo);
void quicksort(std::vector<Arma>& armas, int inicio, int fin);
void ordenarYMostrarArmas(std::vector<Arma>& armas);

//O(n)
bool Arma::operator<(const Arma& otra) const {
    return this->dano < otra.dano;
}
//O(n)
bool Arma::operator>(const Arma& otra) const {
    return this->dano > otra.dano;
}
//O(1)
bool compararPorDurabilidad(const Arma& a, const Arma& b) {
    return a.durabilidad > b.durabilidad;
}
//O(n)
void mostrarArmas(const vector<Arma>& armas) {
    for (const auto& arma : armas) {
        cout << "Arma: " << arma.nombre << ", Daño: " << arma.dano << ", Durabilidad: " << arma.durabilidad << endl;
    }
}
//O(n)
void imprimirArchivoOriginal(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    cout << "\n--- Contenido original del archivo ---\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
//Complejidad promedio: O(n log n), peor caso: O(n^2)
void quicksort(vector<Arma>& armas, int inicio, int fin) {
    if (inicio < fin) {
        int pivote = (inicio + fin) / 2;
        int izq = inicio;
        int der = fin;
        Arma pivoteArma = armas[pivote];

        //O(n)
        while (izq <= der) {
            while (armas[izq] > pivoteArma) {
                izq++;
            }
            while (armas[der] < pivoteArma) {
                der--;
            }
            if (izq <= der) {
                swap(armas[izq], armas[der]);
                izq++;
                der--;
            }
        }
        // Complejidad promedio total de quicksort: O(n log n)
        quicksort(armas, inicio, der);
        quicksort(armas, izq, fin);
    }
}

#endif // ARMA_H
