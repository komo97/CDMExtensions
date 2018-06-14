#pragma once
#include "CDMWindow.h"
#include "CDMTextInput.h"

class CDMTextInputWindow :
	public CDMWindow
{
public:
	CDMTextInputWindow() = delete;
	CDMTextInputWindow(const CDMKey& closeKey, const CDMTextInput::InputType& type);
	void Update(CDMContext* & ctx) override;
	void Draw(CDMContext* & ctx) override;
	std::wstring GetText() const;
	void SetText(const std::wstring& txt);
	~CDMTextInputWindow();
private:
	CDMTextInput *_inputArea = nullptr;
	void PostSetup() final;
	CDMKey _closeKey;
	CDMTextInput::InputType _type;
};

