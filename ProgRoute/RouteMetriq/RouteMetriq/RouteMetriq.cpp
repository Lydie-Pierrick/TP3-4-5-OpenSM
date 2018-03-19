// RouteMetriq.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <set>

#include "calculation.h"

using namespace std;

/**
* Instruction pour l'utilisation des fichiers d'entrées du programme.
*/
void usage(char * name)
{
	cout << "Usage : " << name << " [topoFile] [routeFile]" << endl;
	getchar();
	exit(0);
}

/**
* Fonction principale qui exécute les différents modules du programme.
*/
int main(int argc, char *argv[])
{
	// TO REMOVE !!!!
	// !!!
	argc = 2;
	argv[1] = "Topo1.topo";
	argv[2] = "Topo1.route";

	// END TO REMOVE !!!!

	if (argc < 2) usage(argv[0]);

	char *topoFile = argv[1];
	char *routeFile = argv[2];

	Calculation routecalc(topoFile, routeFile);

	/*
	// Affichage de la topologie
	cout << "Topo file data" << endl;
	getchar();
	routecalc.printTopology();

	// Affichage de la table de routage
	cout << "Route file data" << endl;
	getchar();
	routecalc.printRouting();
	*/

	cout << "Number of hops calculation" << endl;
	//getchar();
	cout << endl << "\tMinimum number of hops = " << routecalc.calculate() << endl;

	cout << "Route balancing " << endl;
	//getchar();
	cout << "\tRoute balancing = " << routecalc.balance() << endl;
	getchar();

	cout << endl;
	return 0;
}
