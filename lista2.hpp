#ifndef _Lista2_HPP_
#define _Lista2_HPP_

class Lista2nSolmu
{
public:

	//muodostimet ja tuhoajat
	Lista2nSolmu();
	Lista2nSolmu(void *ptr);
	~Lista2nSolmu();

	//asettaa solmun datan halutuksi
	void set(void *ptr);

	//tulostaa tiedot
	void print();

	//osoittimet seuraaviin osiin
	class Lista2nSolmu *next;
	class Lista2nSolmu *previous;

	//data, jota solmu kantaa
	void *payload;

};

class Lista2
{
public:
	Lista2();
	~Lista2();
	
	//lisätään Lista2n loppuun alkio (onnistuu aina)
	void add(void *dataptr);
	//poistetaan Lista2n viimeinen alkio (palauttaa false jos Lista2 on tyhjä)
	bool removeLast();
	//lisätään työpointterin jälkeen alkio (palauttaa false jos työpointteri ei ole kelvollinen)
	bool insert(void *dataptr);
	//poistetaan alkio työpointterin kohdalta
	bool remove();

	//tuhotaan koko Lista2 ja vapautetaan kaikki tiedot
	void destroy();

	//asettaa työpointterin Lista2n alkuun (palauttaa false jos Lista2 on tyhjä)
	bool goToStart();
	//asettaa työpointterin Lista2n loppuun (palauttaa false jos Lista2 on tyhjä)
	bool goToEnd();
	//liikuttaa työpointteria eteenpäin (palauttaa false jos Lista2 on loppu)
	bool goForward();
	//liikuttaa työpointteria taaksepäin (palauttaa false jos ollaan alussa)
	bool goBackwards();
	//menee haluttuun nodeen (palauttaa false jos ei onnistu)
	bool goToNode(int number); 

	//tutkii, ollaanko ekassa nodessa
	bool isAtEnd();
	//tutkii, ollaanko vikassa nodessa
	bool isAtStart();

	//antaa ensimmäisen noden osoittaman tiedon
	void *getFirst();
	//antaa viimeisen noden osoittaman tiedon
	void *getLast();
	//antaa työpointterin osoittaman tiedon
	void *getCurrent();
	//asettaa työpointterin nodeen uuden tiedon (tuhoaa vanhan jos siellä sellaista on)
	void setCurrent(void *ptr);
	//kertoo kuinka monta solmua Lista2ssa on
	int getNodeCount();
	//kertoo nykyisen noden
	int getCurrentNodeNumber();

	//tulostetaan Lista2 lokiin (debug)
	void print();
private:
	int solmuja;
	Lista2nSolmu *start;
	Lista2nSolmu *current;
	Lista2nSolmu *end;

};

#endif
