/* File: pokemoncal.cpp
 * Author: CRE
 * Last Edited: Fri Dec 16 17:01:46 2016
 */

#include "crelib/crelib.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#define TYPE_NUMBER 18
using namespace cre;
using namespace std;

double AttriEff[TYPE_NUMBER][TYPE_NUMBER]={
	{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,0.0,1.0,1.0,0.5,1.0},
	{1.0,0.5,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,1.0,2.0,1.0},
	{1.0,2.0,0.5,0.5,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0,1.0},
	{1.0,0.5,2.0,0.5,1.0,1.0,1.0,0.5,2.0,0.5,1.0,0.5,2.0,1.0,0.5,1.0,0.5,1.0},
	{1.0,1.0,2.0,0.5,0.5,1.0,1.0,1.0,0.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0},
	{1.0,0.5,0.5,2.0,1.0,0.5,1.0,1.0,2.0,2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0},
	{2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5,0.5,0.5,2.0,0.0,1.0,2.0,2.0,0.5},
	{1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5,0.5,1.0,1.0,1.0,0.5,0.5,1.0,1.0,0.0,2.0},
	{1.0,2.0,1.0,0.5,2.0,1.0,1.0,2.0,1.0,0.0,1.0,0.5,2.0,1.0,1.0,1.0,2.0,1.0},
	{1.0,1.0,1.0,2.0,0.5,1.0,2.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,0.5,1.0},
	{1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.0,0.5,1.0},
	{1.0,0.5,1.0,2.0,1.0,1.0,0.5,0.5,1.0,0.5,2.0,1.0,1.0,0.5,1.0,2.0,0.5,0.5},
	{1.0,2.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0},
	{0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0},
	{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,0.0},
	{1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5},
	{1.0,0.5,0.5,1.0,0.5,2.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5,2.0},
	{1.0,0.5,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,0.5,1.0}
};

uint AGA[TYPE_NUMBER];

const char * TypeName[TYPE_NUMBER]={"Normal", "Fire", "Water", "Grass", "Electric", "Ice", "Fight", "Poison", "Land", "Fly", "Super", "Insect", "Stone", "Ghost", "Dragon", "Evil", "Steel", "Fairy"};

double attack(uint A, uint B, uint C)//calculate attack effect of AB to C
{
	return max(AttriEff[A][C],AttriEff[B][C]);
}

double defend(uint A, uint B, uint C)//calculate defence effect of AB by C
{
	if (A==B) return AttriEff[C][A];
	return (AttriEff[C][A]*AttriEff[C][B]);
}

void readAE(FILE * TheFile)
{
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		for (uint j=0;j<TYPE_NUMBER;++j)
		{
			fscanf(TheFile,"%lf", &(AttriEff[i][j]));
		}
	}
}

void printAE()
{
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		for (uint j=0;j<TYPE_NUMBER;++j)
		{
			printf("%.1lf\t", AttriEff[i][j]);
		}
		printf("\n");
	}
}

void getAnD(uint A, uint B)
{
	printf("%s+%s:\nTypes:", TypeName[A],TypeName[B]);
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		printf("\t%s", TypeName[i]);
	}
	printf("\nAttack:");
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		printf("\t%.1lf", attack(A,B,i));
	}
	printf("\nDefend:");
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		printf("\t%.1lf", defend(A,B,i));
	}
}

void getADChart()
{
	printf("Number of Effects(Good attack/Bad attack;Good defend/Bad defend) and AGA tables:");
	uint GA=0, BA=0, GD=0, BD=0;
	bool First=true;
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		First=true;
		for (uint j=0;j<=i;++j)
		{
			GA=0;
			BA=0;
			GD=0;
			BD=0;
			for (uint k=0;k<TYPE_NUMBER;++k)
			{
				if (attack(i,j,k)>1.0) ++GA;
				if (attack(i,j,k)<1.0) ++BA;
				if (defend(i,j,k)<1.0-0.1) ++GD;
				if (defend(i,j,k)>1.0+0.1) {++BD;++AGA[k];}
			}
			if (!First) printf("\t");
			First=false;
			printf("%u/%u;%u/%u", GA,BA,GD,BD);
		}
		printf("\n");
	}
	printf("AGA:");
	for (uint k=0;k<TYPE_NUMBER;++k)
	{
		printf("\n%s: %u", TypeName[k], AGA[k]);
	}
}

void help()
{
	fprintf(stderr, "pck to show tables\npkc a b to show attack and defend effects\npkc --help to show this help\na,b are numbers:");
	for (uint i=0;i<TYPE_NUMBER;++i)
	{
		fprintf(stderr, "\n%u: %s", i, TypeName[i]);
	}
}

int main (int argc, const char ** argv)
{
	/* read the AE data
	FILE * TheFile;
	TheFile=fopen("AE.txt", "r");
	if (TheFile==NULL) die("No AE.txt in the directory!");
	readAE(TheFile);
	fclose(TheFile);
	*/
	if (argc==1) getADChart();
	else if (argc==3)
	{
		getAnD(atoi(argv[1]),atoi(argv[2]));
	}
	else help();
	return 0;
}
