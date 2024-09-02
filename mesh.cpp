/*
    Pelit ja vehkeet

*/

#include "mesh.hpp"

TMesh::TMesh()
{
    this->clear();
}


TMesh::TMesh(int vertexcount, int facecount)
{
    this->clear();
    this->facecount = facecount;
    this->vertexcount = vertexcount;
    
    this->f = new TFace[this->facecount];
    this->v = new TVertex[this->vertexcount];
}


TMesh::~TMesh()
{
    this->destroy();
}

void TMesh::clear()
{
    this->f = 0;
    this->v = 0;
    this->e = 0;
    this->facecount = 0;
    this->vertexcount = 0;
    this->edgecount = 0;

    this->vertBufferID = 0;
	this->texBufferID = 0;
	this->normalBufferID = 0;
	this->colorBufferID = 0;
    this->VBOinit = false;
    this->VBOmode = 0;

}
void TMesh::destroy()
{
    if (this->f != 0)
    {
        delete [] this->f;
    }
    if (this->v != 0)
    {
        delete [] this->v;
    }
    if (this->e != 0)
    {
        delete [] this->e;

    }

    this->clear();
    this->freeVBO();
}

void TMesh::startCreation()
{
    this->destroy(); //putsataan vanhat 
}

void TMesh::insertVertex(TVertex &vertex)
{
    this->insertedVertices.push_back(vertex);
}

void TMesh::insertFace(TFace &face)
{
    this->insertedFaces.push_back(face);

}
void TMesh::endCreation()
{
    this->vertexcount = this->insertedVertices.size();
    this->facecount = this->insertedFaces.size();

    this->v = new TVertex[this->vertexcount];
    this->f = new TFace[this->facecount];

    std::vector<TVertex>::const_iterator vertexiterator;
    std::vector<TFace>::const_iterator faceiterator;

    int offset = 0;
    for (vertexiterator = insertedVertices.begin(); vertexiterator != insertedVertices.end(); vertexiterator++)
    {
        TVertex vertex = *vertexiterator;
        this->v[offset++] = vertex;
    }
    offset = 0;
    for (faceiterator = insertedFaces.begin(); faceiterator != insertedFaces.end(); faceiterator++)
    {
        TFace face = *faceiterator;
        this->f[offset++] = face;
    }

    this->calculateNormals();
    this->insertedFaces.clear();
    this->insertedVertices.clear();
}


TMesh *TMesh::clone(TMesh *original)
{
    int i = 0;
    TMesh *temp = new TMesh();
    int facecount = original->getFaceCount();
    int vertexcount = original->getVertexCount();

    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);

    TVertex *v = new TVertex[vertexcount];
    TFace *f = new TFace[facecount];

    TVertex *ov = original->getVertices();
    TFace *of = original->getFaces();
    for (i = 0; i < vertexcount; i++)
    {
        v[i] = ov[i];
    }
    for (i = 0; i < facecount; i++)
    {
        f[i] = of[i];
    }

    temp->setFaces(f);
    temp->setVertices(v);

    return temp;
}

TMesh *TMesh::merge(TMesh *mesh1, TMesh *mesh2)
{
    int i = 0;
    TMesh *temp = new TMesh();

    //tiedot ulos mesheistä
    int vertexcount1 = mesh1->getVertexCount();
    int facecount1 = mesh1->getFaceCount();

    int vertexcount2 = mesh2->getVertexCount();
    int facecount2 = mesh2->getFaceCount();

    int facecount = facecount1 + facecount2;
    int vertexcount = vertexcount1 + vertexcount2;

    TFace *faces1 = mesh1->getFaces();
    TVertex *vertices1 = mesh1->getVertices();
    TFace *faces2 = mesh2->getFaces();
    TVertex *vertices2 = mesh2->getVertices();

    TFace *f = new TFace[facecount];
    TVertex *v = new TVertex[vertexcount];

    int faceoffset = 0;
    int vertexoffset = 0;

    //ensin kopioidaan mesh1 uuteen meshiin
    for (i = 0; i < facecount1; i++)
    {
        f[faceoffset++] = faces1[i];
    }
    for (i = 0; i < vertexcount1; i++)
    {
        v[vertexoffset++] = vertices1[i];
    }

    //sitten kopioidaan perään mesh2
    for (i = 0; i < facecount2; i++)
    {
        TFace face = faces2[i];
        //fiksataan indeksit
        face.a += vertexcount1;
        face.b += vertexcount1;
        face.c += vertexcount1;
        f[faceoffset++] = face;
    }
    for (i = 0; i < vertexcount2; i++)
    {
        v[vertexoffset++] = vertices2[i];
    }

    temp->setFaceCount(facecount);
    temp->setVertexCount(vertexcount);
    temp->setFaces(f);
    temp->setVertices(v);

    return temp;

}

void TMesh::merge(TMesh *another)
{
    //uudessa meshissä tämä + toinen
    //referenssi temppiin menee pinossa, joten sen kuoltua jäljelle jäävät ainoastaan verteksit ja facet heapissa, joihin
    //tämä mesh osoittaa metodin jälkeen
    TMesh *temp = TMesh::merge(this, another);

    //tuhotaan tämä
    this->destroy();

    this->setFaceCount(temp->getFaceCount());
    this->setVertexCount(temp->getVertexCount());
    this->setFaces(temp->getFaces());
    this->setVertices(temp->getVertices());
}

void TMesh::calculateNormals()
{
    int i;

    for (i = 0; i < this->facecount; i++)
    {
        TVertex &v1 = this->v[this->f[i].a];
        TVertex &v2 = this->v[this->f[i].b];
        TVertex &v3 = this->v[this->f[i].c];

        this->f[i].normal = (v3.position - v1.position).crossProduct(v3.position - v2.position).normalize();
    }
    
    for (i = 0; i < this->vertexcount; i++)
    {
        for (int j = 0; j < this->facecount; j++)
        {
            TFace &f = this->f[j];
            if (f.a == i || f.b == i || f.c == i)
            {
                this->v[i].normal += this->f[j].normal;
            }
        }
        this->v[i].normal.normalize();
    }
}

void TMesh::calculateEdges()
{
    int i;

    // Allocate enough space to hold all edges
   TEdge *edgeArray;
   edgeArray = new TEdge[this->facecount * 3];

   int edgeCount = 0;

   // First pass: find edges
   for (i = 0; i < this->facecount; i++)
   {
      int i1 = this->f[i].a;
      int i2 = this->f[i].b;
      int i3 = this->f[i].c;

      if (i1 < i2)
      {
         edgeArray[edgeCount].a = i1;
         edgeArray[edgeCount].b = i2;
         edgeArray[edgeCount].face1 = i;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }

      if (i2 < i3)
      {
         edgeArray[edgeCount].a = i2;
         edgeArray[edgeCount].b = i3;
         edgeArray[edgeCount].face1 = i;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }

      if (i3 < i1)
      {
         edgeArray[edgeCount].a = i3;
         edgeArray[edgeCount].b = i1;
         edgeArray[edgeCount].face1 = i;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }
   }

   // Second pass: match triangles to edges
   //triangle = this->face;
   for (i = 0; i < this->facecount; i++)
   {
      int i1 = this->f[i].a;
      int i2 = this->f[i].b;
      int i3 = this->f[i].c;

      if (i1 > i2)
      {
         //edgelist = edgeArray;
         for (int b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i2) &&
				(edgeArray[b].b == i1) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = i;
               break;
            }
         }
      }

      if (i2 > i3)
      {
         //edgelist = edgeArray;
         for (int b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i3) &&
				(edgeArray[b].b == i2) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = i;
               break;
            }
         }
      }

      if (i3 > i1)
      {
         //edgelist = edgeArray;
         for (int b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i1) &&
				(edgeArray[b].b == i3) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = i;
               break;
            }
         }
      }
   }

    this->edgecount = edgeCount;

	// copy tmpedge to this->edge
	this->e = new TEdge [this->edgecount];

	for(i = 0;  i < this->edgecount; i++) 
    {
		this->e[i] = edgeArray[i];
	}

	delete [] edgeArray;
}




void TMesh::translate(Vector3 &move)
{
    int i;
    for (i = 0; i < this->vertexcount; i++)
    {
        this->v[i].position += move;
    }
}

void TMesh::center()
{
    int i;

    Vector3 center = Vector3(0, 0, 0);

    for (i = 0; i < this->vertexcount; i++)
    {
        center += this->v[i].position;
    }
    center *= 1.0f / this->vertexcount;
    this->translate(center * -1);
}


void TMesh::transform(Matrix &mat, int mode)
{
    int i;
    if ((mode & MESH_VERTEX_BIT) != 0)
    {
        for (i = 0; i < this->vertexcount; i++)
        {
            this->v[i].position *= mat;
        }
    }

    if ((mode & MESH_NORMAL_BIT) != 0)
    {
        for (i = 0; i < this->vertexcount; i++)
        {
            this->v[i].normal *= mat;
        }
    }

}

void TMesh::scale(float max)
{
    int i = 0;
    //normalisointi
    float longest = 0.0f;
    for (i = 0; i < this->vertexcount; i++)
    {
        float l = this->v[i].position.length();
        if (l > longest)
        {
            longest = l;
        }
    }

    for (i = 0; i < this->vertexcount; i++)
    {
        this->v[i].position *= max / longest;
    }
}

void TMesh::removeDuplicateVertices(float epsilon)
{
    int i;

// TODO: joku hieno taulukkorakennelma
//    std::vector<TVertex> tempvertices;
//    std::vector<TVertex>::iterator vertexiterator;


    for (i = 0; i < this->facecount; i++)
    {
        TFace &face = this->f[i];

        TVertex &base1 = this->v[face.a];
        TVertex &base2 = this->v[face.b];
        TVertex &base3 = this->v[face.c];

        for (int j = 0; j < this->vertexcount; j++)
        {
            if (j != face.a && j != face.b && j != face.c)
            {
                TVertex &test = this->v[j];
                if (fabsf(base1.position.x - test.position.x) < epsilon &&
                    fabsf(base1.position.y - test.position.y) < epsilon &&
                    fabsf(base1.position.z - test.position.z) < epsilon)
                {
                    //base1 == test
                    //vaihdetaan referenssi facelistassa tähän verteksiin
                    face.a = j;
                }
                if (fabsf(base2.position.x - test.position.x) < epsilon &&
                    fabsf(base2.position.y - test.position.y) < epsilon &&
                    fabsf(base2.position.z - test.position.z) < epsilon)
                {
                    //base2 == test
                    //vaihdetaan referenssi facelistassa tähän verteksiin
                    face.b = j;
                }
                if (fabsf(base3.position.x - test.position.x) < epsilon &&
                    fabsf(base3.position.y - test.position.y) < epsilon &&
                    fabsf(base3.position.z - test.position.z) < epsilon)
                {
                    //base3 == test
                    //vaihdetaan referenssi facelistassa tähän verteksiin
                    face.c = j;
                }
            }
        }
    }

    this->calculateNormals();
}

void TMesh::makeFaces(int xres, int yres)
{
    int x, y;
	int index = 0;
	for (y = 0; y < yres; y++)
	{
		for (x = 0; x < xres; x++)
		{
			this->f[index].a = (x%xres)+(y%yres)*xres;
			this->f[index].b = ((x+1)%xres)+(y%yres)*xres;
			this->f[index].c = ((x+1)%xres)+((y+1)%yres)*xres;
			index++;
			this->f[index].a = (x%xres)+(y%yres)*xres;
			this->f[index].b = ((x+1)%xres)+((y+1)%yres)*xres;
			this->f[index].c = ((x)%xres)+((y+1)%yres)*xres;
			index++;
		}
	}
}

void TMesh::drawNormals(float scale)
{
    int i = 0;
    glColor4f(1,1,1,1);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_LINES);
    for (i = 0; i < this->vertexcount; i++)
    {
        TVertex &vertex = v[i];
        glColor4f(1,1,1,1);
        glVertex3fv((float *)&(vertex.position));
        glColor4f(1,1,1,0.4f);
        glVertex3fv((float *)&(vertex.position + vertex.normal*scale));
    }
    for (i = 0; i < this->facecount; i++)
    {
        TFace &face = f[i];
        glColor4f(1,0,0,1);

        Vector3 keskipiste = (this->v[face.a].position + 
                              this->v[face.b].position + 
                              this->v[face.c].position ) * 0.33333f;

        glVertex3fv((float *)&(keskipiste));
        glColor4f(1,1,1,0.4f);
        glVertex3fv((float *)&(keskipiste + face.normal*scale));
    }
    glEnd();
}

void TMesh::flipNormals()
{
    int i = 0;

    for (i = 0; i < this->vertexcount; i++)
    {
        this->v[i].normal *= -1;
    }
    for (i = 0; i < this->facecount; i++)
    {
        this->f[i].normal *= -1;
    }
}

void TMesh::renderVBO(int mode)
{
	if(this->VBOinit==false)
	{
		dmsMsg("TMesh::renderVBO() - VBO used, but wasn't initialised!\n");
		return; 
	}
		

    //verteksit aina
	glEnableClientState(GL_VERTEX_ARRAY);

    //muilla tsekataan bitti
    if ((mode & MESH_TEXTURE_BIT) != 0)
    {
	    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->texBufferID );
        glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);			// tekstuurikoordinaatit
        if ((this->VBOmode & MESH_TEXTURE_BIT) != 0)
        {
            dmsMsg("trying to render a mesh VBO textures without texture buffer initialized\n");
        }
    }
    else
    {
	    glDisableClientState(GL_TEXTURE_COORD_ARRAY);		
    }

    if ((mode & MESH_NORMAL_BIT) != 0)
    {
	    glEnableClientState(GL_NORMAL_ARRAY);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->normalBufferID );
	    glNormalPointer(GL_FLOAT, 0, (char *)NULL);			// normaalit
        if ((this->VBOmode & MESH_NORMAL_BIT) != 0)
        {
            dmsMsg("trying to render a mesh VBO normals without normal buffer initialized\n");
        }
    }
    else
    {
	    glDisableClientState(GL_NORMAL_ARRAY);
    }

    if ((mode & MESH_COLOR_BIT) != 0)
    {
	    glEnableClientState(GL_COLOR_ARRAY);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->colorBufferID);
        glColorPointer(3, GL_FLOAT, 0, (char *)NULL);			// värit
        if ((this->VBOmode & MESH_COLOR_BIT) != 0)
        {
            dmsMsg("trying to render a mesh VBO colors without color buffer initialized\n");
        }
    }
    else
    {
	    glDisableClientState(GL_COLOR_ARRAY);
    }

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->vertBufferID );
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);			// verteksit


	glDrawArrays(GL_TRIANGLES, 0, this->facecount*3);			// draw

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);				
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);				
    glDisableClientState(GL_COLOR_ARRAY);				
}	

void TMesh::createVBO(int mode) 
{
	this->VBOinit = true;
    this->VBOmode = mode;

	const int faces = this->facecount;
	const int verts = this->facecount * 3;

    Vector3 *ver = new Vector3[verts];
	Vector3 *nor = new Vector3[verts];	
	Vector3 *col = new Vector3[verts];	
	TTexCoord *tex = new TTexCoord[verts];

	int face = 0;

    //toimiiko tämä ihan varmasti kaikissa tilanteissa? 
	for (int i = 0 ; i < verts ; i += 3)
	{
        ver[i] = this->v[this->f[face].a].position;
        nor[i] = this->v[this->f[face].a].normal;
        tex[i] = this->v[this->f[face].a].uv;
        col[i] = this->f[face].color;

        ver[i+1] = this->v[this->f[face].b].position;
        nor[i+1] = this->v[this->f[face].b].normal;
        tex[i+1] = this->v[this->f[face].b].uv;
        col[i+1] = this->f[face].color;

        ver[i+2] = this->v[this->f[face].c].position;
        nor[i+2] = this->v[this->f[face].c].normal;
        tex[i+2] = this->v[this->f[face].c].uv;
        col[i+2] = this->f[face].color;

		face++;
	}

	// Generate And Bind The Vertex Buffer

    if ((mode & MESH_VERTEX_BIT) != 0)
    {
        glGenBuffersARB( 1, &this->vertBufferID);	
	    glBindBufferARB( GL_ARRAY_BUFFER_ARB, this->vertBufferID);
	    glBufferDataARB( GL_ARRAY_BUFFER_ARB, verts*3*sizeof(float), ver, GL_STATIC_DRAW_ARB );
	    glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
    }

	// Generate And Bind The Texture Coordinate Buffer
    if ((mode & MESH_TEXTURE_BIT) != 0)
    {
	    glGenBuffersARB( 1, &this->texBufferID );					
	    glBindBufferARB( GL_ARRAY_BUFFER_ARB, this->texBufferID);	
	    glBufferDataARB( GL_ARRAY_BUFFER_ARB, verts*2*sizeof(float), tex, GL_STATIC_DRAW_ARB );
    }

	// Generate And Bind The Normal Buffer
    if ((mode & MESH_NORMAL_BIT) != 0)
    {
	    glGenBuffersARB( 1, &this->normalBufferID );					
	    glBindBufferARB( GL_ARRAY_BUFFER_ARB, this->normalBufferID);	
	    glBufferDataARB( GL_ARRAY_BUFFER_ARB, verts*3*sizeof(float), nor, GL_STATIC_DRAW_ARB );
    }

    if ((mode & MESH_COLOR_BIT) != 0)
    {
        glGenBuffersARB( 1, &this->colorBufferID);					
	    glBindBufferARB( GL_ARRAY_BUFFER_ARB, this->colorBufferID);	
	    glBufferDataARB( GL_ARRAY_BUFFER_ARB, verts*3*sizeof(float), col, GL_STATIC_DRAW_ARB );
    }

//	glBindBufferARB(GL_ARRAY_BUFFER, 0);

	delete [] ver; 
	ver = NULL;
	delete [] tex; 
	tex = NULL;
	delete [] nor;
	nor = NULL;
	delete [] col;
	col = NULL;
	
}

void TMesh::freeVBO()
{
    //ei vapauteta mitään jos ei ole initoitu
    //muuten saattaa teoriassa hajota joku bufferi jossain, jos muistissa on roskaa
    if (this->VBOinit)
    {
	    glBindBufferARB(GL_ARRAY_BUFFER, 0);
	    glDeleteBuffersARB(1, &this->vertBufferID);
	    glDeleteBuffersARB(1, &this->texBufferID);
	    glDeleteBuffersARB(1, &this->normalBufferID);
	    glDeleteBuffersARB(1, &this->colorBufferID);
	    
	    this->VBOinit = false;

	    this->texBufferID = -1;	
	    this->vertBufferID = -1;
    }
}


void TMesh::printDebug()
{
    int i = 0;
    dmsMsg("objektin debuggi alkaa\n");
    dmsMsg("----------------------\n");
    dmsMsg("facecount = %d\n", this->facecount);
    dmsMsg("vertexcount = %d\n", this->vertexcount);

    dmsMsg("Tulostetaan vertex-data\n");
    for (i = 0; i < this->vertexcount; i++)
    {
        dmsMsg("*** vertex %d\n", i);
        dmsMsg("    paikka = %f %f %f\n", this->v[i].position.x, this->v[i].position.y, this->v[i].position.z);
        dmsMsg("    normaali = %f %f %f\n", this->v[i].normal.x, this->v[i].normal.y, this->v[i].normal.z);
        dmsMsg("    uv = %f %f \n\n", this->v[i].uv.u, this->v[i].uv.v);

    }

    dmsMsg("Tulostetaan face-data\n");
    for (i = 0; i < this->facecount; i++)
    {
        dmsMsg("*** face %d - a = %d, b = %d, c = %d\n", i, this->f[i].a, this->f[i].b, this->f[i].c);
        dmsMsg("    facenormaali = %f %f %f\n", this->f[i].normal.x, this->f[i].normal.y, this->f[i].normal.z);
        dmsMsg("    vertexnormaali1 = %f %f %f\n", this->v[this->f[i].a].normal.x, this->v[this->f[i].a].normal.y, 
                                                 this->v[this->f[i].a].normal.z);
        dmsMsg("    vertexnormaali2 = %f %f %f\n", this->v[this->f[i].b].normal.x, this->v[this->f[i].b].normal.y, 
                                                 this->v[this->f[i].b].normal.z);
        dmsMsg("    vertexnormaali3 = %f %f %f\n\n", this->v[this->f[i].c].normal.x, this->v[this->f[i].c].normal.y, 
                                                 this->v[this->f[i].c].normal.z);
    }
}


TTexCoord TTexCoord::operator + (TTexCoord const &uv)
{
    TTexCoord t;
    t.u = this->u + uv.u;
    t.v = this->v + uv.v;
	return t;
}

TTexCoord TTexCoord::operator - (TTexCoord const &uv)
{
    TTexCoord t;
    t.u = this->u - uv.u;
    t.v = this->v -  uv.v;
	return t;
}

TTexCoord TTexCoord::operator * (float const &f)
{
    float tu = this->u * f;
    float tv = this->v * f;
    return TTexCoord(tu, tv);

}
TTexCoord TTexCoord::operator *= (float const &f)
{
    this->u *= f;
    this->v *= f;
    return TTexCoord(this->u, this->v);

}
    