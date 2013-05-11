#include "controls.h"
		
//Controls module
	void lua4ps3_controls_read()
	{
		int i;
		ioPadGetInfo2(&lua4ps3_padinfo);
		for(i = 0; i < MAX_PORT_NUM; i++)
		{		 
			if(lua4ps3_padinfo.port_status[i])
			{
				ioPadGetData(i, &lua4ps3_paddata[i]);	 
			}
		}	
	}
	
