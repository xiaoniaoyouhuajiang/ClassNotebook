#include "lab2.h"
size_t Shape::counter = 0;
std::ostream& operator<< (std::ostream& os, Shape& p)
{
    p.print(os);
    return os;
}
void Shape::setColor(Color newcolor)
{
    color = newcolor;
}
Color Shape :: getColor() const //РїРѕР»СѓС‡РµРЅРёРµ С†РІРµС‚Р°
{
    return color;
}

void Ellipse::print(std::ostream& os)
{
    os<< "Id: " << id << std::endl;
}
void Ellipse ::  move(int dx, int dy) {//РїРµСЂРµРјРµС‰РµРЅРёРµ
    center.x+=dx;
    center.y+=dy;
}
void Ellipse :: rotate(int angle) { //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    fi+=angle;
}
void Ellipse :: scale(int k)//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
{
    a=a*k;
    b=b*k;
}

void SectorOfEllipse::print(std::ostream& os)
{
    os<< "Id: " << id << std::endl;
}

Point Ellipse::getCenter() const
{
    return center;
}
unsigned int Ellipse::getAAxis()
{
    return a;
}
unsigned int Ellipse::getBAxis()
{
    return b;
}
unsigned int Ellipse::getAngle()
{
    return fi;
}

void SectorOfEllipse::split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3) {
    //Сѓ СЌР»Р»РёРїСЃР° Рё РµРіРѕ СЃРµРєС‚РѕСЂРѕРІ РєРѕРѕСЂРґРёРЅР°С‚С‹ С†РµРЅС‚СЂР°, РїРѕР»СѓРѕСЃРё Рё СѓРіРѕР» РЅР°РєР»РѕРЅР° Р±СѓРґСѓС‚ РѕРґРёРЅР°РєРѕРІС‹РјРё
    if(ellipse)
    {
        Color ellipseColor = ellipse->getColor();
        Color colorS1(ellipseColor.red,0,0);
        Color colorS2(0,ellipseColor.green,0);
        Color colorS3(0,0,ellipseColor.blue);

        Point ellipseCenter = ellipse->getCenter();
        unsigned int a = ellipse->getAAxis();
        unsigned int b = ellipse->getBAxis();
        unsigned int angle = ellipse->getAngle();

        *s1 = SectorOfEllipse(colorS1, ellipseCenter, a, b, angle, 0, 120);
        *s2 = SectorOfEllipse(colorS2, ellipseCenter, a, b, angle, 120, 240);
        *s3 = SectorOfEllipse(colorS3, ellipseCenter, a, b, angle, 240, 360);
        delete ellipse;
    }
}

bool SectorOfEllipse::operator ==(const SectorOfEllipse &other) const
{
    return(a == other.a &&
           b == other.b &&
           getColor() == other.getColor() &&
           getCenter() == other.getCenter() &&
           fi == other.fi &&
           f1 == other.f1 &&
           f2 == other.f2);
}
//Р РµР°Р»РёР·РѕРІР°С‚СЊ РјРµС‚РѕРґ static void SectorOfEllipse::split(Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3),
//РєРѕС‚РѕСЂС‹Р№ РїСЂРёРЅРёРјР°РµС‚ СЌР»Р»РёРїСЃ Рё СЂР°Р·СЂРµР·Р°РµС‚ РµРіРѕ РЅР° 3 РЅРµРїРµСЂРµСЃРµРєР°СЋС‰РёС…СЃСЏ СЃРµРєС‚РѕСЂР°. Р­Р»Р»РёРїСЃ РїСЂРё СЌС‚РѕРј РґРѕР»Р¶РµРЅ СѓРґР°Р»СЏС‚СЊСЃСЏ. Р¦РІРµС‚ РєР°Р¶РґРѕРіРѕ СЃРµРєС‚РѕСЂР° Р·Р°РґР°С‘С‚СЃСЏ
//РѕРґРЅРѕР№ РёР· СЃРѕСЃС‚Р°РІР»СЏСЋС‰РёС… С†РІРµС‚Р° РёСЃС…РѕРґРЅРѕРіРѕ СЌР»Р»РёРїСЃР°.
//РџСЂРёРјРµСЂ: Р±С‹Р» СЌР»Р»РёРїСЃ Р»РёРјРѕРЅРЅРѕРіРѕ С†РІРµС‚Р°(#F8F344). РџРѕР»СѓС‡РёР»Рё s1 - РєСЂР°СЃРЅС‹Р№(#F80000), s2 - Р·РµР»С‘РЅС‹Р№(#00F300), s3 - СЃРёРЅРёР№(#000044).



bool checkParallelogram(Point a, Point b, Point c, Point d){//РїСЂРѕРІРµСЂРєР° РЅР° РїР°СЂР°Р»Р»РµР»РѕРіСЂР°РјРј
    //СЂР°Р·РЅРёС†Р°РјРё РјРµР¶РґСѓ x-РІРѕР№ РєРѕРѕСЂРґРёРЅР°С‚РѕР№ (Р° Рё РІ) РґРѕР»Р¶РЅР° Р±С‹С‚СЊ С‚Р°РєРѕР№ Р¶Рµ, РєР°Рє Рё Сѓ (c Рё d)
    //Р° СЂР°Р·РЅРёС†Р° РјРµР¶РґСѓ Сѓ-РєРѕРІС‹РјРё РєРѕРѕСЂРґРёРЅР°С‚Р°РјРё (Р° Рё d)==(b Рё c)
    if( ((b.x-a.x)==(c.x-d.x)) & ((c.y-b.y)==(d.y-a.y)) ) return true;
    else return false;
}
void Parallelogram::print(std::ostream& os)
{
    os<< "Id: " << id << std::endl;
}
void Parallelogram ::  move(int dx, int dy) {//РїРµСЂРµРјРµС‰РµРЅРёРµ
    a.x+=dx;
    a.y+=dy;
    b.x+=dx;
    b.y+=dy;
    c.x+=dx;
    c.y+=dy;
    d.x+=dx;
    d.y+=dy;
}
void Parallelogram :: rotate(int angle) { //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    angle=angle;
}
void Parallelogram :: scale(int k)//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
{
    a.x*=k;
    a.y*=k;
    b.x*=k;
    b.y*=k;
    c.x*=k;
    c.y*=k;
    d.x*=k;
    d.y*=k;
}
