#pragma once
#include "CDMWindow.h"
#include <vector>
#include <string>
#include <chrono>

class CDMMenuWindow;

typedef void (*MenuItemCallback)(CDMMenuWindow& callingWindow, void* parameter);

class CDMMenuWindow :
	public CDMWindow
{
public:
	CDMMenuWindow(const CDMKey& up, const CDMKey& down, const CDMKey& cancel, const CDMKey& select);
	~CDMMenuWindow();
	void AddItem(std::wstring name, MenuItemCallback callback, void* callbackParameter);
	void RemoveItem(std::wstring name);
	void Update(CDMContext* & ctx) override;
	void Draw(CDMContext *& ctx) override;
	void SetPreviousMenu(CDMMenuWindow* const& window);
	enum CursorType {
		arrow = 0,
		reverse,
		underline,
	}cursorType;
private:
	typedef struct MenuItem {
		MenuItemCallback callback;
		std::wstring name;
		void* parameter;
		MenuItem(MenuItemCallback cb, std::wstring nm, void* param) : callback(cb), name(nm), parameter(param){}
		MenuItem& operator=(const MenuItem& item)
		{
			callback = item.callback;
			name = item.name;
			parameter = parameter;
			return *this;
		}
	}MenuItem;
	std::vector<MenuItem> _items;
	size_t _selection,
		   _currLetter,
		   _minItemToShow;
	CDMKey  _scrollKeyDown, 
			_scrollKeyUp,
			_selectKey,
			_cancelKey;
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
	CDMMenuWindow* _window = nullptr;
};

