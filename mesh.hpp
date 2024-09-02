#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>
#include "externs.hpp"


//tekstuurikoordinaatti
//huom! jos t�h�n laittaa lis�� muuttujia, niin VBO s�rkyy. 
class TTexCoord
{
public:
    TTexCoord() { this->u = 0.0f; this->v = 0.0f; }
    TTexCoord(float u, float v) { this->u = u; this->v = v; };

    TTexCoord operator + (TTexCoord const &uv);
    TTexCoord operator - (TTexCoord const &uv);
    TTexCoord operator * (float const &f);
    TTexCoord operator *= (float const &f);

    float u, v;
};

//verteksi
class TVertex
{
public:
    TVertex() { this->position = Vector3(0, 0, 0); this->normal = Vector3(0, 0, 0); this->uv.u = 0.0f; this->uv.v = 0.0f;}
    TVertex(const TVertex &v) { this->position = v.position; this->normal = v.normal; this->uv = v.uv; }
    Vector3 position;
    Vector3 normal;
    TTexCoord uv;
};

//face
class TFace
{
public:
    TFace() { this->a = 0; this->b = 0; this->c = 0; this->normal = Vector3(0, 0, 0); }
    TFace(const TFace &f) { this->a = f.a; this->b = f.b; this->c = f.c; this->normal = f.normal; this->color = color; }
    Vector3 normal;
    Vector3 color;
    int a, b, c;
};

//reuna
class TEdge
{
public:
	int face1, face2; //indeksit faceihin
	int a, b; //indeksit vertekseihin
};

//bitmaskit parametrien v�litykseen
const int MESH_VERTEX_BIT = (1 << 1);
const int MESH_NORMAL_BIT = (1 << 2);
const int MESH_COLOR_BIT = (1 << 3);
const int MESH_TEXTURE0_BIT = (1 << 4);
const int MESH_TEXTURE1_BIT = (1 << 5);
const int MESH_TEXTURE2_BIT = (1 << 6);
const int MESH_TEXTURE3_BIT = (1 << 7);

const int MESH_TEXTURE_BIT = MESH_TEXTURE0_BIT;

class TMesh
{
public:

    //tyhj� meshi
    TMesh(); 

    //meshi, jossa n�in paljon tilaa valmiiksi
    TMesh(int vertexcount, int facecount); 

    ~TMesh();

    //nollaa kaikki muuttujat 
    void clear();

    //tuhoaa kaiken mit� tmeshiss� on ja vapauttaa muistin. Kutsuu my�s clear()
    void destroy();

    //luo kopion meshist� 
    static TMesh *clone(TMesh *original);

    //merge�� kaksi meshi� uuteen meshiin
    static TMesh *merge(TMesh *mesh1, TMesh *mesh2);

    //merge�� toisen meshin t�h�n meshiin vuotamatta muistia
    void merge(TMesh *another);

    //aloittaa meshin rakentamisen
    void startCreation();
    //lis�� verteksin startCreationin j�lkeen
    void insertVertex(TVertex &vertex);
    //lis�� facen startCreationin j�lkeen
    void insertFace(TFace &face);
    //lopettaa luontimoodin
    void endCreation();

    //linkitt�� tason faceihin (ei toimi kaikilla objekteilla ollenkaan)
    void makeFaces(int xres, int yres); 

    //siirt�� kaikkia verteksej� move-verran
    void translate(Vector3 &move); 
    //transformoi modessa m��ritellyt asiat matriisilla
    void transform(Matrix &mat, int mode);
    //skaalaa kaikkien verteksien pituuden v�lille 0..max
    void scale(float max);
    //keskitt�� mallin (massakeskipiste origoon)
    void center();
    //laskee face-ja verteksinormaalit
    //Huom! Jos kappale ei ole konveksi tai hyvin m��ritelty, voi tulla ongelmia
    void calculateNormals();
    
    //laskee edgedatan
    void calculateEdges();
    
    //k��nt�� kaikki normaalit toisin p�in (purkkaratkaisu clockwise/counterclockwise-ongelmaan)
    void flipNormals();
    //poistaa tuplaverteksit (epsilon-tarkkuudella)
    void removeDuplicateVertices(float epsilon);
    //tulostaa debug-infoa lokiin
    void printDebug();

    //piirt�� normaalit, verteksinormaalit valkoisella ja facenormaalit punaisella
    //huom! tuhoaa openGL-staten
    void drawNormals(float scale = 0.5f);

    //piirt�� verteksibufferin
	void renderVBO(int mode = MESH_VERTEX_BIT | MESH_TEXTURE_BIT | MESH_NORMAL_BIT);
    //deletoi verteksibufferin
	void freeVBO();
    //luo verteksibufferin
	void createVBO(int mode = MESH_VERTEX_BIT | MESH_TEXTURE_BIT | MESH_NORMAL_BIT);

    //setterit
    void setFaceCount(int facecount) { this->facecount = facecount; };
    void setVertexCount(int vertexcount) { this->vertexcount = vertexcount; };
    void setFaces(TFace *f) { this->f = f; };
    void setVertices(TVertex *v) { this->v = v; };

    //getterit
    TFace *getFaces() { return this->f; };
    TVertex *getVertices() { return this->v; };
    TEdge *getEdges() { return this->e; };

    int getVertexCount() { return this->vertexcount;}
    int getFaceCount() { return this->facecount; }
    int getEdgeCount() { return this->edgecount; }

private:
    //data
    int edgecount;
    int facecount;
    int vertexcount;

    std::vector<TVertex> insertedVertices;
    std::vector<TFace> insertedFaces;

    TEdge *e;
    TVertex *v;
    TFace *f;

    // VBO
    bool VBOinit;
    int VBOmode;
    GLuint vertBufferID;
    GLuint texBufferID;
    GLuint normalBufferID;
    GLuint colorBufferID;

};






#endif