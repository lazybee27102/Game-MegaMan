#ifndef _MEGA_MAN_H_
#define _MEGA_MAN_H_

#include <d3dx9.h>
#include "../SFramework/DirectxInput.h"
#include "../SFramework/Animation.h"
#include "../SFramework/AnimationSpec.h"
#include "../SFramework/Sprite.h"
#include <vector>

using namespace s_framework;
class MegaMan : public DirectxInput, public Sprite
{
public:
	MegaMan();
	~MegaMan();

private: 
	AnimationSpec* m_animation = NULL;

public:
	void setTexture(Texture* texture);
	virtual void render() override;
	virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

	virtual void onKeyDown(int KeyCode);
	virtual void onKeyUp(int KeyCode);

	void changeAnimation(int character, int state);
};

#endif // !_MEGA_MAN_H_



