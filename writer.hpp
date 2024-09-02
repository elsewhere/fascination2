#ifndef _WRITER_HPP_
#define _WRITER_HPP_

#include "externs.hpp"

extern class Writer *writer;

class LetterUV
{
public:
    LetterUV() { this->u = 0.0f; this->v = 0.0f; }
    LetterUV(float u, float v) { this->u = u; this->v = v; };

    LetterUV operator + (LetterUV const &uv);
    LetterUV operator - (LetterUV const &uv);
    LetterUV operator * (float const &f);
    LetterUV operator *= (float const &f);

    float u, v;
};

class Letter
{
public:
    LetterUV uv1;
    LetterUV uv2;
    LetterUV uv3;
    LetterUV uv4;

};

//huora C++
static const int WRITER_DIRECTION_POSITIVE_X = 1;
static const int WRITER_DIRECTION_NEGATIVE_X = 2;
static const int WRITER_DIRECTION_POSITIVE_Y = 4;
static const int WRITER_DIRECTION_NEGATIVE_Y = 8;
static const int WRITER_DIRECTION_POSITIVE_Z = 16;
static const int WRITER_DIRECTION_NEGATIVE_Z = 32;

class Writer
{
public:

    Writer(){};
    Writer(char *texturename);
    void drawString(char *str, float x, float y, float scale, float alpha);
    void drawString3D(const char *str, Vector3 &point, float scale, float alpha, int orientation);

private:
    void startFrame();
    void endFrame();
    void drawSingleLetter(char c, float x, float y, float scale, float alpha);
    void drawSingleLetter3D(char c, Vector3 &point, float scale, float alpha, int orientation);

    int getIndexByChar(char c);

    int lettercount;
    int mapwidth;
    int mapheight;
    Texture *font;

    float letterwidth;
    float letterheight;

    Letter *letters;
};


#endif