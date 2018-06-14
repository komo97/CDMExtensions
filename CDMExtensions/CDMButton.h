#pragma once
#include "CDMWindow.h"
#include <string>

class CDMButton;

typedef void(*ButtonPressCallback)(CDMButton& callingButton, void* parameter);

class CDMButton :
	public CDMWindow
{
public:
	CDMButton(const std::wstring& name, ButtonPressCallback callback, void* parameter);
	~CDMButton();
	void Update(CDMContext* & ctx) override;
	void Draw(CDMContext *& ctx) override;
private:
	ButtonPressCallback _callback;
	void* _parameter;
	std::wstring _name;
};

