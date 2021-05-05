#pragma once



class CTimer
{

public:
	int m_tickLastUpdate;
	int m_interval;

	CTimer(int interval);
	bool TimeForUpdate();

};

