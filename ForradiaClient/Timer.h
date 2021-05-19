#pragma once



class Timer
{

public:
	int m_tickLastUpdate;
	int m_interval;

	Timer(int interval);
	bool TimeForUpdate();

};

