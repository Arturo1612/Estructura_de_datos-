# Ordenamiento de Inventario de Todas las Armas de Zelda Breath of the Wild

## Descripción del Proyecto

Este proyecto tiene como objetivo organizar las armas del juego **The Legend of Zelda: Breath of the Wild** de acuerdo a dos atributos: **daño** y **durabilidad**. El programa lee la información de las armas desde un archivo de texto (`armas.txt`), que contiene los nombres de las armas, su daño y su durabilidad. Después, el programa permite al usuario elegir el criterio por el cual se desea ordenar (ya sea por **daño** o **durabilidad**) y, finalmente, muestra la lista de armas ordenadas.

En el proyecto se ha implementado un **árbol AVL** para simular el inventario del juego, permitiendo la inserción y eliminación eficiente de armas.

### Implementación del Árbol AVL

Decidí utilizar un **árbol AVL** para simular el inventario de armas. El árbol AVL es una estructura autobalanceada que garantiza que las operaciones de búsqueda, inserción y eliminación se realicen en **O(log n)**, lo cual es ideal para manejar datos dinámicamente. 

Sin embargo, no lo utilizo para ordenar la lista completa de armas, ya que la función **`std::sort`** ya tiene una complejidad de **O(n log n)**, por lo que cambiarlo por un árbol AVL para ordenar no mejoraría la eficiencia. A pesar de esto, el **árbol AVL** se destaca en la eliminación de elementos, donde su eficiencia es mejor cuando se necesitan muchas eliminaciones consecutivas, con una complejidad de **O(log n)**.

El árbol AVL organiza los objetos (armas) basándose en el nombre de las armas, logrando un **orden lexicográfico** (alfabético). Esto se logró mediante la sobrecarga de los operadores usados para comparar las armas, lo que garantiza que las armas se inserten en el árbol de manera correcta y balanceada.


### Funcionalidad del Programa

1. **Lectura de archivo**: El programa lee el archivo `armas.txt`, donde cada línea del archivo contiene la información de un arma en el siguiente formato:

2. **Menú de opciones**: Después de cargar los datos, el programa muestra un menú donde el usuario puede seleccionar si desea   :
   - Mostrar armas en el orden original.
   - Ordenar las armas por daño o durabilidad.
   - Insertar o eliminar armas del árbol AVL.
   - Mostrar el árbol AVL en orden (inorden).


3. **Salida**: Dependiendo de la opción seleccionada, el programa realiza lo siguiete:
- Un **Quicksort** para ordenar por daño.
- Un **`std::sort`** (que internamente utiliza **Introsort**) para ordenar por durabilidad.
- Insertar un arma al **Árbol AVL**.
- Eliminar un arma del **Árbol AVL**.
- Mostrar las armas en el árbol (inorder).
- O terminar el programa.



## Cómo Usar el Programa

1. **Preparar el archivo de entrada**: Debes tener un archivo `armas.txt` con la información de las armas en el formato adecuado:

2. **Ejecución**: Ejecuta el programa, y este te mostrará las opciones que puedes realizar.

3. **Selección de criterio**: Escribe la opción que prefieras ("1" para mostrar el contenido del archivo, "2" para ordenar por daño, "3" para ordenar por durabilidad, y así sucesivamente) dependiendo de la opción el programa te va a imprimir la lista ordneada de las armas, las armas en el árbol AVL o te preguntará que arma deseas agregar o eliminar del arbol.

## Indicadores de Sub-Competencias

### SICT0302: Toma decisiones
**Selección de un algoritmo de ordenamiento adecuado al problema**

- Para ordenar las armas por **daño**, se ha implementado el algoritmo **Quicksort**. Se eligió este algoritmo porque ofrece un rendimiento rápido en la mayoría de los casos, con una **complejidad promedio de O(n log n)**. Quicksort es muy eficiente cuando los datos están desordenados (como en este caso), por lo que es improbable que se presente su peor caso \(O(n^2)\), especialmente dado que los datos de entrada no están ordenados previamente.

- Para ordenar las armas por **durabilidad**, se utilizó la función **`std::sort`** de la biblioteca estándar de C++. Esta función utiliza internamente **Introsort**, un algoritmo híbrido que combina **Quicksort**, **Heapsort** e **Insertion Sort**. **Introsort** es ideal porque garantiza un rendimiento **óptimo en el peor caso**, manteniendo una complejidad de **O(n log n)**, mientras evita el riesgo de que Quicksort caiga en su peor caso. Además, `std::sort` es fácil de implementar y está optimizada para diferentes tamaños de datos.

- Decidí utilizar un **árbol AVL** no para ordenar las armas, sino para simular el inventario de armas del juego. El árbol AVL ofrece ventajas en la **inserción y eliminación** de armas, con una complejidad de **O(log n)** en todos sus casos, lo que lo hace eficiente para gestionar un inventario dinámico.

### SICT0301: Evalúa los componentes
**Análisis de complejidad para los algoritmos de ordenamiento usados en el programa**

1. **Complejidad de Quicksort**:
- **Caso promedio**: \(O(n \log n)\) en la mayoría de los casos. Esto se debe a que el algoritmo divide el problema en dos subproblemas de tamaño similar, y luego combina las soluciones.
- **Peor caso**: \(O(n^2)\). El peor caso ocurre cuando el pivote se elige mal y el arreglo está ordenado de manera tal que siempre se divide de forma desbalanceada. Sin embargo, es poco probable que esto ocurra con los datos de este proyecto, ya que están desordenados.

2. **Complejidad de `std::sort` (Introsort)**:
- **Promedio y peor caso**: \(O(n \log n)\). Introsort cambia de Quicksort a Heapsort cuando detecta que la recursión se está profundizando demasiado, lo que lo protege del mal comportamiento en el peor caso. Además, utiliza Insertion Sort para manejar particiones pequeñas de forma eficiente, lo que mejora el rendimiento general en arreglos pequeños.

3. **Complejidad del árbol AVL**:
   - **Inserción y eliminación**: \(O(log n)\), lo que garantiza eficiencia al modificar el inventario dinámico de armas. Esta estructura es ideal para un inventario que permite muchas inserciones y eliminaciones.

### SICT0303: Implementa acciones científicas
**Mecanismos implementados para manipular las estructuras de datos**

- **Lectura de archivos**: El programa carga la información de las armas desde un archivo de texto (`armas.txt`), convirtiendo los datos en objetos `Armas`.

- **AVL Tree**: La implementación del árbol AVL permite agregar y eliminar armas de manera eficiente, simulando un inventario dinámico. Los datos de las armas provienen de los objetos `Armas`. El usuario ingresa el nombre del arma, y el programa busca dicho nombre entre los objetos creados a partir del archivo para obtener la información correspondiente al daño y la durabilidad del arma. De este modo, el usuario solo necesita conocer el nombre del arma para manipular el inventario.

### SICT0301: Evalúa los Componentes

En este programa, se realizó un análisis de complejidad detallado para cada función y estructura utilizada, lo cual permite evaluar la eficiencia del código. La función principal contiene una serie de opciones que permiten ejecutar diferentes operaciones de búsqueda, ordenamiento e inserción de elementos en un árbol AVL, así como el guardado de datos en un archivo. Se emplearon algoritmos eficientes como **Quicksort** y **std::sort** para organizar las armas por sus atributos de daño y durabilidad, respectivamente. Estos algoritmos fueron seleccionados por su complejidad promedio de \( O(n \log n) \), lo cual es adecuado para listas de tamaño moderado, como las que se manejan en este programa. Para almacenar y manipular el inventario de armas de forma eficiente, se utilizó un **árbol AVL** que ofrece tiempos de inserción y eliminación de \( O(\log n) \), lo que asegura un rendimiento consistente incluso cuando se agregan o eliminan múltiples elementos.

La complejidad final del programa depende de la opción seleccionada por el usuario en el menú. Las operaciones de lectura de archivo y procesamiento inicial tienen una complejidad de \( O(n) \), donde \( n \) es el número de armas en el archivo. Las opciones de ordenamiento utilizan **Quicksort** y **std::sort** con \( O(n \log n) \) de complejidad promedio. Las operaciones de inserción, eliminación y búsqueda en el árbol AVL mantienen un rendimiento de \( O(\log k) \), siendo \( k \) el número de armas en el árbol. Finalmente, los recorridos del árbol en orden (`inorder`) o preorden (`preorder`) tienen una complejidad de \( O(k) \), ya que recorren cada nodo del árbol. Este análisis completo asegura que cada componente se haya evaluado y optimizado para proporcionar un rendimiento adecuado según su función en el programa.

### SICT0303: Implementa Acciones Científicas

El programa también implementa correctamente mecanismos de escritura en archivos para guardar datos provenientes de las estructuras de datos. En particular, la opción que permite guardar el recorrido en **preorden** del árbol AVL en un archivo denominado `inventario.txt` es un ejemplo de cómo se manipulan y almacenan los datos en estructuras persistentes. Este archivo contiene el inventario ordenado según el recorrido del árbol, lo que permite que la información pueda ser consultada o utilizada en ejecuciones futuras. La funcionalidad de escritura en archivo se realiza utilizando flujos de salida de C++ (`ofstream`), asegurando que el archivo se abra y se cierre adecuadamente después de escribir el contenido. Este mecanismo no solo guarda los datos de manera eficiente, sino que también garantiza que el archivo resultante esté bien estructurado y disponible para futuras consultas, lo que cumple con los objetivos de almacenamiento persistente en el programa.

## Instrucciones para Usar el Programa

Para utilizar el programa de inventario de armas, sigue los siguientes pasos:

1. **Preparar el Archivo de Entrada**: Asegúrate de tener un archivo llamado `armas.txt` en el mismo directorio que el programa. Este archivo debe contener la información de las armas en el formato: `Nombre,Daño,Durabilidad` en cada línea.

2. **Ejecutar el Programa**: Compila y ejecuta el programa desde tu entorno de desarrollo o terminal.

3. **Seleccionar una Opción**: El programa te mostrará un menú con diferentes opciones. Escribe el número correspondiente a la opción que deseas realizar y presiona `Enter`.

4. **Insertar una Nueva Arma en el Árbol AVL**: Si deseas agregar una nueva arma al inventario, selecciona la opción para insertar en el árbol AVL e ingresa el nombre del arma que se encuentra en el archivo de texto. Ejemplos de nombres de armas para insertar:

   - Espada Maestra
   - Rama de Arbol
   - Antorcha
   - Cucharon de Sopa
   - Bumeran

5. **Guardar el Inventario en un Archivo**: Selecciona la opción para guardar el inventario en el archivo `inventario.txt`. El inventario será guardado en el archivo en un recorrido preorden, permitiendo que la información pueda ser consultada posteriormente.

6. **Finalizar el Programa**: Cuando hayas terminado, selecciona la opción para salir y el programa se cerrará de manera segura.


