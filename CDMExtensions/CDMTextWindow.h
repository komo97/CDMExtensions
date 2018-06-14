#pragma once
#include "CDMWindow.h"
#include <string>

class CDMTextWindow :
	public CDMWindow
{
public:
	void Update(CDMContext* & ctx) override;
	void Draw(CDMContext *& ctx) override;
	void SetText(const std::wstring& text);
	void SetSpeed(const std::size_t& speed);
	void SetScrollKeys(const CDMKey& up, const CDMKey& down);
	CDMTextWindow(const CDMKey& closeKey, const bool& autoScroll);
	CDMTextWindow() = delete;
	~CDMTextWindow();
private:
	std::wstring _text;
	size_t _cursorPos;
	size_t _speed;
	size_t _currScroll;
	CDMKey _scrollKeyDown;
	CDMKey _scrollKeyUp;
	CDMKey _closeKey;
	bool _autoScroll;
};

