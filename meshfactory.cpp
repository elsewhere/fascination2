#include "meshfactory.hpp"


TMesh* TMeshFactory::importT3D(char *name)
{
    int i = 0;

    TMesh *temp = new TMesh();
    T3D *o = dmsGetObject(name);

    //osoittimet kamoihin kappaleesta
    int facecount = o->getFaceCount();
    int vertexcount = o->getVertexCount();
    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);

    T3DVertex *vert = o->getVertexArray();
    T3DFace *faces = o->getFaceArray();

    TVertex *v = new TVertex[vertexcount];
    TFace *f = new TFace[facecount];

    //konvertoidaan eri formaateista toisiin
    for (i = 0; i < facecount; i++)
    {
        f[i].a = faces[i].a;
        f[i].b = faces[i].b;
        f[i].c = faces[i].c;
        f[i].normal = Vector3(0, 0, 0);
    }
    for (i = 0; i < vertexcount; i++)
    {
        Vector vertex = vert[i].position;
        v[i].position = Vector3(vertex.x, vertex.y, vertex.z);
        v[i].uv.u = vert[i].u;
        v[i].uv.v = vert[i].v;
        v[i].normal = Vector3(0, 0, 0);
    }

    temp->setVertices(v);
    temp->setFaces(f);
    temp->calculateNormals();

    return temp;
}



TMesh *TMeshFactory::createSphere(float radius, int xres, int yres, float texturescale)
{
    TMesh *temp = new TMesh();
    
	int vertexcount = xres * yres;
	int facecount = xres * yres * 2;

    TVertex *v = new TVertex[vertexcount];
	TFace *f = new TFace[facecount];

	int x, y;

	for (y=0;y<yres;y++)
	{
		for (x=0;x<xres;x++)
		{
			const float xkohta = x / (float)(xres-1);
			const float ykohta = y / (float)(yres-1);

            Vector3 pos = Mathematics::sphereToCartesian(1, ykohta*3.141592f, xkohta*2*3.141592f);
			v[x+y*xres].position = pos * radius;
            v[x+y*xres].normal = pos;
			v[x+y*xres].uv.u = xkohta*texturescale;
			v[x+y*xres].uv.v = ykohta*texturescale;
		}
	}

    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);
    temp->setFaces(f);
    temp->setVertices(v);

    temp->makeFaces(xres, yres);
    temp->calculateNormals();
    return temp;
}

TMesh *TMeshFactory::createTorus(float radius1, float radius2, int xres, int yres, float texturescale)
{
    int x, y;

    TMesh *temp = new TMesh();

	int vertexcount = xres * yres;
	int facecount = xres * yres * 2;

    TVertex *v = new TVertex[vertexcount];
	TFace *f = new TFace[facecount];

    //ulompi kehä
    for (y = 0 ; y < yres; y++)
    {
        float ykohta = y / (float)yres;
        float yangle = ykohta*2*3.141592f;

        //torus tulee xz-tasoon
        Matrix rotation;
        rotation.makeRotation(0, yangle, 0);

        Vector3 centerpoint = Vector3(0, 0, radius1);

        //sisempi kehä
        for (x=0;x<xres;x++)
        {
            float xkohta = x / (float)xres;
            float xangle = xkohta*2*3.141592f;

            Vector3 edgepoint = Vector3(0, (float)sin(xangle), (float)cos(xangle))*radius2;
            v[x+y*xres].position = (centerpoint + edgepoint) * rotation;
            v[x+y*xres].uv.u = texturescale * y / (float)(yres-1);//xkohta;
            v[x+y*xres].uv.v = texturescale * x / (float)(xres-1);//;
        }
    }

    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);
    temp->setFaces(f);
    temp->setVertices(v);

    temp->makeFaces(xres, yres);
    temp->calculateNormals();
    return temp;
}

//luo kuution
TMesh *TMeshFactory::createCube(float size, int xres, int yres)
{
    TMesh *temp = new TMesh();
    //jokaiselle tahkolle xres*yres verteksiä

    int vertexcount = xres * yres * 6;
    int facecount = vertexcount * 2;
    TVertex *v = new TVertex[vertexcount];
    TFace *f = new TFace[facecount];
    
    for (int i = 0; i < yres; i++)
    {
        for (int j = 0; j < xres; j++)
        {

        }
    }
    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);
    temp->setFaces(f);
    temp->setVertices(v);
    temp->calculateNormals();

    return temp;
}

