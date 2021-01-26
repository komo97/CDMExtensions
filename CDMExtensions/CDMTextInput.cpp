#include "CDMTextInput.h"

CDMTextInput::CDMTextInput(const CDMKey & closeKey, const size_t & maxInput, const InputType& type)
{
	_closeKey = closeKey;
	_maxInput = maxInput;
	_cursor = 0;
	_isActive = true;
	_caps = false;
	inputType = type;
	_blink = false;
	_canBlink = false;
	_blinkTimer = 0;
}

void CDMTextInput::ReadInput(CDMEvent* const& events)
{
	if (CDMGetKeyUp(events, _closeKey))
		_isActive = false;
	if (_isActive)
	{
		if (inputType & Text && _text.size() < _maxInput)
		{
			if (CDMGetKeyUp(events, CDMKey::A))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'A' : L'a');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::B))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'B' : L'b');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::C))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'C' : L'c');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::D))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'D' : L'd');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::E))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'E' : L'e');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::F))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'F' : L'f');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::G))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'G' : L'g');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::H))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'H' : L'h');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::I))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'I' : L'i');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::J))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'J' : L'j');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::K))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'K' : L'k');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::L))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'L' : L'l');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::M))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'M' : L'm');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::N))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'N' : L'n');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::O))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'O' : L'o');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::P))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'P' : L'p');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::Q))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'Q' : L'q');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::R))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'R' : L'r');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::S))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'S' : L's');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::T))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'T' : L't');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::U))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'U' : L'u');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::V))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'V' : L'v');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::W))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'W' : L'w');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::X))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'X' : L'x');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::Y))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'Y' : L'y');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::Z))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L'Z' : L'z');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::space))
			{
				_text.insert(_text.begin() + _cursor,
					(_caps) ? L' ' : L' ');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::substract))
			{
				_text.insert(_text.begin() + _cursor, L'-');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::add))
			{
				_text.insert(_text.begin() + _cursor, L'+');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::divide))
			{
				_text.insert(_text.begin() + _cursor, L'/');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::multiply))
			{
				_text.insert(_text.begin() + _cursor, L'*');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::caps))
			{
				_caps ^= 1;
				return;
			}
			if (inputType & AcceptNewline)
			{
				if (CDMGetKeyUp(events, CDMKey::returnK))
				{
					_text.insert(_text.begin() + _cursor, L'\n');
					++_cursor;
					return;
				}
			}
		}
		if (inputType & Numeric && _text.size() < _maxInput)
		{
			if (CDMGetKeyUp(events, CDMKey::one))
			{
				_text.insert(_text.begin() + _cursor, L'1');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::two))
			{
				_text.insert(_text.begin() + _cursor, L'2');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::three))
			{
				_text.insert(_text.begin() + _cursor, L'3');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::four))
			{
				_text.insert(_text.begin() + _cursor, L'4');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::five))
			{
				_text.insert(_text.begin() + _cursor, L'5');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::six))
			{
				_text.insert(_text.begin() + _cursor, L'6');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::seven))
			{
				_text.insert(_text.begin() + _cursor, L'7');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::eight))
			{
				_text.insert(_text.begin() + _cursor, L'8');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::nine))
			{
				_text.insert(_text.begin() + _cursor, L'9');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::zero))
			{
				_text.insert(_text.begin() + _cursor, L'0');
				++_cursor;
				return;
			}
			else if (CDMGetKeyUp(events, CDMKey::decimal) && inputType & AcceptDecimal)
			{
				_text.insert(_text.begin() + _cursor, L'.');
				++_cursor;
				return;
			}
		}
		if (CDMGetKeyUp(events, CDMKey::backspace) && _text.size() > 0 && _cursor > 0)
		{
			_text.erase(_text.begin() + _cursor - 1, _text.begin() + _cursor);
			--_cursor;
			return;
		}
		else if (CDMGetKeyUp(events, CDMKey::left))
		{
			if (_cursor > 0)
				--_cursor;
			return;
		}
		else if (CDMGetKeyUp(events, CDMKey::right))
		{
			if (_cursor < _text.size())
				++_cursor;
			return;
		}
	}
}

void CDMTextInput::SetActive(const bool & status)
{
	_isActive = status;
}

void CDMTextInput::DisplayText(CDMContext *& ctx, const CDMRect & displayArea, CDMLetterColor let, CDMBackgroundColor bg)
{
	if (_isActive)
	{
		CDMPrintf(&ctx, 0, displayArea, let, bg, _text.data());
		if (_canBlink && _blink)
			CDMPrintf(&ctx, 0, CDMRect{ displayArea.Left + (((SHORT)_cursor) % displayArea.Right),
				displayArea.Top + (((SHORT)_cursor) / displayArea.Right), 1, 1 },
				let, (CDMBackgroundColor)(bg | reverseColors), L" ");
		++_blinkTimer %= BLINKTIME;
		if(!_blinkTimer)
			_blink ^= 1;
	}
}

bool CDMTextInput::IsActive() const
{
	return _isActive;
}

bool CDMTextInput::shouldBlink() const
{
	return _canBlink;
}

void CDMTextInput::canBlink(const bool & canBlink)
{
	_canBlink = canBlink;
}

std::wstring CDMTextInput::GetText() const
{
	return _text;
}

void CDMTextInput::SetText(const std::wstring & text)
{
	_text = text;
	_cursor = 1;
}


CDMTextInput::~CDMTextInput()
{
}
