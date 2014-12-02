#ifndef FishingJoy_ProgressProtocol_h
#define FishingJoy_ProgressProtocol_h

class ProgressDelegate
{
public:
	//函数也可以赋值
	virtual void loadingFinished() = 0;
	//??question, 返回值为void，但是末尾却return了。
	virtual void progressPercentageSetter(float percentage){ return ; };
};
#endif