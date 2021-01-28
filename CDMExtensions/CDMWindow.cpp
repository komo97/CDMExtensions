#include "CDMWindow.h"
#include "CDMInputLocker.h"


CDMWindow::CDMWindow()
{
	_dragStarted = false;
	_shouldDrag = true;
	_isActive = true;
}

CDMWindow::CDMWindow(const int & width, const int & height, const CDMLetterColor & bounds, const CDMBackgroundColor & background) : CDMWindow()
{
}

CDMWindow::~CDMWindow()
{
	if (_upperRightBounds)
		CDMFreeSurface(&_upperRightBounds);
	if (_lowerRightBounds)	  
		CDMFreeSurface(&_lowerRightBounds);
	if (_upperLeftBounds)
		CDMFreeSurface(&_upperLeftBounds);
	if (_lowerLeftBounds)
		CDMFreeSurface(&_lowerLeftBounds);
}

int CDMWindow::getWidth() const
{
	return _width;
}

int CDMWindow::getHeight() const
{
	return _height;
}

void CDMWindow::SetupWindow(const int & width, const int & height, const CDMLetterColor & bounds, const CDMBackgroundColor & background)
{
	if (_upperRightBounds)
		CDMFreeSurface(&_upperRightBounds);
	if (_lowerRightBounds)
		CDMFreeSurface(&_lowerRightBounds);
	if (_upperLeftBounds)
		CDMFreeSurface(&_upperLeftBounds);
	if (_lowerLeftBounds)
		CDMFreeSurface(&_lowerLeftBounds);
	_width = width;
	_height = height;
	_bounds = bounds;
	_background = background;
	_halfHeight = _height / 2;
	_halfWidth = _width / 2;
	_upperLeftBounds = CDMCreateSurface(0, 0, _halfWidth + 1, _halfHeight + 1);
	_lowerLeftBounds = CDMCreateSurface(0, 0, _halfWidth + 1, _halfHeight);
	_upperRightBounds = CDMCreateSurface(0, 0, _halfWidth, _halfHeight + 1);
	_lowerRightBounds = CDMCreateSurface(0, 0, _halfWidth, _halfHeight);
	CDMSetCharacters(&_upperLeftBounds, L'╔', 0, L'═', L'║');
	CDMSetCharacters(&_lowerLeftBounds, L'╚', 0, L'═', L'║');
	CDMSetCharacters(&_upperRightBounds, L'╗', 0, L'═', L'║');
	CDMSetCharacters(&_lowerRightBounds, L'╝', 0, L'═', L'║');
	CDMSetForegroundColor(&_upperLeftBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_lowerLeftBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_upperRightBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_lowerRightBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetBackgroundColor(&_upperLeftBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_lowerLeftBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_upperRightBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_lowerRightBounds, _background, _background, _background, _background);
	for (int i = 0; i <= _halfHeight; ++i)
	{
		for (int j = 0; j <= _halfWidth; ++j)
		{
			if (i <= _halfHeight && i >= 0 && j <= _halfWidth && j >= 0) //Fill
			{
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set2);
				CDMSetPixel(&_lowerLeftBounds, j, i, CDMColorSets::Set2);
				CDMSetPixel(&_upperRightBounds, j, i, CDMColorSets::Set2);
				CDMSetPixel(&_lowerRightBounds, j, i, CDMColorSets::Set2);
			}
			if (i == 0 && j < _halfWidth && j > 0) //Upper bar
			{
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set3);
				CDMSetPixel(&_upperRightBounds, j, i, CDMColorSets::Set3);
			}
			if (i < _halfHeight && i > 0 && j == 0) //Left bar
			{
				CDMSetPixel(&_lowerLeftBounds, j, i, CDMColorSets::Set4);
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set4);
			}
			if (i == _halfHeight && j <= _halfWidth && j >= 0) //Bottom bar
			{
				CDMSetPixel(&_lowerRightBounds, j, i - 1, CDMColorSets::Set3);
				CDMSetPixel(&_lowerLeftBounds, j, i - 1, CDMColorSets::Set3);
			}
			if (i <= _halfHeight && i >= 0 && j == _halfWidth) //Right bar
			{
				CDMSetPixel(&_lowerRightBounds, j - 1, i, CDMColorSets::Set4);
				CDMSetPixel(&_upperRightBounds, j - 1, i, CDMColorSets::Set4);
			}
			if (i == 0 && j == 0) //Upper left corner
			{
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set1);
				CDMSetPixel(&_lowerLeftBounds, j, i, CDMColorSets::Set4);
				CDMSetPixel(&_upperRightBounds, j, i, CDMColorSets::Set3);
			}
			else if (i == 0 && j == _halfWidth) //Upper right corner
			{
				CDMSetPixel(&_upperRightBounds, j-1, i, CDMColorSets::Set1);
				CDMSetPixel(&_lowerRightBounds, j, i, CDMColorSets::Set4);
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set3);
			}
			else if (i == _halfHeight && j == 0) //Lower left corner
			{
				CDMSetPixel(&_lowerLeftBounds, j, i - 1, CDMColorSets::Set1);
				CDMSetPixel(&_lowerRightBounds, j, i, CDMColorSets::Set3);
				CDMSetPixel(&_upperLeftBounds, j, i, CDMColorSets::Set4);
			}
			else if (i == _halfHeight && j == _halfWidth)//Lower right corner
			{
				CDMSetPixel(&_lowerRightBounds, j - 1, i - 1, CDMColorSets::Set1);
				CDMSetPixel(&_lowerLeftBounds, j, i, CDMColorSets::Set3);
				CDMSetPixel(&_upperRightBounds, j, i, CDMColorSets::Set4);
			}
		}
	}
	CDMPrepareSurface(&_upperLeftBounds);
	CDMPrepareSurface(&_lowerLeftBounds);
	CDMPrepareSurface(&_upperRightBounds);
	CDMPrepareSurface(&_lowerRightBounds);
	PostSetup();
}					  

void CDMWindow::ChangeBoundColor(const CDMLetterColor & bounds)
{
	_bounds = bounds;
	CDMSetForegroundColor(&_upperLeftBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_lowerLeftBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_upperRightBounds, _bounds, _bounds, _bounds, _bounds);
	CDMSetForegroundColor(&_lowerRightBounds, _bounds, _bounds, _bounds, _bounds);
}

void CDMWindow::ChangeBackgroundColor(const CDMBackgroundColor & background)
{
	_background = background;
	CDMSetBackgroundColor(&_upperLeftBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_lowerLeftBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_upperRightBounds, _background, _background, _background, _background);
	CDMSetBackgroundColor(&_lowerRightBounds, _background, _background, _background, _background);
}

void CDMWindow::Draw(CDMContext* & ctx)
{
	if (!_isActive)
		return;
	CDMAddSurfaceToContext(&ctx, _upperRightBounds);
	CDMAddSurfaceToContext(&ctx, _lowerLeftBounds);
	CDMAddSurfaceToContext(&ctx, _upperLeftBounds);
	CDMAddSurfaceToContext(&ctx, _lowerRightBounds);
	CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + 1, (SHORT)posY, (SHORT)_width - 1, (SHORT)1 }, _bounds, _background, _title.data());
	if (CDMInputLocker::InControl(this))
		CDMPrintf(&ctx, 0, CDMRect{ (SHORT)posX + (SHORT)_width + 1, (SHORT)posY,1,1 }, _bounds, _background, L"X");
}

void CDMWindow::Update(CDMContext* & ctx)
{
	if (!_isActive)
		return;
	_upperRightBounds->rect.Left = _halfWidth + posX + 1;
	_upperRightBounds->rect.Top = posY;
	_lowerLeftBounds->rect.Left = posX;
	_lowerLeftBounds->rect.Top = _halfHeight + posY + 1;
	_upperLeftBounds->rect.Left = posX;
	_upperLeftBounds->rect.Top = posY;
	_lowerRightBounds->rect.Left = _halfWidth + posX + 1;
	_lowerRightBounds->rect.Top = _halfHeight + posY + 1;
	if (_shouldDrag)
	{
		CDMCoord mousePos = CDMGetMousePos(&ctx->events);
		if (mousePos.X >= posX && mousePos.X <= _width - 1 + posX && mousePos.Y == posY &&
			CDMGetKeyPressed(&ctx->events, CDMKey::mbleft))
		{
			_startDrag = CDMCoord{ mousePos.X - (SHORT)posX, mousePos.Y - (SHORT)posY};
			_dragStarted = true;
		}
		if (!CDMGetKeyPressed(&ctx->events, CDMKey::mbleft))
			_dragStarted = false;
		if (_dragStarted)
		{
			posX = mousePos.X - _startDrag.X;
			posY = mousePos.Y - _startDrag.Y;
		}
	}
}

bool CDMWindow::IsActive() const
{
	return _isActive;
}

void CDMWindow::SetActive(const bool & status)
{
	if (_isActive && !status)
		OnDisable();
	else if (!_isActive && status)
		OnEnable();
	_isActive = status;
}

void CDMWindow::SetTitle(std::wstring title)
{
	if (title.length() > _width - 2)
	{
		for (int i = 0; i < _width - 2; ++i)
			_title += title.at(i);
	}
	else
		_title = title;
}

void CDMWindow::ShouldDrag(const bool & dragable)
{
	_shouldDrag = dragable;
}

void CDMWindow::PostSetup()
{
}

void CDMWindow::OnDisable()
{
	
}

void CDMWindow::OnEnable()
{
	CDMInputLocker::RequestPriority(this);
}
