#ifndef game2H
#define game2H

#include "Window.h"
#include "Weather.h"

class MGame2: public MWindow
{
private:
	//statuses
	bool Pause;
	
	//keyboard
	bool* Key;
	
	//clases
	MWeather* Weather;
	stPoint WindValue;
	
	//viewbox
	stViewBox ViewBox;
	
	//overload virtual functions
	void OnDraw();
	void OnKeyUp(WPARAM wParam);
	void OnKeyDown(WPARAM wParam);
	void OnMainTimer();
	void OnFrameTimer();
	void OnSize();
	
	//local
	void Start();
	void Stop();
	
public:
	MGame2();
	~MGame2();
	bool Initialize();
	bool LoadConfig();
	void OnClose();
};

#endif
