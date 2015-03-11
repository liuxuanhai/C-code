#ifndef PE15TV_H_
#define PE15TV_H_

class Tv
{
private:
    int state;
    int volume;
    int maxchannel;
    int channel;
    int mode;
    int input;
public:
    friend class Remote;    // Remote can access Tv private parts
    enum State{Off, On};
    enum {MinVal,MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, VCR};

    Tv(State s = Off, int mc = 100) : state(s), volume(5),
        maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() {state = (state == On)? Off : On;}
    bool ison() {return state == On ? true : false;}
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    void set_mode() {mode = (mode == Antenna)? Cable : Antenna;}
    void set_input() {input = (input == TV)? VCR : TV;}
    void settings();
    void rmode(Remote & r);

};

class Remote
{
friend class Tv;

public:
    enum Style {Normal, Interactive};
    Remote(int m = Tv::TV, int s = Normal) :
                mode(m), style(s) {}
    bool volup(Tv & t) { return t.volup();}
    bool voldown(Tv & t) { return t.voldown();}
    void onoff(Tv & t) { t.onoff(); }
    void chanup(Tv & t) {t.chanup();}
    void chandown(Tv & t) {t.chandown();}
    void set_chan(Tv & t, int c) {t.channel = c;}
    void set_mode(Tv & t) {t.set_mode();}
    void set_input(Tv & t) {t.set_input();}
    void show_style();
private:
    int mode;     // TV or VCR
    int style;  // Normal or Interactive
};

// place definition here where both Tv and Remote
// class declarations are known
inline void Tv::rmode(Remote & r)
{
    if(state == Off)
        return;
    if (r.style == Remote::Normal)
        r.style = Remote::Interactive;
    else r.style = Remote::Normal;
}
#endif

// pe15tv.cpp

#include <iostream>

bool Tv::volup()
{
    if (volume < MaxVal)
    {
        volume++;
        return true;
    }
    else
        return false;
}
bool Tv::voldown()
{
    if (volume > MinVal)
    {
        volume--;
        return true;
    }
    else
        return false;
}

void Tv::chanup()
{
    if (channel < maxchannel)
        channel++;
    else
        channel = 1;
}

void Tv::chandown()
{
    if (channel > 1)
        channel--;
    else
        channel = maxchannel;
}

void Tv::settings()
{
    using std::cout;
    cout << "TV is " << (state == Off? "Off\n" : "On\n");
    if (state == On)
    {
        cout << "Volume setting = " << volume << "\n";
        cout << "Channel setting = " << channel << "\n";
        cout << "Mode = "
            << (mode == Antenna? "antenna\n" : "cable\n");
        cout << "Input = "
            << (input == TV? "TV\n" : "VCR\n");
    }
}

void Remote::show_style()
{
    if (style == Normal)
        std::cout << "Remote in Normal mode\n";
    else
        std::cout << "Remote in Interactive mode\n";
}

// pe15-1.cpp
// link with pe15tv.cpp

#include <iostream>

int main(void)
{
    Tv s20;
    std::cout << "Initial settings for 20\" TV:\n";
    s20.settings();
    s20.onoff();
    s20.chanup();
    std::cout << "\nAdjusted settings for 20\" TV:\n";
    s20.settings();

    Remote grey;

    grey.set_chan(s20, 10);
    grey.volup(s20);
    grey.volup(s20);
    std::cout << "\n20\" settings after using remote\n";
    s20.settings();

    Tv s27(Tv::On);
    s27.set_mode();
    grey.set_chan(s27,28);
    std::cout << "\n27\" settings:\n";
    s27.settings();
    grey.show_style();    // check mode
    s27.rmode(grey);         // change mode
    grey.show_style();    // recheck mode
    s27.onoff();            // turn set off
    s27.rmode(grey);        // try changing mode again
    grey.show_style();     // check result

    return 0;
}