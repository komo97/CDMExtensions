#pragma once
#include "CDM.h"
#include "CDMObject.h"
#include <string>

class CDMWindow : public CDMObject
{
public:
	enum BoundsType {
		RectangularDouble = 0,
		RectangularDoubleNoEdges,
		RectangularSimple,
		RoundedBox,
		Diagonal,
		TriangleEdge,
	};
	CDMWindow();
	CDMWindow(const int& width, const int& height, const CDMLetterColor& bounds, const CDMBackgroundColor& background);
	virtual ~CDMWindow();
	int getWidth() const;
	int getHeight() const;
	void SetupWindow(const int& width, const int& height, const CDMLetterColor& bounds, const CDMBackgroundColor& background);
	void ChangeBoundColor(const CDMLetterColor& bounds);
	void ChangeBackgroundColor(const CDMBackgroundColor& background);
	void virtual Draw(CDMContext* & ctx);
	void virtual Update(CDMContext* & ctx);
	bool IsActive() const;
	void SetActive(const bool& status);
	void SetTitle(std::wstring title);
	void ShouldDrag(const bool& dragable);
	void SetBoundsType(const BoundsType& bounds);
	int posX = 0, posY = 0;
private:
	CDMSurface * _upperLeftBounds = nullptr,
			   * _lowerLeftBounds = nullptr,
			   * _upperRightBounds = nullptr,
			   * _lowerRightBounds = nullptr;
	BoundsType _btype = RectangularDouble;
	CDMCoord _startDrag;
	bool _dragStarted;
protected:
	CDMLetterColor _bounds;
	CDMBackgroundColor _background;
	int _width, 
		_height,
		_halfWidth,
		_halfHeight;
	bool _useParentColor = false,
		 _isActive,
		 _shouldDrag;
	std::wstring _title;
	virtual void PostSetup();
	virtual void OnDisable();
	virtual void OnEnable();
};

