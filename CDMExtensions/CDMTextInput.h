#pragma once
#include "CDM.h"
#include "CDMObject.h"
#include <string>

class CDMTextInput : public CDMObject
{
public:
	enum InputType
	{
		Text = 0x001,
		Numeric = 0x002,
		AlphaNum = 0x003,
		AcceptNewline = 0x010,
		AcceptDecimal = 0x020,
	}inputType;
	enum CursorType
	{
		reverseCursor = 0,
		underlineCursor = 0,
	}cursorType;
	CDMTextInput() = delete;
	CDMTextInput(const CDMKey& closeKey, const size_t& maxInput, const InputType& type);
	void ReadInput(CDMEvent* const& events);
	void SetActive(const bool& status);
	void DisplayText(CDMContext *& ctx, const CDMRect& displayArea, CDMLetterColor let, CDMBackgroundColor bg);
	bool IsActive() const;
	std::wstring GetText() const;
	void SetText(const std::wstring& text);
	~CDMTextInput();
private:
	bool _isActive,
		 _caps;
	std::wstring _text;
	size_t	_maxInput,
			_cursor;
	CDMKey _closeKey;
	bool _blink;
};

