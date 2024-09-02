
#include <stdio.h>
#include "Lista2.hpp"

//#define LISTDEBUG

Lista2nSolmu::Lista2nSolmu()
{
}
Lista2nSolmu::~Lista2nSolmu()
{
}
Lista2nSolmu::Lista2nSolmu(void *ptr)
{
	payload = ptr;
}
void Lista2nSolmu::set(void *ptr)
{
	payload = ptr;
}
void Lista2nSolmu::print()
{

}
Lista2::Lista2()
{
	//nollataan kaikki osoittimet
	start = 0;
	current = 0;
	end = 0;
	//nollataan solmujen määrä
	solmuja = 0;
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::Lista2() : Lista2 luotu");
#endif
}
Lista2::~Lista2()
{
}

//lisätään alkio Lista2n loppuun
void Lista2::add(void *dataptr)
{
	Lista2nSolmu *temp;
	solmuja++;

	if (start == 0) //lisätään Lista2an ensimmäistä alkiota
	{
		//luodaan uusi solmu
		temp = new Lista2nSolmu(dataptr);

		//koska solmu on ensimmäinen, nämä ovat molemmat 0
		temp->previous = 0;
		temp->next = 0;

		//molemmat "pääosoittimet" osoittamaan ekaan solmuun
		start = temp;
		end = temp;

#ifdef LISTDEBUG
		loki->writeToLog("Lista2::add : Luotu ensimmäinen Lista2n solmu");
		temp->print();
#endif
	}
	else
	{
		//luodaan uusi solmu Lista2n perälle
		Lista2nSolmu *temp = new Lista2nSolmu(dataptr);
		//seuraavaa solmua ei tietenkään ole
		temp->next = 0; 

		//menee yhden askeleen lopun jälkeen. Muutetaan vanha Lista2n loppu osoittamaan tähän solmuun
		temp->previous = end;
		end->next = temp;

		//uusi solmu on Lista2n viimeinen
		end = temp;		
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::add : Luotu uusi solmu Lista2an");
		temp->print();
#endif
	}
}

//laitetaan uusi alkio työosoittimen kohdalle
bool Lista2::insert(void *dataptr)
{
	if (current==0)
	{
		return false; //työosoitin ei ole kelvollinen, joten ei tehdä mitään ja palautetaan false
	}
	//ollaan Lista2n lopussa
	if (current == end)
	{
		add(dataptr); //laitetaan Lista2n loppuun uusi alkio
		return true;
	}
	//lisääminen onnistuu joka tapauksessa tästä eteenpäin, joten lisätään solmujen määrää
	solmuja++;
	//ollaan Lista2n alussa tai keskellä, joten luodaan uusi solmu
	Lista2nSolmu *temp = new Lista2nSolmu(dataptr); 
	//asetetaan uusi solmu osoittamaan seuraavaan solmuun
	temp->next = current->next;
	//seuraavan solmun previous osoittaa uuteen solmuun
	current->next->previous = temp; 
	//seuraava solmu hoideltu
	//uusi solmu tulee väliin, joten sen edellinen on nykyinen
	temp->previous = current;
	//lopulta säädetään currentin seuraavan osoitin uuteen
	current->next = temp; 

	//huh
	return true;
}


//poistetaan alkio työpointterin kohdalla
bool Lista2::remove()
{
	if (start == 0)	//Lista2 tyhjä
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::remove : ei ole mitään poistettavaa");
#endif
		return false; //ei ole mitään poistettavaa
	}
	if (start == end)		//vain yksi alkio Lista2ssa (current == start)
	{
		solmuja--;
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::remove : vain yksi alkio Lista2ssa");
#endif
		if (current->payload != 0)	//poistetaan lasti jos sitä on
		{
			delete current->payload;
		}
		delete current; //tuhotaan solmu

		start = 0;
		end = 0;
		current = 0; //nollataan pointterit

		return true;
	}
	if (current == end)	//yritetään poistaa viimeistä alkiota
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::remove : poistetaan viimeinen alkio");
#endif
		removeLast();	//solmujen määrä muutetaan täällä
		return false;
	}
	if (current == start) //yritetään poistaa ensimmäistä alkiota
	{
		solmuja--;
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::remove : poistetaan ensimmäistä alkiota");
#endif
		Lista2nSolmu *temp = start->next;	//osoitetaan Lista2n toiseen alkioon
		temp->previous = 0;					//josta tehdään Lista2n ensimmäinen alkio
		if (start->payload != 0)
		{
			delete start->payload;
		}
		delete start; //poistetaan start-osoittimen osoittama alkio
		start = temp; //ja laitetaan se osoittamaan Lista2n toiseen alkioon, joka on nyt ensimmäinen
		current = temp; //current myös

		return true;
	}
	//erikoistapaukset käsitelty

	solmuja--;
	Lista2nSolmu *temp;
	if (current->next != 0)
		temp = current->next;
	else
		temp = current->previous;

	current->previous->next = current->next; //hypätään currentin ylitse
	current->next->previous = current->previous;

	if (current->payload != 0)
	{
		delete current->payload;
	}
	delete current;
	current = temp; //current on joko seuraava tai edellinen (jos seuraavaa ei ollut)
	return true;
}

//poistetaan Lista2n viimeinen alkio

bool Lista2::removeLast()
{
	if (start == 0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::removeLast : ei ole mitään poistettavaa");
#endif
		return false; //ei ole mitään poistettavaa
	}
	else
	{
		solmuja--;
		if (end->previous == 0) //jos Lista2ssa on vain yksi alkio
		{
#ifdef LISTDEBUG
			loki->writeToLog("Lista2::removeLast : vain yksi alkio");
#endif
			if (end->payload != 0) //jos Lista2 osoittaa johonkin
			{
				delete end->payload;
			}
			delete end;	//poistetaan viimeinen alkio
			end = 0;	//nollataan nämä, muuten ne osoittavat jonnekin jota ei ole enää olemassa
			start = 0;
			current = 0;
		}
		else		//poistetaan viimeinen alkio
		{
#ifdef LISTDEBUG
			loki->writeToLog("Lista2::removeLast");
#endif
			//solmu, joka osoittaa edelliseen
			Lista2nSolmu *temp = end->previous;

			//tuhotaan viimeisen solmun lasti
			if (end->payload != 0)
			{
				delete end->payload;
			}
			//jos current osoittaa loppuun, vaihdetaan se osoittamaan uuteen loppuun (muuten ryskis)
			if (current == end)
			{
				current = current->previous;
			}
			delete end;
			end = temp;
			temp->next = 0;
		}
		return true; //poisto onnistui
	}
}

//tuhotaan koko Lista2
void Lista2::destroy()
{
	int temp = solmuja; //solmuja muuttuu removeLastissa, joten siksi tehdään siitä kopio nyt
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::destroy");
#endif
	for (int i=0;i<temp;i++)
		removeLast();
}

bool Lista2::goToStart()
{
	if (start!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::goToStart() onnistui");
#endif
		current = start;	//Lista2 on olemassa
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::goToStart() epäonnistui");
#endif
	current = 0;
	return false;
}
bool Lista2::goToEnd()
{
	if (end!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::goToEnd() onnistui");
#endif
		current = end;	//Lista2 on olemassa
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::goToStart() epäonnistui");
#endif
	current = 0;
	return false;
}
bool Lista2::goForward()
{
	if (current == end)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::goForward() yritti mennä lopusta ylitse!");
#endif
		return false;
	}
	if (current->next!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::goForward() onnistui");
#endif
		current = current->next;
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::goForward() epäonnistui");
#endif
	return false;
}
bool Lista2::goBackwards()
{
	if (current->previous!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista2::goBackwards() onnistui");
#endif
		current = current->previous;
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::goBackwards() epäonnistui");
#endif
	return false;
}

bool Lista2::goToNode(int number)
{
	/* paskaa koodia! */
	bool value;
	goToStart();

	for (int i=0;i<number;i++)
	{
		value = goForward();
	}
	return value;
}
int Lista2::getCurrentNodeNumber()
{
	/* paskaa koodia! */
	int i=0;
	Lista2nSolmu *walker = start;
	while (walker != current)
	{
		i++;
		walker = walker->next;
	}
	return i;

}


void *Lista2::getFirst()
{
	return start->payload;
}
void *Lista2::getLast()
{
	return end->payload;
}
void *Lista2::getCurrent()
{
	if(current)
		return current->payload;
	else return 0;

}
void Lista2::setCurrent(void *ptr)
{
	if (current->payload) //tuhotaan vanha
	{
		delete current->payload;
	}
	current->payload = ptr; 
}
int Lista2::getNodeCount()
{
	return solmuja;
}

bool Lista2::isAtEnd()
{
	if (current == end)
		return true;
	else return false;
}

bool Lista2::isAtStart()
{
	if (current == start)
		return true;
	else return false;
}

void Lista2::print()
{
#ifdef LISTDEBUG
	loki->writeToLog("Lista2::print");
#endif
	Lista2nSolmu *walker = start;
	if (walker == 0)
		return; //Lista2ssa ei ole mitään
	while (walker!=0)
	{
		walker->print();
		walker = walker->next;
	}
}
