#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <set>
using namespace std;
//muestra los elementos de las matrices
void mostrar(vector<vector<int>> b) {
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[i].size(); j++) {
			cout << b[i][j];
		}
		cout << endl;
	}
}
//convierte los miniterminos a binarios, segun la cantidad de variables
vector <int> bin(int n, int x) {
	vector <int> y;
	int c = 0;
	for (int i = 1; i <= n; i++) {
		if (x % 2 == 1) {
			c++;
		}
		y.insert(y.begin(), x%2);
		x = x / 2;
	}
	y.insert(y.begin(), c);
	return y;
}
//devuelve true si los numeros binarios difieren en solo un numero
bool esSimilar(vector<int> a, vector<int> b){
	int c = 0;
	for (int i = 1; i < a.size(); i++) {
		if (a[i] != b[i]) {
			c++;
		}
	}
	if (c == 1) {
		return true;
	} else {
		return false;
	}
}
//coloca -1 en las casillas que difieren
vector<int> simplificar(vector<int> a, vector<int> b) {
	vector<int> c;
	int m = 0;
	for (int i = 1; i < a.size(); i++) {
		if (a[i] == b[i]) {
			if (a[i] == 1) {
				m++;
			}
			c.push_back(a[i]);
		}
		else {
			c.push_back(-1);
		}
	}
	c.insert(c.begin(), m);
	return c;
}
//pone al final del vector "a" los elementos del vector "b"
vector<int> unir(vector<int> a, vector<int> b) {
	vector<int> r(a);
	r.insert(r.begin(), b.begin(), b.end());
	return r;
}
//elige los conjuntos de binarios que iran a la tabla final
void seleccionar(vector<vector<int>> &n, vector<vector<int>> &f, int e) {
	vector<vector<int>> v;
	vector<vector<int>> r1;
	vector<vector<int>> r2;
	vector<int> aux;
	int c = 0;
	for (int i = 0; i < pow(2, e); i++) {
		aux.push_back(0);
	}
	for (int i = 0; i < n.size(); i++) {
		v.push_back(aux);
	}
	for (int i = 0; i < n.size(); i++) {
		for (int j = 0; j < n[1].size(); j++) {
			v[i][n[i][j]] = 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[1].size(); j++) {
			if (v[i][j] == 1) {
				c = 0;
				for (int k = 0; k < v.size(); k++) {
					if (v[k][j] == 1) {
						c++;
					}
				}
				if (c == 1) {
					r1.push_back(n[i]);
					r2.push_back(f[i]);
					j = v[i].size() - 1;
				}
			}
		}
	}
	f = r2;
	n = r1;
}
//devuelve true si el vector "a" existe en la matriz "b"
bool existe(vector<int> a, vector<vector<int>> b) {
	for (int i = 0; i < b.size(); i++) {
		if (a == b[i]) {
			return true;
		}
	}
	return false;
}
//genera la tabla simplificada de los valores binarios
void reducir(vector<vector<int>> &b, vector<vector<int>> &n) {
	int d = 0;
	int f = b.size();
	vector<vector<int>> r;
	vector<vector<int>> v;
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (b[i][0] == b[j][0] + 1) {
				if (esSimilar(b[i],b[j])) {
					if (d == 0) {
						r.push_back(simplificar(b[i], b[j]));
						v.push_back(unir(n[i], n[j]));
					}
					else
					{
						if (existe(simplificar(b[i], b[j]), r) != true) {
							r.push_back(simplificar(b[i], b[j]));
							v.push_back(unir(n[i], n[j]));
						}
					}
					d++;
				}
			}
		}
	}
	if (d == 0) {
		r = b;
		v = n;
	}
	b = r;
	n = v;
}
//devuelve la expresion final de la tabla a
void expresion(vector<vector<int>> a) {
	vector<string> var{ "x","y","z","w","r","s","t","u","v" };
	string m = "";
	for (int i = 0; i < a.size(); i++) {
		for (int j = 1; j < a[1].size(); j++) {
			if (a[i][j] >= 0) {
				if (a[i][j] == 1) {
					m = m + var[j-1];
				}
				else
				{
					m = m + var[j-1] + "'";
				}

			}
		}
		if (i != a.size() - 1) {
			m = m + "+";
		}
	}
	cout << m << endl;
}

int main() {
	vector <vector <int>> numeracion;
	vector <vector <int>> miniterminos, aux;
	vector <int> num;
	int nv, nm, min;
	cout << "Indique el numero de variables: ";
	cin >> nv;
	cout << "Indique el numero de miniterminos: ";
	cin >> nm;
	cout << "Indique los miniterminos (0-" << pow(2, nv) - 1 << "):" << endl;
	for (int i = 1; i <= nm; i++) {
		vector <int> n;
		cout << "Minitermino " << i << ": ";
		cin >> min;
		n.push_back(min);
		numeracion.push_back(n);
		miniterminos.push_back(bin(nv, min));
	}
	do
	{
		aux = miniterminos;
		reducir(miniterminos, numeracion);
	} while (aux != miniterminos);
	seleccionar(numeracion, miniterminos, nv);
	cout << "Expresion simplificada: ";
	expresion(miniterminos);
}