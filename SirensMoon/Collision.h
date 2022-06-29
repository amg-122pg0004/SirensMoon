/*****************************************************************//**
 * \file   Collision.h
 * \brief  �Փ˔�����s�����߂ɃN���X
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once

struct Vector2 {
	int x{ 0 };
	int y{ 0 };
};


class AABB {
public:
	Vector2 min;//<�R���W������`�̍�����W
	Vector2 max;//<�R���W������`�̉E�����W

	/**
	 * \brief �f�o�b�O�p�Փ˔������
	 * 
	 * \param red RGB��R
	 * \param green RGB��G
	 * \param blue�@RGB��B
	 */
	void Draw(int red, int green, int blue) const;
};

/**
 * \brief 2��AABB�̌�������
 * 
 * \param r1 AABB1��
 * \param r2 AABB2��
 * \return �������Ă�����True
 */
bool Intersect(const AABB& r1, const AABB& r2);




