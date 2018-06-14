#pragma once
#include "CDMObject.h"
#include <stack>
#include <vector>

class CDMInputLocker
{
private:
	CDMInputLocker();
	~CDMInputLocker();
	//static std::stack<CDMObject*> _priorityHolders;
	//static std::vector<CDMObject*> _releasers;
	static CDMObject* _priorityHolder;
public:
	static void RequestPriority(CDMObject* const& obj);
	static bool InControl(CDMObject* const& obj);
};

