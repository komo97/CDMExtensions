#include "CDMButton.h"


CDMButton::CDMButton(const std::wstring& name, ButtonPressCallback callback, void* parameter) : CDMWindow(), _parameter(parameter)
{
	_shouldDrag = false;
	_callback = callback;
	_parameter = parameter;
	_name = name;
	SetBoundsType(BoundsType::RoundedBox);
}

CDMButton::~CDMButton()
{
}

void CDMButton::Update(CDMContext *& ctx)
{
	CDMWindow::Update(ctx);
	CDMCoord mousePos = CDMGetMousePos(&ctx->events);
	if (mousePos.X >= posX && mousePos.X <= _width - 1 + posX && mousePos.Y >= posY &&
		mousePos.Y <= _height - 1 + posY &&
		CDMGetKeyPressed(&ctx->events, CDMKey::mbleft))
	{
		_bounds = (CDMLetterColor)(_bounds | CDMExtraOptions::reverseColors);
		_callback(*this, _parameter);
	}
	else if (_bounds & CDMExtraOptions::reverseColors && !CDMGetKeyPressed(&ctx->events, CDMKey::mbleft))
		_bounds = (CDMLetterColor)(_bounds ^ CDMExtraOptions::reverseColors);

}

void CDMButton::Draw(CDMContext *& ctx)
{
	CDMWindow::Draw(ctx);
	CDMPrintf(&ctx, 0, CDMRect{ (SHORT)((posX + _width / 2) - (_name.length() / 2)) + 1, (SHORT)(posY + _height / 2), (SHORT)_name.length(), 1 },
		_bounds, _background, _name.data());
}
