#include "CDMMouseInputWindow.h"
#include "CDMInputLocker.h"


CDMMouseInputWindow::CDMMouseInputWindow() : CDMWindow()
{
	_globalMousePos = { 0,0 };
}


CDMMouseInputWindow::~CDMMouseInputWindow()
{
}

CDMCoord CDMMouseInputWindow::GetMousePosition(const bool & absolute)
{
	if(absolute)
		return _globalMousePos;
	else
		return CDMCoord{ (SHORT)(_globalMousePos.X - posX - 2), (SHORT)(_globalMousePos.Y - posY - 2)};
}

bool CDMMouseInputWindow::IsClicking(CDMContext *& ctx, const short & mouseButton) const
{
	return !mouseButton ? CDMGetKeyPressed(&ctx->events,CDMKey::mbleft) : CDMGetKeyPressed(&ctx->events, CDMKey::mbright);
}

void CDMMouseInputWindow::Update(CDMContext* & ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Update(ctx);
	if (!CDMInputLocker::InControl(this))
	{
		CDMCoord mousePos = CDMGetMousePos(&ctx->events);
		if (mousePos.X >= posX && mousePos.X <= _width - 1 + posX && mousePos.Y >= posY &&
			mousePos.Y <= _height - 1 + posY &&
			CDMGetKeyPressed(&ctx->events, CDMKey::mbleft))
			CDMInputLocker::RequestPriority(this);
	}
	else
	{
		CDMCoord temp = CDMGetMousePos(&ctx->events);
		if (temp.X > 0)
			_globalMousePos = temp;
		if (CDMGetKeyUp(&ctx->events, _closeKey))
			SetActive(false);
	}
}

void CDMMouseInputWindow::Draw(CDMContext *& ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Draw(ctx);

}
