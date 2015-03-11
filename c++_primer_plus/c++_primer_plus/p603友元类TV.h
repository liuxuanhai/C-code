#include <iostream>
#ifndef TV_H
#define TV_H

class Tv
{
private:
	int state;  // on or off
	int volume;  // 音量
	int maxchannel;  // 最大的频道数
	int channel;  // 当前广播频道数
	int mode;  // 有线接收 or 广播接收
	int input;  // TV or DVD
public:
	friend class Remote;  // 声明友元遥控器类, 其在公有还是私有都是一样的
	enum {Off, On};
	enum {MinVol, MaxVol = 20};  // 最大音量, 最小音量
	enum {Antenna, Cable};  // 无线, 广播
	enum {TV, DVD};

	Tv(int s = Off, int mc = 125) : state(s), volume(5),
		maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void onoff() {state = (state == On) ? Off : On;}  // 开关机
	bool ison() const {return state == On;}
	bool volup();  // 加音量
	bool voldown();  // 减音量
	void chanup();  // 加频道
	void chandown();  // 减频道
	void set_mode() {mode = (mode == Antenna) ? Cable : Antenna;} // 有线 广播转换
	void set_input() {input = (input == TV) ? DVD : TV;}  // DVD TV转换
	void settings() const;  // 输出当前设置
};

class Remote
{
private:
	int mode;  // TV or DVD
public:
	Remote(int m = Tv::TV) : mode(m) {}
	bool volup(Tv & t) {return t.volup();}
	bool voldowl(Tv & t) {return t.voldown();}
	void onoff(Tv & t) {t.onoff();}
	void chanup(Tv & t) {t.chanup();}
	void chandown(Tv & t) {t.chandown();}
	void set_chan(Tv & t, int c) {t.channel = c;}
	void set_mode(Tv & t) {t.set_mode();}
	void set_input(Tv & t) {t.set_input();}
};

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