#pragma once
#include "CDMWindow.h"
class CDMMouseInputWindow :
	public CDMWindow
{
public:
	CDMMouseInputWindow();
	~CDMMouseInputWindow();
	CDMCoord GetMousePosition(const bool& absolute = false);
	bool IsClicking(CDMContext*& ctx, const short& mouseButton = 0) const;
	void Update(CDMContext* & ctx) override;
	void Draw(CDMContext* & ctx) override;
private:
	CDMCoord _globalMousePos;
	CDMKey _closeKey;
};

