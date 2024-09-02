/*
	-head = tail logiikkaa viilattu
	-previous-node lisätty
	-deleteNode-funktiota korjattu
	-find-funktiota korjattua previouksen lisäyksen mukaan
	-get-funktio lisätty, hakee nodeja indexin perusteella
	-getNodeCount-funktio lisätty
*/

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <stdio.h>
#include <string.h>

template<class type>
class __declspec(dllexport) Node
{
	public:
		
		Node();
		~Node();

		type *a;
		char name[80];
		unsigned int prio;
		Node<type> *next;
		Node<type> *previous;
};

template<class type>
class __declspec(dllexport) List
{
	public:

		List();
		~List();

		void alusta();
		void pushHead(type *a);
		void pushHead(type *a, char *n, unsigned int p);
		void addHead(type *a);
		void addHead(type *a, char *n, unsigned int p);
		void pushTail(type *a);
		void pushTail(type *a, char *n, unsigned int p);
		void addTail(type *a);
		void addTail(type *a, char *n, unsigned int p);
		void deleteNode(unsigned long i);
		void freeList();
		void debug();
		
		void sort();

		Node<type> *getHead();
		Node<type> *getTail();
		Node<type> *find(char *n);
		Node<type> *get(unsigned long n);
		unsigned long getNodeCount();
		
	private:

		unsigned long nNodes;
		Node<type> *head;
		Node<type> *tail;	
		Node<type> *lastfind;
};

template<class type>
Node<type>::Node()
{	
	memset(name, 0, 80);
	prio = 0;
	a = NULL;
	next = NULL;
	previous = NULL;
}

template<class type>
Node<type>::~Node()
{
	if(a) 
	{
		delete a;
		a = NULL;
	}	
		
	memset(name, 0, 80);
	prio = 0;
	next = NULL;
	previous = NULL;
}

template<class type>
List<type>::List()
{	
	nNodes = 0;
	head = NULL;
	tail = NULL;

	lastfind = NULL;	
}

template <class type>
List<type>::~List()
{
	nNodes = 0;
	head = NULL;
	tail = NULL;	

	lastfind = NULL;	
}

template<class type>
void List<type>::alusta()
{	
	printf("lista alustettu!");
	nNodes = 0;
	head = NULL;
	tail = NULL;

	lastfind = NULL;	
}

template<class type>
void List<type>::pushHead(type *a)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
		/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;		
		head->next = NULL;

		tail->a = a;
		tail->next = NULL;
		*/	

		// Preacher, Kelpaako? ;) Hint hint! 
		Node<type> *node = new Node<type>;
		node->a = a;
		node->next = NULL;
		node->previous = NULL;
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node ennen headia
		// ja vanha node on tail
		
		Node<type> *node = new Node<type>;

		node->a = a;
		node->next = tail;
		node->previous = NULL;
				
		tail = head;
		tail->previous = node;
		head = node;

		nNodes++;

		return;
	}

	// muulloin jos listassa on _ainakin_ 2 nodea
	Node<type> *node = new Node<type>;	
	
	node->a = a;	
	node->next = head;			// node->next osoittaa 'vanhaan' headiin
	node->previous = NULL;

	head->previous = node;	
	head = node;				// uusi headi on node

	nNodes++;

	return;
}

template<class type>
void List<type>::pushHead(type *a, char *n, unsigned int p)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;		
		head->name = n;
		head->next = NULL;

		tail->a = a;
		tail->name = n;
		tail->next = NULL;
*/		
		Node<type> *node = new Node<type>;
		node->a = a;		
		node->prio = p;
		node->next = NULL;
		node->previous = NULL;

		sprintf(node->name, "%s", n);
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node ennen headia
		// ja vanha node on head
/*
		head->next = tail;
		head->a = a;
		head->name = n;

		nNodes++;
*/
		Node<type> *node = new Node<type>;

		node->a = a;
		node->prio = p;
		node->next = tail;
		node->previous = NULL;
		sprintf(node->name, "%s", n);
				
		tail = head;
		tail->previous = node;
		head = node;

		nNodes++;

		return;
	}

	// muulloin jos listassa on _ainakin_ 2 nodea
	Node<type> *node = new Node<type>;	
	
	node->a = a;	
	node->prio = p;
	node->next = head;			// node->next osoittaa 'vanhaan' headiin
	node->previous = NULL;

	sprintf(node->name, "%s", n);

	head->previous = node;	
	head = node;				// uusi headi on node

	nNodes++;

	return;
}

template<class type>
void List<type>::pushTail(type *a)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->next = NULL;

		tail->a = a;
		tail->next = NULL;
*/
		Node<type> *node = new Node<type>;
		node->a = a;
		node->next = NULL;
		node->previous = NULL;
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node ennen tailia
		// ja vanha node on head
/*
		head->next = tail;
		head->a = a;

		nNodes++;
*/
		Node<type> *node = new Node<type>;

		node->a = a;
		node->next = tail;
		node->previous = NULL;
				
		tail = head;
		tail->previous = node;
		head = node;

		nNodes++;

		return;
	}

	Node<type> *walker;
	Node<type> *prev = NULL;

	walker = head;

	if(walker)
	{
		// etsitään tail node
		while(walker->next)
		{
			prev = walker;
			walker = walker->next;
		}
	}
	
	// muulloin jos listassa on _ainakin_ 2 nodea
	Node<type> *node = new Node<type>;

	node->a = a;	
	node->next = tail;			// node->next osoittaa 'vanhaan' tailiin
	node->previous = prev;

	tail->previous = node;
	prev->next = node;			// uusi tail on node

	nNodes++;

	return;
}

template<class type>
void List<type>::pushTail(type *a, char *n, unsigned int p)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->name = n;
		head->next = NULL;

		tail->a = a;
		tail->name = n;
		tail->next = NULL;
*/
		Node<type> *node = new Node<type>;
		node->a = a;		
		node->prio = p;
		node->next = NULL;
		node->previous = NULL;

		sprintf(node->name, "%s", n);
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node ennen headia
		// ja vanha node on head
/*
		head->next = tail;
		head->a = a;
		head->name = n;

		nNodes++;
*/
		Node<type> *node = new Node<type>;

		node->a = a;
		node->prio = p;
		node->next = tail;
		node->previous = NULL;

		sprintf(node->name, "%s", n);
				
		tail = head;
		tail->previous = node;
		head = node;

		nNodes++;

		return;
	}

	Node<type> *walker;
	Node<type> *prev = NULL;

	walker = head;

	if(walker)
	{
		// etsitään tail node
		while(walker->next)
		{
			prev = walker;
			walker = walker->next;
		}
	}
	
	// muulloin jos listassa on _ainakin_ 2 nodea
	Node<type> *node = new Node<type>;

	node->a = a;	
	node->prio = p;
	node->next = tail;			// node->next osoittaa 'vanhaan' tailiin
	node->previous = prev;
	sprintf(node->name, "%s", n);

	tail->previous = node;
	prev->next = node;			// uusi tail on node

	nNodes++;
}

template<class type>
void List<type>::addHead(type *a)
{
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->next = NULL;

		tail->a = a;
		tail->next = NULL;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		node->a = a;
		node->next = NULL;
		node->previous = NULL;
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node headin
		// jälkeen
/*
		head->next = tail;
		tail->a = a;

		nNodes++;
*/	
		Node<type> *node = new Node<type>;

		node->a = a;
		node->next = NULL;
		node->previous = head;

		tail = node;		
		head->next = tail;

		nNodes++;

		return;
	}

	// jos listassa on _ainakin_ 2 nodea niin työnnetään uusi node
	// headin jälkeen
	Node<type> *node = new Node<type>;
	Node<type> *third = NULL;		
	
	third = head->next;
	third->previous = node;

	node->a = a;
	node->next = third;		// toka node otetaan talteen
	node->previous = head;

	head->next = node;		// headia seuraava node on uusi node
	
	nNodes++;
}

template<class type>
void List<type>::addHead(type *a, char *n, unsigned int p)
{
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->name = n;
		head->next = NULL;

		tail->a = a;
		tail->name = n;
		tail->next = NULL;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		node->a = a;		
		node->prio = p;
		node->next = NULL;
		node->previous = NULL;
		sprintf(node->name, "%s", n);
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node headin
		// jälkeen
/*
		head->next = tail;
		tail->a = a;
		tail->name = n;

		nNodes++;
*/
		Node<type> *node = new Node<type>;

		node->a = a;
		node->prio = p;
		node->next = NULL;
		node->previous = head;
		sprintf(node->name, "%s", n);

		tail = node;		
		head->next = tail;

		nNodes++;

		return;
	}

	// jos listassa on _ainakin_ 2 nodea niin työnnetään uusi node
	// headin jälkeen
/*
	Node<type> *node = new Node<type>;

	node->a = a;
	node->name = n;
	node->next = head->next;// toka node otetaan talteen

	head->next = node;		// headia seuraava node on uusi node

	nNodes++;
*/
	Node<type> *node = new Node<type>;
	Node<type> *third = NULL;		
	
	third = head->next;
	third->previous = node;

	node->a = a;	
	node->prio = p;
	node->next = third;		// toka node otetaan talteen
	node->previous = head;
	sprintf(node->name, "%s", n);

	head->next = node;		// headia seuraava node on uusi node
	
	nNodes++;
}

template<class type>
void List<type>::addTail(type *a)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->next = NULL;

		tail->a = a;
		tail->next = NULL;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		node->a = a;
		node->next = NULL;
		node->previous = NULL;
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node tailin
		// jälkeen
/*
		head->next = tail;
		tail->a = a;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		
		node->a = a;
		node->next = NULL;
		node->previous = head;
		
		tail = node;
		head->next = tail;						

		nNodes++;
		
		return;
	}

	Node<type> *node = new Node<type>;

	node->a = a;	
	node->next = NULL;			// node->next on NULL koska tämä on viimeinen node eli tail = node
	node->previous = tail;

	tail->next = node;
	tail = node;

	nNodes++;

	return;
}

template<class type>
void List<type>::addTail(type *a, char *n, unsigned int p)
{	
	if(!head)
	{
		// Jos listaa ei ole ennestään luodaan se.
		// Koska nodeja on tässä vaiheessa listassa vain yksi, luodaan 
		// myös tail node, koska yhdellä nodella head=tail
/*
		head = new Node<type>;
		tail = new Node<type>;

		head->a = a;
		head->name = n;
		head->next = NULL;

		tail->a = a;
		tail->name = n;
		tail->next = NULL;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		node->a = a;		
		node->prio = p;
		node->next = NULL;
		node->previous = NULL;
		sprintf(node->name, "%s", n);
		
		head = node;
		tail = node;
		
		nNodes++;

		return;
	}
	else if(!head->next)
	{
		// jos nodeja on vain 1 niin työnnetään uusi node tailin jälkeen		
/*
		head->next = tail;
		tail->a = a;
		tail->name = n;

		nNodes++;
*/
		Node<type> *node = new Node<type>;
		
		node->a = a;
		node->prio = p;
		node->next = NULL;
		node->previous = head;
		sprintf(node->name, "%s", n);
				
		tail = node;
		head->next = tail;

		nNodes++;

		return;
	}

	Node<type> *node = new Node<type>;	

	node->a = a;	
	node->prio = p;
	node->next = NULL;			// node->next on NULL koska tämä on viimeinen node eli tail->next = node
	node->previous = tail;
	sprintf(node->name, "%s", n);
	
	tail->next = node;
	tail = tail->next;	
		
	nNodes++;

	return;
}

/*
	for(i = 0; i < nEffects-1; i++)
		{
			for(j = nEffects-1; j > i; j--)
			{			
				getNode1 = effects.get(j-1);
				getNode2 = effects.get(j);

				if(getNode1->a->priority < getNode2->a->priority)
				{
					dmsMsg("SWAPPED\n");
					effect = getNode1->a;
					getNode1->a = getNode2->a;
					getNode2->a = effect;
				}
			}
		}
*/
template<class type>
void List<type>::sort()
{		
/*
	Node<type> *i = NULL;
	Node<type> *j = NULL;	
	Node<type> *tmp = NULL;

	for(i = head; i != NULL; i = i->next)
	{
		for(j = tail; j != NULL; j = j->previous)
		{
			if(i && j)
			{
				//printf("%d %d\n", *i->a, *j->a);			
				if(i->prio < j->prio)
				{
					char n1[80] = {0};
					char n2[80] = {0};
					unsigned int p1 = i->prio;
					unsigned int p2 = j->prio;

					sprintf(n1,"%s", i->name);
					sprintf(n2,"%s", j->name);
					printf("%d %d\n", i->prio, j->prio);

					type *ptr = j->a;
					j->a = i->a;
					i->a = ptr;

					sprintf(i->name,"%s", n2);
					sprintf(j->name,"%s", n1);
					i->prio = p2;
					j->prio = p1;
				}
			}
		}
	}
*/
/*
	unsigned int i, j;

	for(i = 0; i < nNodes-1; i++)
	{
		for(j = nNodes-1; j > i; j--)
		{
			Node<type> *n1 = get(i);
			Node<type> *n2 = get(j);

			if(n1->prio < n2->prio)
			{
				char t1[80] = {0};
				char t2[80] = {0};
				unsigned int p1 = n1->prio;
				unsigned int p2 = n2->prio;

				sprintf(t1,"%s", n1->name);
				sprintf(t2,"%s", n2->name);
				
				type *ptr = n2->a;
				n2->a = n1->a;
				n1->a = ptr;

				sprintf(n1->name,"%s", t2);
				sprintf(n2->name,"%s", t1);
				n1->prio = p2;
				n2->prio = p1;
			}
		}
	}
*/

	unsigned int i, j;
	Node<type> *n1 = head;
	Node<type> *n2 = tail;

	for(i = 0; i < nNodes-1; i++, n1 = n1->next)
	{
		n2 = tail;

		for(j = nNodes-1; j > i; j--, n2 = n2->previous)
		{	
			if(n1 && n2)
			{
				if(n1->prio < n2->prio)
				{
					char t1[80] = {0};
					char t2[80] = {0};
					unsigned int p1 = n1->prio;
					unsigned int p2 = n2->prio;

					sprintf(t1,"%s", n1->name);
					sprintf(t2,"%s", n2->name);
					
					type *ptr = n2->a;
					n2->a = n1->a;
					n1->a = ptr;

					sprintf(n1->name,"%s", t2);
					sprintf(n2->name,"%s", t1);
					n1->prio = p2;
					n2->prio = p1;
				}
			}
		}
	}
}

template<class type>
void List<type>::debug()
{
	int i;	
	Node<type> *walker;
	Node<type> *previous;
	Node<type> *next;

	i = 0;	
	if(head != NULL)
	{
		walker = head;
		next = head->next;
		previous = head->previous;
	
		if(head == tail)
		{
			printf("Node count: %d\n", nNodes);
			//printf("Node name: %s, value: %d\n", walker->name, *walker->a);
			printf("Node name: %s\n", walker->name);
			
			return;
		}

		if(walker)
		{			
			printf("Node count: %d\n", nNodes);
			while(walker)
			{					
				//printf("Node name: %s, value: %d\n", walker->name, *walker->a);
				printf("Node name: %s", walker->name);
				
				if(previous)
				{	
					//printf("Previous Node: %s, value: %d\n", previous->name, *previous->a);
					printf(", Previous Node: %s\n", previous->name);
				}
				else
				{
					printf("\n");
				}
				i++;
			
				walker = walker->next;			
				(walker) ? previous = walker->previous : previous = previous;
			}
		}			
	}
	else
	{
		printf("Lista on tyhjä!\n");
	}
}

template<class type>
void List<type>::freeList()
{
	Node<type> *walker;
	Node<type> *tmp;

	walker = head;	
	
	if(walker)
	{
		tmp = walker;
		while(walker)
		{
			walker = walker->next;

			delete tmp;
			tmp = walker;
		}
	
		head = tail = NULL;
	}
	else
	{
		// virhe
		//printf("List Error: (Node)head = NULL, lista on jo tyhjä\n");
	}
}

template<class type>
void List<type>::deleteNode(unsigned long i)
{	
	if(i >= 0 && i < nNodes)
	{
		/***    Erikoistapaukset!    ***/
		// jos listassa on vain yksi node
		if(head && !head->next)
		{						
			if(head)
			{
				head->a = NULL;
				delete head;
				head = NULL;
			}
			
			nNodes--;
			return;
		} 

		// jos poistetaan ensimmäistä nodea
		if(i == 0)
		{	
			Node <type> *tmp = NULL;

			tmp = head->next;
			tmp->previous = NULL;

			if(head) 
			{
				delete head;
			}

			head = tmp;
															
			nNodes--;
			return;

		}
		
		// jos poistetaan viimeistä nodea
		// parannetaan kun lisätän previous node mukaan
		if(i == (nNodes-1))
		{
			Node<type> *walker;
			Node<type> *prev;

			walker = head;
			prev = walker;

			while(walker->next)
			{
				prev = walker;
				walker = walker->next;
			}

			prev->next = NULL;
			delete walker;
			nNodes--;

			return;
		}

			unsigned int count;

			Node<type> *walker;
			Node<type> *prev;
			Node<type> *uusi;

			walker = head;
			prev = walker;

			for(count = 0; count < i; count++)
			{
				prev = walker;
				walker = walker->next;
			}			

			if(!walker) return;
			if(!prev) return;

			Node<type> *tmp;

			uusi = walker->next;
			uusi->previous = prev;
			tmp = walker;

			prev->next = uusi;
			delete tmp;

			nNodes--;

			return;	
	}

}

template<class type>
Node<type> *List<type>::getHead()
{
	return head;
}

template<class type>
Node<type> *List<type>::getTail()
{
	return tail;
}

// palauttaa osoittimen nodeen joka vastaa haettua nimeä
template<class type>
Node<type> *List<type>::find(char *n)
{	
	Node<type> *walker;
	Node<type> *current;

	walker = head;
	
	if(head && tail)
	{
			if(!strcmp(head->name, n))
			{
				//printf("\nLöytyi päästä!\n");
				lastfind = head;
				return lastfind;
			}

			if(!strcmp(tail->name, n))
			{
				//printf("\nLöytyi hännästä!\n");
				lastfind = tail;
				return lastfind;
			}		
	}
	else
	{
		return false;
	}

	// jos etsitään samaa kuin viime haulla niin palautetaan viimeisin
	if(lastfind != NULL)
	{
		if(!strcmp(lastfind->name, n))
		{
			//printf("\nLöytyi vanha!\n");
			return lastfind;
		}

		// tarkistetaan josko olisi sivu osuma node:lle
		if(lastfind->next)
		{		
			if(!strcmp(lastfind->next->name, n))
			{
				//printf("\nLöytyi sivuosuma: next!\n");
				lastfind = lastfind->next;
				return lastfind;
			}		
		}

		// tarkistetaan josko olisi sivu osuma node:lle
		if(lastfind->previous)
		{		
			if(!strcmp(lastfind->previous->name, n))
			{
				//printf("\nLöytyi sivuosuma: previous!\n");
				lastfind = lastfind->previous;
				return lastfind;
			}		
		}
	}
		
	// muutoin kahlataan lista läpi ...
	// tässä voisi pistää walkerit listan keskeltä menemään molempiin suuntiin
	// niin saisi viilattua tuota läpi käynnin aikaa. Tähän pitäisi laskea
	// yksi middle-node
	while(walker)
	{
		current = walker;

		if(!strcmp(current->name, n))
		{						
			//printf("Osuma!\n");
			lastfind = current;
			lastfind->next = current->next;
			return current;
		}

		walker = walker->next;		
	}	

	return NULL;
}

// palauttaa osoittimen nodeen joka vastaa haettua node indeksiä
template<class type>
Node<type> *List<type>::get(unsigned long n)
{	
	Node<type> *walker;
	Node<type> *current = NULL;
	unsigned int i;

	walker = head;
	current = walker;
/*
	// jos etsitään samaa kuin viime haulla niin palautetaan viimeisin
	if(lastfind != NULL)
	{
		if(!strcmp(lastfind->name, n))
		{
			printf("\nLöytyi vanha!\n");
			return lastfind;
		}

		// tarkistetaan josko olisi sivu osuma node:lle
		if(lastfind->next)
		{		
			if(!strcmp(lastfind->next->name, n))
			{
				printf("\nLöytyi sivuosuma: next!\n");
				lastfind = lastfind->next;
				return lastfind;
			}		
		}

		// tarkistetaan josko olisi sivu osuma node:lle
		if(lastfind->previous)
		{		
			if(!strcmp(lastfind->previous->name, n))
			{
				printf("\nLöytyi sivuosuma: previous!\n");
				lastfind = lastfind->previous;
				return lastfind;
			}		
		}
	}	
*/	
	// muutoin kahlataan lista läpi ...
	// tässä voisi pistää walkerit listan keskeltä menemään molempiin suuntiin
	// niin saisi viilattua tuota läpi käynnin aikaa. Tähän pitäisi laskea
	// yksi middle-node
	i = 0;
	//printf("haku\n");
	if(n >= 0 && n <= nNodes)
	{
		do
		{
			current = walker;
			walker = walker->next;
			//printf("%d\n",i);
		}
		while(walker && i++ != n);

		return current;
	}	

	return NULL;
}

template <class type>
unsigned long List<type>::getNodeCount()
{
	return nNodes;
}

#endif
