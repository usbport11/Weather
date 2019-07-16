#ifndef weatherH
#define weatherH

struct stParticle
{
	stPoint Point;
	stPoint Velocity;
};

class MWeather
{
private:
	bool Stop;
	stViewBox* pViewBox;
	unsigned short int ParticlesCount[2];
	unsigned short int ParticlesUsed[2];
	unsigned char YVelocityLimit[2];
	unsigned short int XZoneStart;
	stPoint Wind;
	stParticle* XArray;
	stParticle* YArray;
	void MoveParticle(stParticle& Particle, unsigned char Y=0);
	
public:
	MWeather();
	~MWeather();
	bool Initialize(stViewBox* ViewBox, unsigned short int inParticlesCount);
	void SetWind(float X, float Y);
	void Draw();
	void Close();
	void SetStop(bool inStop);
};

#endif
