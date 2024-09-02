#include <ctype.h>
#include "writer.hpp"


Writer::Writer(char *texturename)
{
    int x = 0;
    int y = 0;

    this->font = dmsGetTexture(texturename);
    this->mapheight = 5;
    this->mapwidth = 16;

    this->lettercount = this->mapheight * this->mapwidth;

    this->letters = new Letter[this->lettercount];

    //hardkoodatut dimensiot
    float dy = 1.0f / 8.0f;//this->mapheight;
    float dx = 1.0f / 16.0f; //tästä joutuu helvettiin//this->mapwidth;

    this->letterwidth = 0.05f;//dx;
    this->letterheight = this->letterwidth*640/480.0f;// * 480 / 640.0f;

    for (y = 0; y < this->mapheight; y++)
    {
        float yt = y / 8.0f;//(float)this->mapheight;
        yt += 0.029f;
        for (x = 0; x < this->mapwidth; x++)
        {
            float xt = x / 16.0f;//(float)this->mapwidth;

            Letter &l = this->letters[x + y * this->mapwidth];
            //tekstuuri ylösalaisin

            l.uv1 = LetterUV(xt,      yt);
            l.uv2 = LetterUV(xt + dx, yt);
            l.uv3 = LetterUV(xt + dx, yt + dy);
            l.uv4 = LetterUV(xt,      yt + dy);
//            dmsMsg("x = %d, y = %d, uv1 = %f %f, uv4 = %f %f\n", x, y, l.uv1.u, l.uv1.v, l.uv3.u, l.uv3.v);
        }
    }
}

#define INDEX_UPPERCASE_START 0
#define INDEX_LOWERCASE_START 32
#define INDEX_NUMBER_START 32

#define INDEX_EXCLAMATION 26
#define INDEX_QUESTIONMARK 27
#define INDEX_COLON 28
#define INDEX_DOT 29
#define INDEX_COMMA 30
#define INDEX_ASTERISK 31
#define INDEX_SLASH 68

int Writer::getIndexByChar(char c)
{
    int index = 0;
    if (c >= 'A' && c <= 'Z')
    {
        index = c - 'A' + INDEX_UPPERCASE_START;
    }
    else if (c >= 'a' && c <= 'z')
    {
        index = c - 'a' + INDEX_LOWERCASE_START;
    }
    else if (c >= '0' && c <= '9')
    {
        index = c - '0' + INDEX_NUMBER_START;
    }
    else
    {
        switch(c)
        {
            case '!':
                index = INDEX_EXCLAMATION;
                break;
            case '?':
                index = INDEX_QUESTIONMARK;
                break;
            case ':':
                index = INDEX_COLON;
                break;
            case '.':
                index = INDEX_DOT;
                break;
            case ',':
                index = INDEX_COMMA;
                break;
            case '*':
                index = INDEX_ASTERISK;
                break;

            case '/':
                index = INDEX_SLASH;
                break;


            default:
                index = 0;
                

        };
    }
    return index;
}
void Writer::drawSingleLetter(char c, float x, float y, float scale, float alpha)
{
    const float width = this->letterwidth * scale;
    const float height = this->letterheight * scale;

    const float dx = width - this->letterwidth;
    const float dy = (height - this->letterheight) * -1;

    if (c == ' ')
    {
        return;
    }


/*
    int index = c;
    index = i;
*/
    int index = this->getIndexByChar(c);
    Letter &l = this->letters[index];

    glTexCoord2fv((float *)&l.uv1);
    glVertex2f(x - dx*0.5f, y - dy *0.5f);

    glTexCoord2fv((float *)&l.uv2);
    glVertex2f(x + width - dx*0.5f, y- dy *0.5f);

    glTexCoord2fv((float *)&l.uv3);
    glVertex2f(x + width - dx*0.5f, y - height- dy *0.5f);

    glTexCoord2fv((float *)&l.uv4);
    glVertex2f(x - dx * 0.5f, y - height- dy *0.5f);
}

void Writer::startFrame()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->font->getID());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -10.0f, 10.0f);
}

void Writer::endFrame()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void Writer::drawString(char *str, float x, float y, float scale, float alpha)
{
    int i = 0;
    
    int len = strlen(str);

    this->startFrame();
    glColor4f(1,1,1,alpha);
    glBegin(GL_QUADS);

    float cursorX = x;
    const float cursorspacing = this->letterwidth * 0.7f * scale;

    for (i = 0; i < len; i++)
    {
//        glColor3ub(rand()%255, rand()%255, rand()%255);
        char c = str[i];
        this->drawSingleLetter(c, cursorX, y, scale, alpha);
        cursorX += cursorspacing;
    }
    glEnd();
    this->endFrame();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
// 3D
/////////////////////////////////////////////////////////////////////////////////////////////////////

void Writer::drawSingleLetter3D(char c, Vector3 &point, float scale, float alpha, int orientation)
{
    if (c == ' ')
        return;

    const float width = this->letterwidth * scale;
    const float height = this->letterheight * scale;

    int index = this->getIndexByChar(c);
    Letter &l = this->letters[index];

    if (orientation == WRITER_DIRECTION_POSITIVE_X || orientation == WRITER_DIRECTION_NEGATIVE_X)
    {
        //x muuttuu, 
        glTexCoord2fv((float *)&l.uv1);
        glVertex3f(point.x, point.y, point.z);
        glTexCoord2fv((float *)&l.uv2);
        glVertex3f(point.x + width, point.y, point.z);
        glTexCoord2fv((float *)&l.uv3);
        glVertex3f(point.x + width, point.y - height, point.z);
        glTexCoord2fv((float *)&l.uv4);
        glVertex3f(point.x, point.y - height, point.z);
    }
    if (orientation == WRITER_DIRECTION_POSITIVE_Y || orientation == WRITER_DIRECTION_NEGATIVE_Y)
    {
        //y muuttuu, 
        glTexCoord2fv((float *)&l.uv1);
        glVertex3f(point.x, point.y, point.z);
        glTexCoord2fv((float *)&l.uv2);
        glVertex3f(point.x + width, point.y, point.z);
        glTexCoord2fv((float *)&l.uv3);
        glVertex3f(point.x + width, point.y - height, point.z);
        glTexCoord2fv((float *)&l.uv4);
        glVertex3f(point.x, point.y - height, point.z);
    }
    if (orientation == WRITER_DIRECTION_POSITIVE_Z || orientation == WRITER_DIRECTION_NEGATIVE_Z)
    {
        //z muuttuu, 
        glTexCoord2fv((float *)&l.uv1);
        glVertex3f(point.x, point.y, point.z);
        glTexCoord2fv((float *)&l.uv2);
        glVertex3f(point.x + width, point.y, point.z);
        glTexCoord2fv((float *)&l.uv3);
        glVertex3f(point.x + width, point.y, point.z + height);
        glTexCoord2fv((float *)&l.uv4);
        glVertex3f(point.x, point.y, point.z + height);
    }
}


void Writer::drawString3D(const char *str, Vector3 &point, float scale, float alpha, int orientation)
{
    int i = 0;

    if (orientation != WRITER_DIRECTION_POSITIVE_X && 
        orientation != WRITER_DIRECTION_NEGATIVE_X && 
        orientation != WRITER_DIRECTION_POSITIVE_Y && 
        orientation != WRITER_DIRECTION_NEGATIVE_Y && 
        orientation != WRITER_DIRECTION_POSITIVE_Z && 
        orientation != WRITER_DIRECTION_NEGATIVE_Z)
    {
        dmsMsg("Trying to write text with orientation %d\n. No!!", orientation);
        return;
    }
    
    int len = strlen(str);

    Vector3 cursordelta;

    float spaceamount = 0.0f;
    switch(orientation)
    {
        case WRITER_DIRECTION_POSITIVE_X:
            spaceamount = this->letterwidth * 0.7f;
            cursordelta = Vector(1, 0, 0); 
            break;
        case WRITER_DIRECTION_NEGATIVE_X:
            spaceamount = this->letterwidth * 0.7f;
            cursordelta = Vector(-1, 0, 0); 
            break;

        case WRITER_DIRECTION_POSITIVE_Y:
            spaceamount = this->letterheight * 0.7f;
            cursordelta = Vector(0, -1, 0); 
            break;
        case WRITER_DIRECTION_NEGATIVE_Y:
            spaceamount = this->letterheight * 0.7f;
            cursordelta = Vector(0, 1, 0); 
            break;

        case WRITER_DIRECTION_POSITIVE_Z:
            spaceamount = this->letterheight * 0.7f;
            cursordelta = Vector(0, 0, 1); break;
        case WRITER_DIRECTION_NEGATIVE_Z:
            spaceamount = this->letterheight * 0.7f;
            cursordelta = Vector(0, 0, -1); break;

        default:
            cursordelta = Vector(0,0,0); break; //shouldn't ever happen
    }
    Vector3 cursor = point;

    Vector3 cursorspacing = cursordelta * (spaceamount * scale);
 
    glBindTexture(GL_TEXTURE_2D, this->font->getID());
    glBegin(GL_QUADS);
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        this->drawSingleLetter3D(c, cursor, scale, alpha, orientation);
        cursor += cursorspacing;
    }
    glEnd();
}
