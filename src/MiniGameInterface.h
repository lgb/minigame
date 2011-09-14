#ifndef MINIGAMEINTERFACE_H
#define MINIGAMEINTERFACE_H

/////////////////////////////////////////////////////////////////////////////

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};

class MiniGame
{
public:
	virtual ~MiniGame() = 0;
	virtual void Initialize() = 0;		// called before start
	virtual void Click(float x, float y) = 0;	// called on mouse click ((x, y) are screen coordinates)
	virtual bool IsComplete() const = 0;	// returns true when minigame successfully finished
	virtual void Render() const = 0;		// called to render one frame (must use global Render function)

public:
	static const int cTextureId = 1;
	static const int cColumns = 5;
	static const int cRows = 5;
};

void Render(const Rect& screenCoords, int textureId, const Rect& textureCoord);

/////////////////////////////////////////////////////////////////////////////

#endif // MINIGAMEINTERFACE_H
