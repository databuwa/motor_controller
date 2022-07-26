#pragma once

class CTimeDelay
{
private:
	volatile bool isInDelay;
	/**
	 * @brief The interval this function waite between executions in miliseconds.
	 * 
	 */
	const int _time_delay;

public:
	/**
	 * @brief Construct a new CTimeDelay object
	 * 
	 * @param delay The interval this function waite between executions in miliseconds.
	 */
	CTimeDelay(const int &delay) : _time_delay(delay), isInDelay(false) 
	{
	}

	/**
	 * @brief Returns the interval in miliseconds.
	 * 
	 * @return uint32_t 
	 */
	uint32_t GetDelay()
	{
		return _time_delay;
	}

	/**
	 * @brief 
	 * 
	 * @param DelayFunc The functions to execute periodically.
	 * @param values Function arguments.
	 */
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