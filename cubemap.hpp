/*

    Staattinen ja dynaaminen cubemap-implementaatio
 
*/

#ifndef _CUBEMAP_HPP_
#define _CUBEMAP_HPP_

#include "externs.hpp"

using namespace std;

class Cubemap
{
    public:
        Cubemap();
        ~Cubemap();

        //** dynaamiset **

        //luo dynaamisen res-kokoisen cubemapin
        void setupDynamic(int res);
        //luo my�s tekstuurit, joita p�ivitet��n. Niiden nimet = name00, name01 jne. Ei testattu. Hidas.
        void setupDynamic(int res, string name); 

        //laittaa viewportin ja perspektiivit kuntoon.
        void startRendering(); 
        //asettaa kameran oikein kyseiselle sivulle
        void setupRenderSide(int side); 
        //kopioi kuvan tekstuuriin
        void finishRenderSide(int side);          
        //palauttaa alkuper�iset asetukset takaisin
        void endRendering(); 

        //staattiset

        //tekstuurien oletetaan olevan neli�it� molemmissa tapauksissa. 
        //luo staattisen cubemapin, jonka koko on tekstuurin koko ja kaikki sivut ovat mainittu tekstuuri
        void setupStatic(Texture *texture);
        //luo staattisencubemapin, jonka sivuina em. tekstuurit. J�rjestyksess� +x, -x, +y, -y, +z, -z
        void setupStatic(Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5, Texture *t6);

        //bindaa t�m�n cubemapin k�ytt��n. Dynaaminen tekee t�m�n automaattisesti startRendering-metodissa.
        void bind();

        //antaa ID:N
        unsigned int getID();

    private:

        bool dynamic; //dynaaminen vai staattinen
        bool renderToTexture; //rendataanko dynaamiset my�s textureihin
        //cubemapin resoluutio
        int res;
        //cubemapin ID
        unsigned int cubeMap;

        //rotaatiokulmat rendausta varten
        float rotations[6][4];
	    unsigned int cubeTarget[6];
        unsigned int textureID[6];

        //tekstuurien nimet
        string texturenames[6];
};




#endif