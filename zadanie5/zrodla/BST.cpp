﻿#include <iostream>
#include <string>
#include "Common.h"
#include "BST.h"

using namespace std;

Node* newNode() {
	Node* wezel = new Node;
	wezel->lewy = NULL;
	wezel->prawy = NULL;
	wezel->ojciec = NULL;
	wezel->wartosc = NaN;
	return wezel;
}

void  destroyNode(Node* wezel) {
	if (wezel != NULL) {
		if (wezel->lewy != NULL) destroyNode(wezel->lewy);
		if (wezel->prawy != NULL) destroyNode(wezel->prawy);
		delete wezel;
	}
}

Drzewo* newDrzewo() {
	Drzewo* tree = new Drzewo;
	tree->korzen = NULL;
	return tree;
}

void  destroyDrzewo(Drzewo* drzewo) {
	destroyNode(drzewo->korzen);
	delete drzewo;
}

void wstaw(Drzewo* drzewo, int wartosc) {
	Node* nowyWezel = newNode();
	nowyWezel->wartosc = wartosc;
	if (drzewo->korzen == NULL) {
		drzewo->korzen = nowyWezel;
		return;
	}
	Node* wezel = drzewo->korzen;
	Node* ojciec = NULL;
	while (wezel != NULL) {
		ojciec = wezel;
		if (wezel->wartosc > nowyWezel->wartosc) {
			wezel = wezel->lewy;
		} 
		else {
			wezel = wezel->prawy;
		}
	}
	nowyWezel->ojciec = ojciec;
	if (ojciec->wartosc > nowyWezel->wartosc) {
		ojciec->lewy = nowyWezel;
	}
	else {
		ojciec->prawy = nowyWezel;
	}
}

Node* znajdz(Node* node, int wartosc) { //zwrocenie wezla z wartoscia poszukiwana
	//Tutaj dokonaj implementacji funkcji
	//node = znajdz(node, wartosc);
	if (node == nullptr or node->wartosc == wartosc) {
		return node;
	}
	else if (node->wartosc > wartosc) {
		return znajdz(node->lewy, wartosc);
	}
	else {
		return znajdz(node->prawy, wartosc);
	}
}
/* Iteracyjne znajdz
Node* znajdz(Node* node, int wartosc) {
	while (node != nullptr and node->wartosc != wartosc) {
		if (node->wartosc > wartosc) {
			node = node->lewy;
		}
		else {
			node = node->prawy;
		}
	}
	return node;
}

*/


Node* minimum(Node* wezel) {  //znalezienie minimum
	//Tutaj dokonaj implementacji funkcji -funkcja pomocnicza
	while (wezel->lewy != nullptr) {
		wezel = wezel->lewy;
	}
	return wezel;
}

int minimum(Drzewo* drzewo) {
	Node* wezel = drzewo->korzen;
	wezel = minimum(wezel);
	return wezel->wartosc;
}

Node* nastepnik(Node* wezel) { //nastepny element wezla
	//Tutaj dokonaj implementacji funkcji - funkcja pomocnicza
	//wezel = nastepnik(wezel);
	//
	if (wezel->prawy != nullptr) {
		return minimum(wezel->prawy);
	}
	Node* nastepnik = wezel->ojciec;
	while (nastepnik != nullptr and nastepnik->prawy == wezel) {
		wezel = nastepnik;
		nastepnik = wezel->ojciec;
	}
	return nastepnik;
	
}

int nastepnik(Drzewo* drzewo, int wartosc) {	
	Node* wezel = znajdz(drzewo->korzen, wartosc);
	wezel = nastepnik(wezel);
	return wezel->wartosc;
}

void usun(Drzewo* drzewo, Node* wezelDoUsunuecia) {
	Node* ojciecUsuwanegoWezla = wezelDoUsunuecia->ojciec;
	Node* wezelZastepczy = NULL;
	if (wezelDoUsunuecia->lewy == NULL && wezelDoUsunuecia->prawy == NULL) { //Jeśli nie mamy dzieći to po prostu usuwamy
		if (ojciecUsuwanegoWezla == NULL) { //Jeśli usuwamy korzen
			wezelZastepczy = NULL;
		} else {
			//Sprawdzenie czy wezel do usuniecia był po lewej czy po prawej stronie ojca
			if (ojciecUsuwanegoWezla->lewy == wezelDoUsunuecia) {
				ojciecUsuwanegoWezla->lewy = NULL;
			} else {
				ojciecUsuwanegoWezla->prawy = NULL;
			}
		}
	} else { //Jeśli mamy przynajmniej jedno dziecko		
		wezelZastepczy = nastepnik(wezelDoUsunuecia); //Szukamy węzła który zastąpi obecny	- zawsze jest to węzeł który jest po prawej, ale nie wiemy który		
		{//Podmiana dzieci wezłaZastępczego i podpięcie do rodzica
			if (wezelZastepczy->ojciec == wezelDoUsunuecia) {
				//Z dziećmi wezla zastępczego nic nie trzeba robić
			}
			else if (wezelZastepczy->lewy == wezelDoUsunuecia) {
				//Z dziecmi wezla zastępczego nic nie trzeba robić
			}
			else {	//Gdy węzeł zastępczy jest jednym z węzłów po lewej stronie węzłaDoUsunięcia ale nie jest bezpośrednim dzieckiem	tego wezla
			 //Wóczas dziecko węzłaZastępczego musimy przepiąć do rodzica dziecka zastępczego
				wezelZastepczy->ojciec->lewy = wezelZastepczy->prawy; //Bo z lewej nikogo nie ma wezel zastepczy bo jest nastepnikiem
				if (wezelZastepczy->prawy != NULL) {
					wezelZastepczy->prawy->ojciec = wezelZastepczy->ojciec;
				}
			}
		}
		{//Podmiana wezelZastepczy z ojcemUsuwanego
			if (ojciecUsuwanegoWezla != NULL && ojciecUsuwanegoWezla->lewy == wezelDoUsunuecia) { //Jeśli jesteśmy lewym dzieckiem to podpinamy w to miejsce naszego dzieciaka
				ojciecUsuwanegoWezla->lewy = wezelZastepczy;
			}
			if (ojciecUsuwanegoWezla != NULL && ojciecUsuwanegoWezla->prawy == wezelDoUsunuecia) { //Jeśli jesteśmy prawym dzieckiem to podpinamy w to miejsce naszego dzieciaka
				ojciecUsuwanegoWezla->prawy = wezelZastepczy;
			}
			wezelZastepczy->ojciec = ojciecUsuwanegoWezla;
		}
		{ //Podmiana dzieci wezłaUsuwanego do węzłaZastępczego
			wezelZastepczy->lewy = wezelDoUsunuecia->lewy;
			if (wezelDoUsunuecia->lewy != NULL)
				wezelDoUsunuecia->lewy->ojciec = wezelZastepczy;	
			if (wezelZastepczy != wezelDoUsunuecia->prawy)
				wezelZastepczy->prawy = wezelDoUsunuecia->prawy;
			if (wezelDoUsunuecia->prawy != NULL) {
				if (wezelDoUsunuecia->prawy != wezelZastepczy) { //Jeśli wezel zastepczy nie jest dzieckiem wezlaDoUsuniecia
					wezelDoUsunuecia->prawy->ojciec = wezelZastepczy;
				}
				else { //Jak jednak jest dzieckiem to nic nie musimy obić				
				}
			}
		}
	}
	if (ojciecUsuwanegoWezla == NULL) {
		drzewo->korzen = wezelZastepczy;
	}
}

bool czyJest(Drzewo* drzewo, int wartosc) { 
	//Tutaj dokonaj implementacji funkcji
	if (drzewo->korzen == nullptr) {
		return false;
	}
	else if (drzewo->korzen->wartosc == wartosc) {
		return true;
	}
	if (drzewo->korzen->ojciec->wartosc > wartosc);

}

int usun(Drzewo* drzewo, int wartosc) {	
	Node* wezelDoUsuniecia = znajdz(drzewo->korzen, wartosc);
	if (wezelDoUsuniecia==NULL) return NaN;
	int wynik = wezelDoUsuniecia->wartosc;
	usun(drzewo, wezelDoUsuniecia);	
	delete wezelDoUsuniecia;
	return wynik;
}

string wypisz(Node* wezel, string poziom) {
	string s = "";		
	s += poziom;
	s += "Wartosc: " + to_string(wezel->wartosc);
	s += "\n";
	poziom += "--";
	if (wezel->lewy != NULL) {
		s += poziom + "L:";
		s += wypisz(wezel->lewy, poziom);
	}
	if (wezel->prawy != NULL) {
		s += poziom + "P:";
		s += wypisz(wezel->prawy, poziom);
	}
	return s;
}

void wyswietl(Drzewo* drzewo) {
	string s = wypisz(drzewo->korzen, "");
	cout << s;
}
