#include "InkGUI.h"


class Contentpage
{
private:
    void DisplayFullUpdate();
    void DisplaypartialUpdate();
public:
    Contentpage(GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> *display , 
        char tittle[] , char content[] , bool communication[] ,int status[]);
    ~Contentpage();
    static void CommunicationBar(const void*);
};

Contentpage::Contentpage(GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> *display , 
        char tittle[] , char content[] , bool communication[] ,int status[])
{
    display->drawPaged(CommunicationBar,0);
}

void Contentpage::CommunicationBar(const void*)
{

}

Contentpage::~Contentpage()
{
}