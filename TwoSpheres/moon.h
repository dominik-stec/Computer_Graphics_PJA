#ifndef MOON_H
#define MOON_H

#include "indexmodel.h"
#include "movablemodel.h"
#include "texturemodel.h"
#include "matma.h"
#include "texturecameraprogram.h"

class Moon : public IndexModel, public MovableModel, public TextureModel {
public:
	Moon(float init_velocity = 40, float init_angle = 0);
	void SetInitAngle(float angle) { angle_ = angle; }
	void SetVelocity(float velocity) { velocity_ = velocity; }
	void Initialize(int n, int m, float R, float r);
	void Draw(const TextureCameraProgram & program) const;
	void Move(float delta_t);
	void SpeedUp();
	void SlowDown();
	void ToggleAnimated();
	//void SelectTexturePrim(GLUint t) {texture_ = t;}
private:
	int n_; // mesh parameter
	int m_; // mesh parameter

	float R; //big radius
	float r; //small radius

	float angle_;
	float velocity_;
	bool animated_;

	//dodane druga sfera
	//Mat4 model_matrix_prim_;

	//texture swithc
	//GLuint texture_prim_

};

#endif // MOON_H
