#pragma once
#include "BaseObject.h"
class SpriteAnimation : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
//	void			CaculateWorldMatrix();
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;

public:
	SpriteAnimation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);	
	virtual ~SpriteAnimation();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

	GLint		GetHeight() { return m_iHeight; }
	GLint		GetWidth() { return m_iWidth; }
	void		SetFrameTime(GLfloat frameTime) { m_frameTime = frameTime; }
	void		ResetAnimation() { m_currentFrame = 0; }
};

