#include "cAreaDiGioco.h"
#include "cPacman.h"

cAreaDiGioco::cAreaDiGioco()
{
	//inizializzo i fantasmi
	fantasma1 = cFantasma(1);
	fantasma2 = cFantasma(2);
	fantasma3 = cFantasma(3);

	//inizializza il punteggio 
	this->punteggio = 0;
	this->inizializzaLvl1();
}

void cAreaDiGioco::inizializzaLvl1()
{
	for (int i = 0; i < RIGHE; i++)
	{
		for (int j = 0; j < COLONNE; j++)
		{
			griglia[i][j] = livello1[i][j];
		}
	}

	//inizializza la matrice 
	//inizializza il punteggio 
	//inizializza il pacman
		//trovo il punto di partenza
	cPunto coord = getFromChar('I');
	//setto coord al Pacman
	pacman.setC(coord.getC());
	pacman.setR(coord.getR());
	griglia[coord.getR()][coord.getC()] = VUOTO;

	//inizializza i fantasmi
		//li posiziono nella "gabbia"

}

void cAreaDiGioco::mangiaCaramella()
{
	if (griglia[pacman.getR()][pacman.getC()] == CARAMELLA)
	{
		griglia[pacman.getR()][pacman.getC()] = VUOTO;
		punteggio+= 10;
	}
}

void cAreaDiGioco::next(char dir)
{
	if (dir == 'w' || dir == 'a' || dir == 's' || dir == 'd')
		pacman.setDir(dir);

	cPunto posPrec = pacman.getCoord();

	if(controllaMuri())
		pacman.muovi();

	mangiaCaramella();
}

int cAreaDiGioco::getPunteggio()
{
	return this->punteggio;
}

bool cAreaDiGioco::controllaMuri()
{
	if (pacman.getDirezione() == 'w' && griglia[pacman.getR() - 1][pacman.getC()] == MURO)
		return false;

	if (pacman.getDirezione() == 'a' && griglia[pacman.getR()][pacman.getC() - 1] == MURO)
		return false;

	if (pacman.getDirezione() == 's' && griglia[pacman.getR() + 1][pacman.getC()] == MURO)
		return false;

	if (pacman.getDirezione() == 'd' && griglia[pacman.getR()][pacman.getC() + 1] == MURO)
		return false;

	return true;
}

cPunto cAreaDiGioco::getFromChar(char carattereDaCercare)
{
	for (int i = 0; i < RIGHE; i++)
	{
		for (int j = 0; j < COLONNE; j++)
		{
			if (griglia[i][j] == carattereDaCercare)
			{
				//setta il punto i j sul pacman
				return cPunto(i, j);
			}

		}
	}
	return cPunto(-1, -1);
}

string cAreaDiGioco::getFrame()
{
	string tmp = "";
	for (int i = 0; i < RIGHE; i++)
	{
		for (int j = 0; j < COLONNE; j++)
		{
			tmp += griglia[i][j];
		}
		tmp += "\r\n";
	}

	int indexACapo = tmp.find('\n');

	//pacman
	int posPacman = pacman.getR() * (indexACapo + 1) + pacman.getC();
	tmp.replace(posPacman, 1, "C");

	//fantasma1 - Inky
	int posFantasma1 = fantasma1.getR() * (indexACapo + 1) + fantasma1.getC();
	tmp.replace(posFantasma1, 1, "I");

	//fantasma2 - Pinky
	int posFantasma2 = fantasma2.getR() * (indexACapo + 1) + fantasma2.getC();
	tmp.replace(posFantasma2, 1, "P");

	//fantasma3 - Blinky
	int posFantasma3 = fantasma3.getR() * (indexACapo + 1) + fantasma3.getC();
	tmp.replace(posFantasma3, 1, "B");

	return tmp;
}