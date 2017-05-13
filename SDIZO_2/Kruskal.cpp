#include "stdafx.h"
#include "Kruskal.h"

int findPrevious(int u, int *previous)	//Funkcja rekurencyjnie wyszukuj�ca poprzednika, jako argumenty otrzymuje wierzcho�ek i tablic� wierzcho�k�w, w kt�rej ma szuka� poprzednika
{
	if (u != previous[u])	//Je�li wierzcho�ek nie jest pocz�tkowym danego poddrzewa
	{
		previous[u] = findPrevious(previous[u], previous);
	}

	return previous[u];
}


void Kruskal::execute()
{

	//Macierzowa(u�ywaj�c wektor�w)-------------------------------------------------------------------------------------------------------------------------
	int MSTWeight = 0; //waga
	int **tempMatrix = _graph->getGraphMatrix();


	cout << "Listowa. Zawarte kraw�dzie:" << endl;
	typedef pair<int, int> neighbour;	//Para integer�w, podobnie jak w algorytmie prima, �atwiejsze sortowanie
	list <pair<int, neighbour>> edges; //Lista par int i para integer�w, reprezentuje kraw�dzie <waga <wierzcho�ek u,wierzcho�ek v>>

	for (int i = 0; i < _graph->getVerticeAmount(); i++)	//Przepisuj� graf do lokalnej listy par <<int> <int,int>>. �atwiejsze sortowanie (domy�lnie po pierwszym elemencie pary - wadze.)
	{														//To nie jest cz�� algorytmu
		for (int j = 0; j < _graph->getVerticeAmount(); j++)
		{
			edges.push_back({ tempMatrix[i][j], {i,j} });
		}
	}


	edges.sort();	//Sortuje kraw�dzie wed�ug wagi, rosn�co
	

	int *rank = new int[_graph->getVerticeAmount()+1];	//Tablica rang
	int *previous = new int[_graph->getVerticeAmount() + 1]; //Tablica poprzednik�w

	for (int i = 0; i <= _graph->getVerticeAmount(); i++)
	{
		rank[i] = 0; //Pocz�tkowo wszystkie wierzcho�ki maj� rang� 0 i s� w osobnych drzewach

		previous[i] = i; //Ka�dy element pocz�tkowych jednoelementowych poddrzew jest swoim poprzednikiem
	}

	list <pair<int, neighbour>>::iterator i;

	for (i = edges.begin(); i != edges.end(); i++)
	{
		int u = i->second.first;	//Wybieram wierzcho�ki z pary neighbour <u,v>
		int v = i->second.second;

		int setU= findPrevious(u, previous);
		int setV = findPrevious(v, previous);

		if (setU != setV)	//Sprawdzam czy nie tworzy cyklu(u i v nie mog� nale�e� do tego samego setu)
		{
			cout << u << " -- " << v << " Waga: " << tempMatrix[u][v] << endl; 


			MSTWeight += i->first; //Zwi�kszam wag� ca�kowit� drzewa


			//Zestaw krok�w maj�cy na celu ��czenie poddrzew wed�ug rangi zawartej w tablicy rang
			setU = findPrevious(setU, previous);
			setV = findPrevious(setV, previous);

			if (rank[setU] > rank[setV])
			{
				previous[setV] = setU;	//Je�li ranga setU jest wi�ksza od rangi setV, setU staje si� poprzednikiem setV
			}
			else if (rank[setU] <= rank[setV])
			{
				previous[setU] = setV;	
			}

			if (rank[setU] == rank[setV])
			{
				rank[setV]++;	//Je�li rangi s� r�wne inkrementuj� rang� setV
			}
		}

	}
	


	cout << "Waga calkowita: " << MSTWeight << endl;

	

	//Macierzowa-------------------------------------------------------------------------------------------------------------------------------------------
	//NIE DZIA�A JAK POWINNO, BRAK SORTOWANIA, NAPRAWI�

	cout << "Macierzowa. Zawarte kraw�dzie:" << endl;
	for (int i = 0; i <= _graph->getVerticeAmount(); i++)	//Przywracam tablice rang i poprzednik�w do stanu pocz�tkowego
	{
		rank[i] = 0; 

		previous[i] = i; 
	}

	MSTWeight = 0;

	for (int i = 0; i < _graph->getVerticeAmount(); i++)
	{
		for (int j = 0; j < _graph->getVerticeAmount(); j++)
		{
			int u = i;
			int v = j;

			int setU = findPrevious(u, previous);
			int setV = findPrevious(v, previous);



			if (setU != setV)	//Sprawdzam czy nie tworzy cyklu(u i v nie mog� nale�e� do tego samego setu)
			{
				cout << u << " -- " << v << " Waga: " << tempMatrix[u][v] << endl;


				MSTWeight += tempMatrix[i][j];


									   //Zestaw krok�w maj�cy na celu ��czenie poddrzew wed�ug rangi zawartej w tablicy rang
				setU = findPrevious(setU, previous);
				setV = findPrevious(setV, previous);

				if (rank[setU] > rank[setV])
				{
					previous[setV] = setU;	//Je�li ranga setU jest wi�ksza od rangi setV, setU staje si� poprzednikiem setV
				}
				else if (rank[setU] <= rank[setV])
				{
					previous[setU] = setV;
				}

				if (rank[setU] == rank[setV])
				{
					rank[setV]++;	//Je�li rangi s� r�wne inkrementuj� rang� setV
				}
			}
		}
	}

	cout << "Waga calkowita: " << MSTWeight << endl;


	cout << "Kruskal executed" << endl;
}

Kruskal::Kruskal()
{
}


Kruskal::~Kruskal()
{
}

Kruskal::Kruskal(Graph * graph)
{
	_graph = graph;
}
