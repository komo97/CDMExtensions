#include "CDMTextWindow.h"
#include "CDMInputLocker.h"

void CDMTextWindow::Update(CDMContext* & ctx)
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
		if (_scrollKeyDown != KeysEnd && CDMGetKeyUp(&ctx->events, _scrollKeyDown))
			++_currScroll;
		if (_scrollKeyUp != KeysEnd && CDMGetKeyUp(&ctx->events, _scrollKeyUp) && _currScroll > 0)
			--_currScroll;
		if (CDMGetKeyUp(&ctx->events, _closeKey))
			SetActive(false);
		++_cursorPos;
		if (_autoScroll)
			_currScroll = (_cursorPos / (_width - 2)) / (_height - 2);
		if (_currScroll > (_text.length() / _width))
			_currScroll = (_text.length() / _width);
		if (_cursorPos >= _text.length())
			_cursorPos = _text.length();
	}
}

void CDMTextWindow::Draw(CDMContext *& ctx)
{
	if(!_isActive)
		return;
	CDMWindow::Draw(ctx);
	std::wstring realTxt;
	for (int i = _currScroll * (_width - 3); i < _cursorPos + (_currScroll * (_width - 3)) && i < _text.length(); ++i)
		realTxt += _text.at(i);
	CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 2, (SHORT)posY + 2, (SHORT)_width - 3, (SHORT)_height - 2 }, _bounds, _background, realTxt.data());
}

void CDMTextWindow::SetText(const std::wstring & text)
{
	_text = text;
	_cursorPos = 0;
}

void CDMTextWindow::SetSpeed(const std::size_t & speed)
{
	_speed = speed;
	_currScroll = 0;
}

void CDMTextWindow::SetScrollKeys(const CDMKey & up, const CDMKey & down)
{
	_scrollKeyUp = up;
	_scrollKeyDown = down;
}

CDMTextWindow::CDMTextWindow(const CDMKey& closeKey, const bool& autoScroll) : CDMWindow()
{
	_cursorPos = 0;
	_currScroll = 0;
	_scrollKeyDown = _scrollKeyUp = KeysEnd;
	_closeKey = closeKey;
	_autoScroll = autoScroll;
	_speed = 1;
}


CDMTextWindow::~CDMTextWindow()
{
}
