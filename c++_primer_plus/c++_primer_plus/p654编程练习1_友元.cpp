#include <iostream>
#include <string>
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

	bool RemoteMoshi(Remote & r) const;
};

class Remote
{
private:
	int mode;  // TV or DVD
	enum {changgui, hudong};
	int moshi;
public:

	friend class Tv;

	Remote(int m = Tv::TV, int ms = Remote::changgui) : mode(m), moshi(ms) {}
	bool volup(Tv & t) {return t.volup();}
	bool voldowl(Tv & t) {return t.voldown();}
	void onoff(Tv & t) {t.onoff();}
	void chanup(Tv & t) {t.chanup();}
	void chandown(Tv & t) {t.chandown();}
	void set_chan(Tv & t, int c) {t.channel = c;}  // 只有这里访问了私有的数据成员
	void set_mode(Tv & t) {t.set_mode();}
	void set_input(Tv & t) {t.set_input();}
	std::string Moshi() const {return moshi == changgui ? "常规模式" : "互动模式";}
};

inline bool Tv::RemoteMoshi(Remote & r) const  // 这里如果直接写在声明的地方(Tv类内部)而不是放在Remote类后面的话在编译的时候会报错说没有定义Remote类, 因为r.moshi...等在Tv类的时候都是不可见的
{
	if (state == On) 
	{                                 //  静态引用不用与特定的对象对应, 所以这里不用写上r.hudong而是写上Remote::hudong
		r.moshi == Remote::changgui ? r.moshi = Remote::hudong : r.moshi = Remote::changgui;
		return true;
	}
	else 
		return false; 
}

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
	std::cout << 1111111111111 << std::endl; 
    std::cout << grey.Moshi() << std::endl;    // check mode
	s27.RemoteMoshi(grey);         // change mode
	std::cout << grey.Moshi() << std::endl;   // recheck mode
    s27.onoff();            // turn set off
	s27.RemoteMoshi(grey);        // try changing mode again
	std::cout << grey.Moshi() << std::endl;     // check result

    return 0;
}