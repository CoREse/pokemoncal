/* File: pokemoncal.cpp
 * Author: CRE
 * Last Edited: Thu Dec 15 15:40:12 2016
 */

#include "crelib/crelib.h"
#include <algorithm>
#include <stdio.h>
#define TYPE_NUMBER 18
using namespace cre;
using namespace std;

double AttriEff[TYPE_NUMBER][TYPE_NUMBER];

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

int main (int argc, const char ** argv)
{
	if (argc!=2) return 1;
	FILE * TheFile;
	TheFile=fopen(argv[1], "r");
	readAE(TheFile);
	fclose(TheFile);
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
	return 0;
}
