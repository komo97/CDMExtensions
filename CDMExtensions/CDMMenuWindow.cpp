#include "CDMMenuWindow.h"
#include "CDMInputLocker.h"
#include <algorithm>

CDMMenuWindow::CDMMenuWindow(const CDMKey & up, const CDMKey & down, const CDMKey & cancel, const CDMKey & select) :
	CDMWindow()
{
	_scrollKeyDown = down;
	_scrollKeyUp = up;
	_selectKey = select;
	_cancelKey = cancel;
	_selection = 0;
	_currLetter = 0;
	_startTime = std::chrono::high_resolution_clock::now();
	cursorType = arrow;
	_minItemToShow = 0;
	SetBoundsType(BoundsType::RectangularDouble);
}

CDMMenuWindow::~CDMMenuWindow()
{
}

void CDMMenuWindow::AddItem(std::wstring name, MenuItemCallback callback, void * callbackParameter)
{
	_items.push_back(MenuItem(callback, name, callbackParameter));
}

void CDMMenuWindow::RemoveItem(std::wstring name)
{
	_items.erase(std::remove_if(_items.begin(), _items.end(), [name](const MenuItem& item) {return item.name == name; }), _items.end());
}

void CDMMenuWindow::Update(CDMContext *& ctx)
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
		if (CDMGetKeyUp(&ctx->events, _scrollKeyUp))
		{
			if (_selection > 0)
				--_selection;
			else
				_selection = _items.size() - 1;
			_currLetter = 0;
			_startTime = std::chrono::high_resolution_clock::now();
		}
		else if (CDMGetKeyUp(&ctx->events, _scrollKeyDown))
		{
			if (_selection < _items.size() - 1)
				++_selection;
			else
				_selection = 0;
			_currLetter = 0;
			_startTime = std::chrono::high_resolution_clock::now();
		}
		else if (CDMGetKeyUp(&ctx->events, _selectKey))
			_items[_selection].callback(*this, _items[_selection].parameter);
		else if (CDMGetKeyUp(&ctx->events, _cancelKey))
		{
			if (_window)
			{
				_window->SetActive(true);
				SetActive(false);
			}
		}
	}
}

void CDMMenuWindow::Draw(CDMContext *& ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Draw(ctx);
	std::wstring str;
	int iter = 0;
	if (_items.size() > _height - 3 && (int)(_selection - (_height - 3)) >= 0)
		_minItemToShow = _selection - (_height - 3) + 1;
	else
		_minItemToShow = 0;
	for (auto &i : _items)
	{
		str = L"";
		if (iter < (_height - 3 + _minItemToShow) && iter >= _minItemToShow)
		{
			if (iter == _selection)
			{
				for (int x = _currLetter; x < _width - 3 + _currLetter && x < i.name.length(); ++x)
					str += i.name[x];
				if (_currLetter >= i.name.length())
					_currLetter = 0;
				switch (cursorType)
				{
				default:
				case arrow:
					CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 2, (SHORT)(posY + 2 + iter - _minItemToShow), (SHORT)_width - 2, 1 }, _bounds,
						_background, L"»%s", str.data());
					break;
				case reverse:
					CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 2, (SHORT)(posY + 2 + iter - _minItemToShow), (SHORT)_width - 2, 1 }, _bounds,
						(CDMBackgroundColor)(_background | CDMExtraOptions::reverseColors), str.data());
					break;
				case underline:
					CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 2, (SHORT)(posY + 2 + iter - _minItemToShow), (SHORT)_width - 2, 1 }, _bounds, 
						(CDMBackgroundColor)(_background | CDMExtraOptions::underscore), str.data());
					break;
				}
				std::chrono::duration<double> deltaT = (std::chrono::high_resolution_clock::now() - _startTime);
				if (deltaT.count() > 1)
				{
					++_currLetter;
					_startTime = std::chrono::high_resolution_clock::now();
				}
			}
			else
			{
				for (int x = 0; x < _width - 3 && x < i.name.length(); ++x)
					str += i.name[x];
				CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 2, (SHORT)(posY + 2 + iter - _minItemToShow), (SHORT)_width - 2, 1 }, _bounds,
					_background, str.data());
			}
		}
		++iter;
	}
	if (_minItemToShow == 0)
		CDMPoke(&ctx, CDMCoord{ (SHORT)(posX + _width - 1), (SHORT)(posY + _height - 1) }, L'v', _bounds, _background);
	else if (_minItemToShow > 0 && _minItemToShow < _items.size() - (_height - 3) )
	{								   
		CDMPoke(&ctx, CDMCoord{ (SHORT)(posX + _width - 1), (SHORT)(posY + _height - 1) }, L'v', _bounds, _background);
		CDMPoke(&ctx, CDMCoord{ (SHORT)(posX + _width - 1), (SHORT)(posY + 1) }, L'^', _bounds, _background);
	}															   
	else
		CDMPoke(&ctx, CDMCoord{ (SHORT)(posX + _width - 1), (SHORT)(posY + 1) }, L'^', _bounds, _background);
}

void CDMMenuWindow::SetPreviousMenu(CDMMenuWindow * const & window)
{
	_window = window;
}
