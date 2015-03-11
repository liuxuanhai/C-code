#include <iostream>
#ifndef 程序清单15_4
#define 程序清单15_4

class Tv;  // forward declaration

class Remote
{
public:
	enum State{Off, On};
	enum {MinVal, MaxVal = 20};
	enum {Antenna, Cable};  // 电视, 广播
	enum {TV, DVD};
private:
	int mode;
public:
	Remote(int m = TV) : mode(m) {}
	bool volup(Tv & t);  // 仅仅进行原型的声明
	bool voldown(Tv & t);
	void onoff(Tv & t);
	void chanup(Tv & t);
	void chandown(Tv & t);
	void set_mode(Tv & t);
	void set_input(Tv & t);
	void set_chan(Tv & t, int c);
};

class Tv
{
private:   // 前面编译器已经看到了Remote类的声明(其中包含set_chan()的声明)
	friend void Remote::set_chan(Tv & t, int c);
	enum State{Off, On};
	enum {MinVol, MaxVol = 20};
	enum {Antenna, Cable};  // 电视, 广播
	enum {TV, DVD};
public:
	Tv(int s = Off, int mc = 125) : state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void onoff() {state = (state == On) ? Off : On;}
	bool ison() const {return state == On;}
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() {mode = (mode == Antenna) ? Cable : Antenna;}
	void set_input() {input = (input == TV) ? DVD : TV;}
	void settings() const;
private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;
	
};

// Remote methods as inline functions
inline bool Remote::volup(Tv & t) {return t.volup();}
inline bool Remote::voldown(Tv & t) {return t.voldown();}
inline void Remote::onoff(Tv & t) {t.onoff();}
inline void Remote::chanup(Tv & t) {t.chanup();}
inline void Remote::chandown(Tv & t) {t.chandown();}
inline void Remote::set_mode(Tv & t) {t.set_mode();}
inline void Remote::set_input(Tv & t) {t.set_input();}
inline void Remote::set_chan(Tv & t, int c) {t.channel = c;}  // Remote类中只有这一个函数访问了Tv类中的私有数据

#endif

bool Tv::volup()
{
	if (volume < MaxVol)
	{
		volume++;
		return true;
	}
	else
		return false;
}

bool Tv::voldown()
{
	if (volume > MinVol)
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

void Tv::settings() const
{
	using std::cout;
	using std::endl;
	cout << "Tv is " << (state == Off ? "Off" : "On") << endl;
	if (state == On)
	{
		cout << "Volume setting = " << volume << endl;
		cout << "Channel setting = " << channel << endl;
		cout << "Mode = " << (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
	}
}