#ifndef AVL_H_
#define AVL_H_

#include <string>
#include <sstream>
#include "exception.h"
#include <iostream>

using namespace std;

template <class T> class AVL;

struct Armas{
	string nombre;
	int dano;
	int durabilidad;

    // Constructor por defecto
	//O(1)
    Armas() {
        nombre = "";
        dano = 0;
        durabilidad = 0;
    }

    // Constructor con parámetros
	//O(1)
    Armas(const std::string& nombre, int dano, int durabilidad) {
        this->nombre = nombre;
        this->dano = dano;
        this->durabilidad = durabilidad;
    }

	//Sobrecargar el operador < para que compare por longitud de palabra
	//O(n)
    bool operator<(const Armas& otra) const {
        return this->nombre < otra.nombre;
    }

    // Sobrecarga del operador >
	//O(n)
    bool operator>(const Armas& otra) const {
        return this->nombre > otra.nombre;
    }

	//Sobrecargar del operador =
	//O(n)
	Armas& operator=(const Armas& otra) {
		if (this != &otra) {
			this->nombre = otra.nombre;
			this->dano = otra.dano;
			this->durabilidad = otra.durabilidad;
		}
		return *this;
	}
	
	//Sobre carga del operador ==
	//O(n)
	bool operator==(const Armas& otra) const {
    	return this->nombre == otra.nombre &&
           	this->dano == otra.dano &&
           	this->durabilidad == otra.durabilidad;
	}

	
	//Sbobrecarga del operador <<
	//O(n)
	friend std::ostream& operator<<(std::ostream& os, const Armas& arma) {
    	os << "Nombre: " << arma.nombre << ", Daño: " << arma.dano << ", Durabilidad: " << arma.durabilidad;
    	return os;
	}

    // Sobrecargar el operador <= para comparar por daño
	//O(n)
    bool operator<=(const Armas& otra) const {
        return this->nombre <= otra.nombre;
    }

	// Sobrecargar el operador >= para comparar por daño
	//O(n)
    bool operator>=(const Armas& otra) const {
        return this->nombre >= otra.nombre;
    }
};


template <class T>
class Node {
private:
	T value;
	Node *left, *right;
	int level, balance;
	//O(log n)
	Node<T>* predecesor();

public:
	//O(1)
	Node(T);
	Node(T, Node<T>*, Node<T>*, int, int);
	//O(log n)
	void add(T);
	//O(log n)
	bool find(T);
	//O(log n)
	void remove(T);
	//O(n)
	void removeChilds();
	//O(n)
	void inorder(std::stringstream&) const;
	//O(n)
	void preorder(std::stringstream&) const;
	//O(log n)
	int max_depth();
	//O(log n)
	Node<T>* check_tree(T*, Node<T>*, bool*);
	//O(1)
	Node<T>* balance_tree();
	//O(1)
	Node<T>* rot_left(Node<T>* );
	Node<T>* rot_right(Node<T>* );
	Node<T>* rot_left_right(Node<T>* );
	Node<T>* rot_right_left(Node<T>* );
	friend class AVL<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), level(0), balance(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, int lev, int bal)
	: value(val), left(le), right(ri), level(lev), balance(bal) {}

template <class T>
//O(log n)
void Node<T>::add(T val) {
    if (val >= value) {  // Permitir duplicados y colocarlos en el subárbol derecho
        if (right == nullptr) {
            right = new Node<T>(val);
        } else {
            right->add(val);
        }
    } else {  // Si el valor es menor, va al subárbol izquierdo
        if (left == nullptr) {
            left = new Node<T>(val);
        } else {
            left->add(val);
        }
    }
}


template <class T>
//O(log n)
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
    return false;
}

template <class T>
//O(log n)
Node<T>* Node<T>::predecesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	Node<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
//O(log n)
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
//O(n)
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
//O(n)
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != nullptr) {
        left->inorder(aux);
    }

    aux << value << "\n";  // Imprime el valor del nodo y añade un salto de línea

    if (right != nullptr) {
        right->inorder(aux);
    }
}

template <class T>
//O(n)
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value << "\n";  // Imprime el valor del nodo y añade un salto de línea

    if (left != nullptr) {
        left->preorder(aux);
    }

    if (right != nullptr) {
        right->preorder(aux);
    }
}


template <class T>
//O(log n)
int Node<T>::max_depth() {
	int le =0 , ri = 0;
	if (left != 0)
		le = left->max_depth() + 1;
	if (right != 0)
		ri = right->max_depth() + 1;
	if(le > ri)
		level = le;
	else
		level = ri;
	balance = le - ri;
	return level;
}

template <class T>
//O(log n)
Node<T>* Node<T>::check_tree(T *check_val, Node<T> *parent, bool *checked) {
	Node<T>*le = 0, *ri = 0, *a = 0;
	if (left != 0)
		le = left->check_tree(check_val,this,checked);
	if (right != 0)
		ri = right->check_tree(check_val,this,checked);
	if (*checked == false){
		if (balance > 1){
			a = balance_tree();
			*check_val = value;
			*checked = true;
			if(parent != 0){
				parent->left = a;
			}
		}else if (balance < -1){
			a = balance_tree();
			*check_val = value;
			*checked = true;
			if(parent != 0){
				parent->right = a;
			}
		}
	}
	return a;
}

template <class T>
//O(1)
Node<T>* Node<T>::balance_tree() {
	Node<T> *a = this, *le = left, *ri = right;
	int old_value = value.nombre.length();  // Comparar por longitud del nombre
	
	if (balance > 0) {
		if (le->balance > 0){
			a = rot_right(a);
		}else{
			a = rot_left_right(a);
		}
	}else{
		if (ri->balance < 0){
			a = rot_left(a);
		}else{
			a = rot_right_left(a);
		}
	}
	return a;
}


template <class T>
Node<T>* Node<T>::rot_left(Node<T>* a){
	Node<T> *b, *temp = 0;
	if (a->right != 0){
		b = a->right;
		if (b->left != 0)
			temp = b->left;
		b->left = a;
		if(temp != 0){
			a->right = temp;
		}else{
			a->right = 0;
		}
	}
	return b;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* a){
	Node<T> *b, *temp = 0;
	if (a->left != 0){
		b = a->left;
		if (b->right != 0)
			temp = b->right;
		b->right = a;
		if(temp != 0){
			a->left = temp;
		}else{
			a->left = 0;
		}
	}
	return b;
}

template <class T>
Node<T>* Node<T>::rot_left_right(Node<T>* a){
	a->left = rot_left(a->left);
	a = rot_right(a);
	return a;
}

template <class T>
Node<T>*  Node<T>::rot_right_left(Node<T>* a){
	a->right = rot_right(a->right);
	a = rot_left(a);
	return a;
}

template <class T>
class AVL {
private:
	Node<T> *root;

public:
	//O(1)
	AVL();
	~AVL();
	//O(1)
	bool empty() const;
	//O(log n)
	void add(T);
	//O(log n)
	bool find(T) const;
	//O(log n)
	void remove(T);
	//O(n)
	void removeAll();
	//O(n)
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
AVL<T>::AVL() : root(0) {}

template <class T>
AVL<T>::~AVL() {
	removeAll();
}

template <class T>
bool AVL<T>::empty() const {
    return root == nullptr;  // Verifica si el árbol está vacío
}

template<class T>
void AVL<T>::add(T val) {
    if (root != 0) {
        Node<T> *temp;
        T check_val = T();
        bool aux = false;
        root->add(val);
        root->max_depth();
        temp = root->check_tree(&check_val, 0, &aux);
        if (check_val == root->value) {
            root = temp;
        }
        root->max_depth();
    } else {
        root = new Node<T>(val);
    }
}


template <class T>
void AVL<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->predecesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
		root->max_depth();
		Node <T> *temp;
		T check_val = T();
		bool aux = false;
		temp = root->check_tree(&check_val, 0, &aux);
		if (check_val == root->value){
			root = temp;
		}
		root->max_depth();
	}
}

template <class T>
void AVL<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool AVL<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
std::string AVL<T>::inorder() const {
    std::stringstream aux;

    if (!empty()) {
        root->inorder(aux);
    }

    return aux.str();
}

template <class T>
std::string AVL<T>::preorder() const {
    std::stringstream aux;

    if (!empty()) {
        root->preorder(aux);
    }

    return aux.str();
}

#endif /* AVL_H_ */
