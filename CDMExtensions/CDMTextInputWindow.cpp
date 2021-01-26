#include "CDMTextInputWindow.h"
#include "CDMInputLocker.h"

CDMTextInputWindow::CDMTextInputWindow(const CDMKey & closeKey, const CDMTextInput::InputType& type) : CDMWindow()
{
	_closeKey = closeKey;
	_type = type;
}

void CDMTextInputWindow::Update(CDMContext* & ctx)
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
		{
			CDMInputLocker::RequestPriority(this);
			_inputArea->canBlink(true);
		}
		else
			_inputArea->canBlink(false);
	}
	else
	{
		if (CDMGetKeyUp(&ctx->events, _closeKey))
			SetActive(false);
		_inputArea->ReadInput(&ctx->events);
	}
}

void CDMTextInputWindow::Draw(CDMContext *& ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Draw(ctx);
	_inputArea->DisplayText(ctx, CDMRect{ (SHORT)posX + 2, (SHORT)posY + 2, (SHORT)_width - 2, (SHORT)_height - 2 }, _bounds, _background);
}

std::wstring CDMTextInputWindow::GetText() const
{
	return _inputArea->GetText();
}

void CDMTextInputWindow::SetText(const std::wstring & txt)
{
	_inputArea->SetText(txt);
}

CDMTextInputWindow::~CDMTextInputWindow()
{
	if (_inputArea)
		delete _inputArea;
}

void CDMTextInputWindow::PostSetup()
{
	_inputArea = new CDMTextInput(_closeKey, (_width - 2) * (_height - 3), _type);
}
