#pragma once

class CTimeDelay
{
private:
	volatile bool isInDelay;
	const int _time_delay;

public:
	CTimeDelay(const int &delay) : _time_delay(delay), isInDelay(false) 
	{
	}

	uint32_t GetDelay()
	{
		return _time_delay;
	}

	template <typename F, typename... types>
	void TimeDelay(F DelayFunc, types... values)
	{
		long mills = millis();
		if (((mills % _time_delay) < 100) && !isInDelay)
		{
			DelayFunc(values...);
			isInDelay = true;
		}
		else
		{
			if (((mills % _time_delay) > 100) && isInDelay)
			{
				isInDelay = false;
			}
		}
	}
};