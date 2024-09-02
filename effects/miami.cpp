#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Miami.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Miami::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.1f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

    filter.init(true);
	renderScene(pos, alpha);
    filter.glow(7, 0.01f, 0.01f, 0.93f, -1.0f, 1.0f);
}

void Miami::shiftLandscape()
{
    int i = 0;
    for (i = 0; i < this->segmentcount - 1; i++)
    {
        for (int j = 0; j < this->piececount; j++)
        {
            this->segments[i]->colors[j] = this->segments[i + 1]->colors[j];
            this->segments[i]->vertices[j].y = this->segments[i + 1]->vertices[j].y;
        }
        this->segments[i]->number = this->segments[i + 1]->number;
        this->segments[i]->keilacolor = this->segments[i + 1]->keilacolor;
        this->segments[i]->tiecolor = this->segments[i + 1]->tiecolor;
    }
    int modifiedsegment = this->segmentcount - 1;

    LandSegment *s = this->segments[modifiedsegment];
    s->set(modifiedsegment, this->segmentwidth, this->segmentlength);
    s->setNumber(this->piececount + this->shifts);

    float buf[256];

    dmsGetSpectrum(buf, 256);
    buf[255] = 0.0f;
    buf[254] = 0.0f;

    for (i = 0; i < this->piececount / 2; i++)
    {
        float t = i / (float)(this->piececount / 2);
        float val = sqrtf(buf[i]) * 15.0f * (1-t);

        if (i > this->piececount * 20 / 100)
            val = 0.0f;

        this->soundbuffer[i] = val;
        this->soundbuffer[this->piececount - 1 - i] = val;
    }
    s->setHeights(this->soundbuffer);
}

void Miami::drawKeila(float dist, float z, Vector3 &color, float alpha)
{
    const float keila = 3.33f;
    const float korkeus = 28.0f;
    float f = alpha * 0.4f;

    float s = 1.4f;

    Vector3 d1 = Vector(0, 0, 0);
    Vector3 d2 = Vector(-s, 0, 0);
    Vector3 d3 = Vector(-s, 0, -s);
    Vector3 d4 = Vector(0, 0, -s);

    Vector3 base = Vector(-dist, 0, z);

    Vector3 v1 = base + d1;
    Vector3 v2 = base + d2;
    Vector3 v3 = base + d3;
    Vector3 v4 = base + d4;

    Vector3 v5 = base + d1 * keila; 
    Vector3 v6 = base + d2 * keila; 
    Vector3 v7 = base + d3 * keila; 
    Vector3 v8 = base + d4 * keila; 

    v5.y = korkeus;
    v6.y = korkeus;
    v7.y = korkeus;
    v8.y = korkeus;

    glColor4f(color.x, color.y, color.z, f);
    glVertex3fv((float *)&v1);
    glVertex3fv((float *)&v2);
    glColor4f(color.x, color.y, color.z, 0);
    glVertex3fv((float *)&v6);
    glVertex3fv((float *)&v5);

    glColor4f(color.x, color.y, color.z, f);
    glVertex3fv((float *)&v2);
    glVertex3fv((float *)&v3);
    glColor4f(color.x, color.y, color.z, 0);
    glVertex3fv((float *)&v7);
    glVertex3fv((float *)&v6);

    glColor4f(color.x, color.y, color.z, f );
    glVertex3fv((float *)&v3);
    glVertex3fv((float *)&v4);
    glColor4f(color.x, color.y, color.z, 0);
    glVertex3fv((float *)&v8);
    glVertex3fv((float *)&v7);

    glColor4f(color.x, color.y, color.z, f );
    glVertex3fv((float *)&v4);
    glVertex3fv((float *)&v1);
    glColor4f(color.x, color.y, color.z, 0);
    glVertex3fv((float *)&v5);
    glVertex3fv((float *)&v8);
}

void Miami::drawTienPala(float x, float z, float syvyys, float leveys)
{
    const float korkeus = 1.0f;
    Vector v1 = Vector3(x, korkeus, z);
    Vector v2 = Vector3(x + leveys, korkeus, z);
    Vector v3 = Vector3(x + leveys, korkeus, z + syvyys);
    Vector v4 = Vector3(x, korkeus, z + syvyys);

    glVertex3fv((float *)&v1);
    glVertex3fv((float *)&v2);
    glVertex3fv((float *)&v3);
    glVertex3fv((float *)&v4);


}

void Miami::drawLandscape(float pos, float alpha)
{
    int i = 0;

    glDisable(GL_TEXTURE_2D);

    float keilat = alpha * Mathematics::calcPosFloat(pos, 0.1f, 0.16f);
    float keilaalpha = sinf(keilat*3.141592f*0.5f);

    float valot = alpha * Mathematics::calcPosFloat(pos, 0.2f, 0.24f);
    float valoalpha = sinf(keilat*3.141592f*0.5f) * (0.8f + 0.2f*cosf(pos*41));

    if (keilat > 0.001f && keilat < 0.999f)
    {
        if (Mathematics::randFloat() > keilat)
        {
            keilaalpha *= 0.1f;
        }
    }

    if (valot > 0.001f && valot < 0.999f)
    {
        if (Mathematics::randFloat() > valot)
        {
            valoalpha *= 0.1f;
        }
    }

    float sync = beat->getValue();

    for (i = 0; i < this->segmentcount - 1; i++)
    {
        LandSegment *s1 = this->segments[i];
        LandSegment *s2 = this->segments[i+1];
        float z = s1->vertices[0].z;

        //itse maasto
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j < this->piececount; j++)
        {
            const float f = (s2->fog * 0.6f * (1+s1->vertices[j].y*0.4f)) * alpha;
            Vector3 c1 = s1->colors[j] * f;
            Vector3 c2 = s2->colors[j] * f;

            glColor3fv((float *)&c1);
            glVertex3fv((float *)&s1->vertices[j]);
            glColor3fv((float *)&c2);
            glVertex3fv((float *)&s2->vertices[j]);
        }
        glEnd();

        //keilat
        if (!(s1->number % 17))
        {
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBegin(GL_QUADS);
            float dist = 18.0f;
            drawKeila(-dist, z, s1->keilacolor * s1->fog, keilaalpha);
            drawKeila( dist, z, s1->keilacolor * s1->fog, keilaalpha);
            glEnd();
        }


        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        //tienviivat
        const float tienviivamod = 0.4f * alpha * s1->fog;

        if (!(s1->number % 5))
        {
            float d = 4.5f;
            float leveys = 0.3f;
            float syvyys = 4.5f;

            glBegin(GL_QUADS);
            glColor4f(s1->tiecolor.x, s1->tiecolor.y, s1->tiecolor.z,tienviivamod); 
            drawTienPala(d, z, syvyys, leveys);
            drawTienPala(-d, z, syvyys, -leveys);
            glEnd();
        }
        if (!(s1->number % 7))
        {
            float d = -0.2f;
            float leveys = 0.4f;
            float syvyys = 3 * this->segmentlength;

            glBegin(GL_QUADS);
            glColor4f(s1->tiecolor.x, s1->tiecolor.y, s1->tiecolor.z, tienviivamod * 0.87f); 
            drawTienPala(d, z, syvyys, leveys);
            glEnd();
        }
        //laskeutumisvalot
        if (valot > 0.00001f)
        {
            if (!(s1->number % 2))
            {
                float d = 5.5f;
                float leveys = 0.4f;
                float syvyys = 0.4f;

                float a = valoalpha * 2.7f * s1->fog * (0.5f+0.5f*sinf(pos*141 + s1->number * 0.15f)) * (0.7f+0.3f*sync);

                Vector3 color = Vector3(0.5f, 0.7f, 0.9f);
                if (!(s1->number % 16))
                {
//                    color = Vector3(0.9f, 0.4f, 0.8f);
                    a *= 3.0f;
                }
                glBegin(GL_QUADS);
                glColor4f(color.x, color.y, color.z, a); 
                drawTienPala(d, z, syvyys, leveys);
                drawTienPala(-d, z, syvyys, -leveys);
                glEnd();
            }
        }
    }

    //reunat
    Vector v1 = this->segments[0]->vertices[0];
    Vector v2 = this->segments[this->segmentcount - 1]->vertices[0];
    Vector v3 = this->segments[0]->vertices[this->piececount - 1];
    Vector v4 = this->segments[this->segmentcount - 1]->vertices[this->piececount - 1];

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    float peitto = 200;
    glVertex3f(v1.x, 0, v1.z);
    glVertex3f(v2.x, 0, v2.z);
    glVertex3f(v2.x - peitto, 0, v2.z);
    glVertex3f(v1.x - peitto, 0, v1.z);

    glVertex3f(v3.x, 0, v3.z);
    glVertex3f(v4.x, 0, v4.z);
    glVertex3f(v4.x + peitto, 0, v4.z);
    glVertex3f(v3.x + peitto, 0, v3.z);
    glEnd();
}

const int hori = 4;

static Vector horizoncolors[] = 
{
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.3f, 0.8f, 1.0f),
    Vector3(0.6f, 0.5f, 0.9f),
    Vector3(0.6f, 0.2f, 0.9f),
    Vector3(0, 0, 0),
};

static float horizonh[] = 
{
    -5,
    0,
    15,
    25,
    80,
};

void Miami::drawHorizon(float pos, float alpha)
{
    int i = 0;
    const float width = 100.0f;
    const float height = 40.0f;
    const float z = 60.0f;

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);

    const float bright = 0.12f * Mathematics::calcSaturate(pos, 0, 1, 4);
//    Vector3 color1 = Vector3(0.7f, 0.2f, 0.9f) * bright * ;
//    Vector3 color2 = Vector3(0, 0, 0) * bright;

    glBegin(GL_QUADS);
    for (i = 0; i < hori; i++)
    {
        Vector3 color1 = horizoncolors[i] * bright;
        Vector3 color2 = horizoncolors[i + 1] * bright;

        float h1 = horizonh[i];
        float h2 = horizonh[i + 1];

        glColor3fv((float *)&color1);
        glVertex3f(-width, h1, z);
        glVertex3f( width, h1, z);
        glColor3fv((float *)&color2);
        glVertex3f( width, h2, z);
        glVertex3f(-width, h2, z);
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,1);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("cityscape_1024.png")->getID());
    glBegin(GL_QUADS);
    const float vaaka = 1024.0f;
    const float pysty = 128.0f;

    const float scalefactor = 0.35f;

    const float paskanpoisto = 0.01f;

    const float z2 = 600.0f;
    glTexCoord2f(0, 1-paskanpoisto);
    glVertex3f(-vaaka * scalefactor, 0, z2);
    glTexCoord2f(1, 1-paskanpoisto);
    glVertex3f( vaaka * scalefactor, 0, z2);
    glTexCoord2f(1, paskanpoisto);
    glVertex3f( vaaka * scalefactor, pysty * scalefactor, z2);
    glTexCoord2f(0, paskanpoisto);
    glVertex3f(-vaaka * scalefactor, pysty * scalefactor, z2);
    glEnd();

    glDepthMask(1);
}



const int CREDITSLENGTH = 21;

char *creditstext[] = 
{
    " ",
    "WELCOME TO THE",
    "TRACTION AND",
    "BRAINSTORM",
    "AIRLINES FLIGHT",
    "INTO THE NEON RAIN",
    "  ",
    "YOUR PILOTS",
    "ON THIS FLIGHT ARE",
    "PREACHER",
    "NAPSA",
    "BUZZER",
    "FACET",
    "CRITIKILL",
    "AND",
    "THE PRIDE",
    " ",
    "WE THANK YOU FOR",
    "FLYING WITH US",
    "AND WISH YOU A",
    "PLEASANT JOURNEY",
    " ",
    " ",
};





void Miami::renderScene(float pos, float alpha)
{
    int i = 0;
    this->timer->update();
    while (this->timer->stepsLeft())
    {
        const float speed = 0.75f + 0.4f*sinf(Mathematics::calcPosFloat(pos, 0.73f, 0.87f)*0.5f*3.141592f);
        this->cameramovement += speed; //camera speed

        if (this->cameramovement >= this->segmentlength)
        {
            this->cameramovement -= this->segmentlength;

            shifts++;
            //move segments
            shiftLandscape();
        }

        this->timer->endStep();
    }

    Vector3 takeoff = Vector(0, powf(sinf(Mathematics::calcPosFloat(pos, 0.80f, 1.00f)*3.141592f*0.5f), 3.0f), 0);

    Vector3 basecam = Vector3(0*(float)cosf(pos*36), 4.5f, 0);
    Vector3 cam = basecam + Vector3(0, 0, this->cameramovement);

    Vector3 camdelta = Vector3(0.35f*cosf(pos*14)+0.2f*sinf(pos*22),
                               0.5f+0.6f*cosf(pos*18),
                               0.7f+0.4f*cosf(pos*33));

    Vector3 tgt = cam + Vector(0, 0, 6);// + camdelta * 1.5f;

//    cam += camdelta * 2.5f;
    cam += takeoff * 11;
    tgt += takeoff * 14;

    Matrix uprot;
    uprot.makeRotation(0, 0, -0.35f*powf(sinf(3.141592f * 0.5f * Mathematics::calcPosFloat(pos, 0.933f, 1.00f)), 2.0f));

    Vector3 up = Vector(0, 1, 0) * uprot;

    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z,
              tgt.x, tgt.y, tgt.z,
               up.x,  up.y,  up.z);

    //horisontti
    drawHorizon(pos, alpha);

    //maasto
    drawLandscape(pos, alpha);

    //teksti

    dmsPerspective2D(1,1);
    glLoadIdentity();

    const float ct = Mathematics::calcPosFloat(pos, 0.04f, 0.89f);
    int selected = (int)((CREDITSLENGTH + 1)* ct);
    float frac = (CREDITSLENGTH + 1) * ct - selected;

    writer->drawString(creditstext[selected], 0.1f, 0.1f, 1.0f, alpha * powf(sinf(frac * 3.141592f), 0.5f));
    dmsPerspective3D();
    glLoadIdentity();


 
 
}


LandSegment::LandSegment(int which, int count, float segmentwidth, float segmentlength)
{
    int i = 0;
    this->piececount = count;

    this->vertices = new Vector3[this->piececount]; //quad strip
    this->colors = new Vector3[this->piececount];

    this->set(which, segmentwidth, segmentlength);

}

void LandSegment::set(int which, float segmentwidth, float segmentlength)
{
    int i = 0;
    Vector3 originalcolor = getKasariColor()*1.0f;

    if (rand()%5)
    {
        originalcolor *= 0.02f;
    }

    for (i = 0; i < this->piececount; i++)
    {
        float t = i / (float)this->piececount;

        float x = (t - 0.5f) * segmentwidth;

        float z = which * segmentlength;
        float y = Mathematics::randFloat()*0.1f;//0.0f;

        this->vertices[i] = Vector3(x, y, z);

        float colorfade = 1 - sinf(t * 3.141592f);

        Vector3 color = originalcolor;

        const float limit = 0.20f;
        if (t > limit && t < 1-limit)
        {
            color = Vector3(0, 0, 0);
        }

        this->colors[i] = color * (0.9f + Mathematics::randBetween(0.0f, 0.1f)) * (0.6f+0.4f*colorfade);
        this->fog = powf(1.0f - which / 70.0f, 1.7f);
    }
    do
    {
        this->keilacolor = getKasariColor();
    } while (this->keilacolor.length() < 0.85f);

    this->keilacolor += Vector(1,1,1)*0.2f; //vaaleammaksi

    do
    {
        this->tiecolor = getKasariColor();
    } while (this->tiecolor.length() < 0.95f);
    this->tiecolor = Vector(1,1,1);
}


void LandSegment::setHeights(float *ptr)
{
    int i = 0;

    for (i = 0; i < this->piececount; i++)
    {
        this->vertices[i].y = ptr[i];
    }
}

void LandSegment::setNumber(int number)
{
    this->number = number;
}

Miami::Miami()
{
    int i = 0;
    this->timer = new FrameTimer(1000 / 60, 10);
    this->segmentcount = 130;
    this->segments = new LandSegment*[this->segmentcount];

    this->segmentlength = 2.0f;
    this->segmentwidth = 30.0f;
    this->piececount = 70;
    this->shifts = 0;

    this->soundbuffer = new float[this->piececount + 1];

    for (i = 0; i < segmentcount; i++)
    {
        this->segments[i] = new LandSegment(i, piececount, segmentwidth, segmentlength);
        this->segments[i]->setNumber(i);
    }
    this->cameramovement = 0.0f;

    //alkuun maasto
    for (int j = 0; j < segmentcount; j++)
    {
        LandSegment *s = this->segments[j];
        for (i = 0; i < this->piececount / 2; i++)
        {
            float t = i / (float)(this->piececount / 2);
            float val = sqrtf(Mathematics::randBetween(1.0f-t, 0.0f)) * 15.0f * (1-t);

            if (i > this->piececount * 20 / 100)
                val = 0.0f;

            this->soundbuffer[i] = val;
            this->soundbuffer[this->piececount - 1 - i] = val;
        }
        s->setHeights(this->soundbuffer);
    }
}

Miami::~Miami()
{
}


bool Miami::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

