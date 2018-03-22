#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "calculation.h"
#include "topology.h"
#include "routing.h"

using namespace std;

Calculation::Calculation() {}

Calculation::~Calculation() {}

/**
* Constructeur qui charge les informations
* de la topologie et table de routage en mémoire.
*/
Calculation::Calculation(char* topoFile, char* routeFile)
{
	topologyTable.loadData(topoFile);
	routingTable.loadData(routeFile);
}

/**
* Méthode qui calcule le nombre de sauts
* d'un noeud source jusqu'au noeud destination.
* n’oubliez pas de compléter le code !
*/
int Calculation::getHopCount(int fromId, int toId)
{
	int count = 0;

	struct hostNode * fromHost = topologyTable.getHostById(fromId);
	struct hostNode * toHost = topologyTable.getHostById(toId);

	//Noeud de calcul source
	string fromNode = fromHost->name;
	//Noeud de calcul destination
	string toNode = topologyTable.getHostById(toId)->name;

	string switchName = fromHost->dstName;

	struct routeItem * routeItem;
	struct switchNode * switchNode;
	string nextName = switchName;
	int idOut;

	// permet de charger la table de routage
	while (nextName.compare(toNode) != 0) // Tant que le nom suivant n'est pas le nom de destination
	{
		routeItem = routingTable.getTableByName(nextName);
		switchNode = topologyTable.getSwitchByName(nextName);

		// Récupérer dans la table de routage du routeItem le port correspondant à la destination
		idOut = routeItem->outport.at(distance(routeItem->dstInfo.begin(), find(routeItem->dstInfo.begin(), routeItem->dstInfo.end(), toHost->name)));

		cout << "\nPort de sortie : " << idOut << endl;

		nextName = switchNode->dstName.at(distance(switchNode->srcPort.begin(), find(switchNode->srcPort.begin(), switchNode->srcPort.end(), idOut)));

		cout << "\nProchain switch : " << nextName << endl;

		count++;
	}

	//TODO
	//Parcourir la table de routage du noeud fromId vers le toId
	//Aide : Regarder la struture routeItem et switchNode elles pourront vous aider.
	//Aide : struct routeItem * item = routingTable.getTableByName(switchName); permet de charger la table de routage
	//Retourner le nombre de sauts du noeud fromId vers le toId	
	cout << "From " << fromNode << " to " << toNode << ": Hop Count = " << count << endl;

	return count;
}

/**
* Méthode qui implémente la métrique Minhop.
*/
int Calculation::calculate()
{
	//TODO 
	//Implémenter l'algo du calcul du nombre de sauts
	//Aide : Pour recueperer le nombre de saut de source vers destination -> getHopCount(source, destination);
	//Aide : Pour recuperer le nombre de HCA -> topologyTable.getHostCount();
	//retourner le minimum trouver.

	int minHop = 0; //Min value
	int cpt = 0;
	int hopCount = 0;

	for (int i = 0; i < topologyTable.getHostCount(); i++)
	{
		cout << "------------------------------------------" << endl;

		cpt = 0;
		minHop = 0;

		for (int j = 0; j < topologyTable.getHostCount(); j++)
		{
			cout << "-----------------" << endl;
			if (i != j)
			{				
				hopCount = getHopCount(i, j);
				cpt = max(cpt, hopCount);
			}
		}

		minHop = max(minHop, cpt);
	}
	
	return minHop;
}

/**
* Méthode qui calcule la charge d'un noeud
* source jusqu'au noeud destination.
*/
int Calculation::getRoute(int fromId, int toId)
{
	struct hostNode * fromHost = topologyTable.getHostById(fromId);

	string fromNode = fromHost->name;

	string toNode = topologyTable.getSwitchById(toId)->name;

	cout << "From " << fromNode << " to " << toNode;

	string switchName = fromHost->dstName;


	//TODO
	//Parcourir la table de routage du noeud fromId vers le toId
	//Aide : Regarder la structure routeItem et switchNode elles pourront vous aider.
	//Aide : struct routeItem * item = routingTable.getTableByName(switchName); permet de charger la table de routage
	//Retourner 1 si le noeud toId est atteilgnable depuis fromId sinon 0

	return 0;
}

/**
* Méthode qui implémente la métrique nombre de chemins disjoints.
*/
int Calculation::balance()
{
	int cpt = 0;

	//TODO 
	//Implémenter l'algo du calcul de chemins disjoints 
	//Aide : Pour recueperer le nombre de sauts de source vers destination -> getHopCount(source, destination);
	//Aide : Pour recuperer le nombre de HCA -> topologyTable.getHostCount();
	//retourner la valeur maximale trouvée

	return cpt;
}

