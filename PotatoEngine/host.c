#include "pt_def.h"

float newTimestepIncr, oldTimestepIncr;

static int ValidateTimestep(float timestep)
{
	int success = 1;
	newTimestepIncr += timestep;
	
	if (newTimestepIncr < 1)
	{
		success = 0;
	}
	else 
	{
		newTimestepIncr = 0;
	}

	//oldTimestepIncr = newTimestepIncr;
	return success;
}

void InitHost(void)
{
	
}

void Update(float timestep)
{
	if (!ValidateTimestep(timestep))
	{
		return 0;
	}

	VID_Update(timestep);
}

void HOST_Shutdown(void)
{
	VID_Shutdown();
	SYS_Shutdown();
}