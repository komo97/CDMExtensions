#include "CDMInputLocker.h"
#include <algorithm>

//std::stack<CDMObject*> CDMInputLocker::_priorityHolders;
//std::vector<CDMObject*> CDMInputLocker::_releasers;
CDMObject* CDMInputLocker::_priorityHolder = nullptr;

CDMInputLocker::CDMInputLocker()
{
}


CDMInputLocker::~CDMInputLocker()
{
}

void CDMInputLocker::RequestPriority(CDMObject * const & obj)
{
	_priorityHolder = obj;
}

bool CDMInputLocker::InControl(CDMObject * const & obj)
{
	return obj == _priorityHolder;
}
