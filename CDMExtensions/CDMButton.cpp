#include "CDMButton.h"

//Tienes una maquina expendedora y te tiene que devolver cambio,
//en monedas de cuanto y si tiene disponibilidad de monedas y de preferencia no lo hagas en un arreglo
//100, 25, 10, 5, 1 centavos. TAREA DE VLAD.
//Permitir configuracion de monedas a la maquina.

CDMButton::CDMButton(const std::wstring& name, ButtonPressCallback callback, void* parameter) : CDMWindow(), _parameter(parameter)
{
	_shouldDrag = false;
	_callback = callback;
	_parameter = parameter;
	_name = name;
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
