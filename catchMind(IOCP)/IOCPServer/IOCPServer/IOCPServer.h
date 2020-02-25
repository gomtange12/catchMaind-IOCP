#pragma once
#include "Singleton.h"

class IOCPServer : public Singleton<IOCPServer>
{
private:
	HANDLE			iocp;
public:

	void			 initNetwork();
	void			 releaseNetwork();
	inline HANDLE	 getIocp()const { return iocp; }

};