#include "stdafx.h"
#include "Game2.h"

MGame2::MGame2():MWindow() //IMPORTANT
{
	Pause = true;
    Key = new bool [256];
    memset(Key, 0, 256);
    NullPoint(WindValue);
}

MGame2::~MGame2()
{
}

bool MGame2::Initialize()
{	
    LogFile<<"Initialize Game2"<<endl;
    
    if(!WindowInitialized)
    {
    	LogFile<<"Window was not initialized"<<endl;
    	return 0;
	}
	
	//randomize
    LogFile<<"Randomize rand by time"<<endl; 
    srand(time(NULL));
    
    //viewbox
    ViewBox.Enabled = true;
    ViewBox.SetSize((float)WindowWidth, (float)WindowHeight);
    
    //weather
    Weather = new MWeather;
    if(!Weather->Initialize(&ViewBox, 50)) return false;
   
    //VERY IMPORTANT! (Do not use game resources before textures loads)
    //start capture buttons. scene always drawing
    Pause = false;
    LogFile<<"Pause is "<<Pause<<endl;
    
    return true;
}

void MGame2::Start()
{
    Pause = false;
}

void MGame2::Stop()
{
    Pause = true;
}

void MGame2::OnDraw()
{
	Weather->Draw();
}

void MGame2::OnKeyDown(WPARAM wParam)
{
	Key[wParam] = 1;
}

void MGame2::OnKeyUp(WPARAM wParam)
{
	Key[wParam] = 0;
}

void MGame2::OnClose()
{
	Stop();
	LogFile<<"Free game resources"<<endl;
	if(Key) delete [] Key;
	//free classes
	Weather->Close();
	if(Weather) delete Weather;
}

void MGame2::OnMainTimer()
{
	//start-stop game
	if(Key[VK_RETURN])
	{
		Pause = !Pause;
		LogFile<<"Pause = "<<Pause<<endl;
		Key[VK_RETURN] = 0;
		Weather->SetStop(Pause);
	}
	if(!Pause)
	{
		if(Key[VK_LEFT])
		{
			WindValue.p[0] --;
			Weather->SetWind(WindValue.p[0], WindValue.p[1]);
			return;
		}
		if(Key[VK_RIGHT])
		{
			WindValue.p[0] ++;
			Weather->SetWind(WindValue.p[0], WindValue.p[1]);
			return;
		}
	}
}

void MGame2::OnFrameTimer()
{
}

void MGame2::OnSize()
{
	ViewBox.SetSize((float)WindowWidth, (float)WindowHeight);
}
