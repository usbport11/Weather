#include "stdafx.h"
#include "Weather.h"
	
MWeather::MWeather()
{
	pViewBox = NULL;
	NullPoint(Wind);
	ParticlesUsed[0] = 1;
	ParticlesUsed[1] = 1;
	Stop = true;
}

MWeather::~MWeather()
{
	NullPoint(Wind);
}

void MWeather::MoveParticle(stParticle& Particle, unsigned char Y)
{
	if(IsPointNull(Wind)) 
		Particle.Point = AddPoints(Particle.Point, Particle.Velocity);
	else 
		Particle.Point = AddPoints(Particle.Point, AddPoints(Particle.Velocity, Wind));
	if(Particle.Point.p[1] < 0 )
	{
		if(Y == 0)
		{
			SetPoint(Particle.Point, rand() % int(pViewBox->Size.p[0]), pViewBox->Size.p[1]);
			if(ParticlesUsed[0] < ParticlesCount[0]) ParticlesUsed[0] ++;	
		}
		if(Y == 1)
		{
			SetPoint(Particle.Point, XZoneStart, rand() % int(pViewBox->Size.p[1]));
			if(ParticlesUsed[1] < ParticlesCount[1]) ParticlesUsed[1] ++;
		}
		SetPoint(Particle.Velocity, 0, (rand() % (YVelocityLimit[1] - YVelocityLimit[0]) + YVelocityLimit[0]) * -1);
	}
}

void MWeather::Draw()
{
	if(fabs(Wind.p[0]) > 0 && fabs(Wind.p[0]) < 4) ParticlesCount[1] = ParticlesCount[0] >> 2;
	else ParticlesCount[1] = ParticlesCount[0] >> 1;
	
	//glDisable(GL_TEXTURE_2D);
	glPointSize(2);
	glBegin(GL_POINTS);
	for(unsigned short int i=0; i<ParticlesUsed[0]; i++)
	{
		if(!Stop) MoveParticle(XArray[i], 0);
		glVertex2f(XArray[i].Point.p[0], XArray[i].Point.p[1]);
	}
	if(Wind.p[0] != 0) //> 2
	{
		for(unsigned short int i=0; i<ParticlesUsed[1]; i++)
		{
			if(!Stop) MoveParticle(YArray[i], 1);
			glVertex2f(YArray[i].Point.p[0], YArray[i].Point.p[1]);
		}
	}
	glEnd();
	glPointSize(1);
	//glEnable(GL_TEXTURE_2D);
}

void MWeather::SetWind(float X, float Y)
{
	SetPoint(Wind, X, Y);
	if(Wind.p[0] > 0) XZoneStart = 0;
	else XZoneStart = pViewBox->Size.p[0];
	LogFile<<"Weather: wind x velocity: "<<Wind.p[0]<<endl;
}

void MWeather::SetStop(bool inStop)
{
	Stop = inStop;
}

bool MWeather::Initialize(stViewBox* ViewBox, unsigned short int inParticlesCount)
{
	if(!ViewBox)
	{
		LogFile<<"Weather: empty ViewBox"<<endl;
		return false;
	}
	if(inParticlesCount > 256)
	{
		LogFile<<"Weather: too many points"<<endl;
		return false;
	}
	pViewBox = ViewBox;
	ParticlesCount[0] = inParticlesCount;
	ParticlesCount[1] = inParticlesCount >> 1;
	LogFile<<"Weater: Particles X count: "<<ParticlesCount[0]<<" Particles Y count: "<<ParticlesCount[1]<<endl;
	try
    {
		XArray = new stParticle[ParticlesCount[0]];
		YArray = new stParticle[ParticlesCount[1]];
	}
	catch(bad_alloc& ba)
	{
		LogFile<<"Weather: can not allocate memory"<<endl;
		return false;
	}
	memset(XArray, 0, sizeof(XArray));
	memset(YArray, 0, sizeof(YArray));
	
	YVelocityLimit[0] = 6;
	YVelocityLimit[1] = 10;
	
	for(unsigned short int i=0; i<ParticlesCount[0]; i++)
	{
		SetPoint(XArray[i].Point, rand() % int(pViewBox->Size.p[0]), pViewBox->Size.p[1]);
		SetPoint(XArray[i].Velocity, 0, (rand() % (YVelocityLimit[1] - YVelocityLimit[0]) + YVelocityLimit[0]) * -1);
		LogFile<<"Weather: Particle "<<i<<" x: "<<XArray[i].Point.p[0]<<" y: "<<XArray[i].Point.p[1]<<endl;
	}
	
	for(unsigned short int i=0; i<ParticlesCount[1]; i++)
	{
		SetPoint(YArray[i].Point, 0, rand() % int(pViewBox->Size.p[1]));
		SetPoint(YArray[i].Velocity, 0, (rand() % (YVelocityLimit[1] - YVelocityLimit[0]) + YVelocityLimit[0]) * -1);
		LogFile<<"Weather: Particle "<<i<<" x: "<<YArray[i].Point.p[0]<<" y: "<<YArray[i].Point.p[1]<<endl;
	}
	Stop = false;
	
	return true;
}

void MWeather::Close()
{
	if(XArray) delete [] XArray;
	if(YArray) delete [] YArray;
}
