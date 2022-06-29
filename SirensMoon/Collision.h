/*****************************************************************//**
 * \file   Collision.h
 * \brief  衝突判定を行うためにクラス
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#pragma once

struct Vector2 {
	int x{ 0 };
	int y{ 0 };
};


class AABB {
public:
	Vector2 min;//<コリジョン矩形の左上座標
	Vector2 max;//<コリジョン矩形の右下座標

	/**
	 * \brief デバッグ用衝突判定可視化
	 * 
	 * \param red RGBのR
	 * \param green RGBのG
	 * \param blue　RGBのB
	 */
	void Draw(int red, int green, int blue) const;
};

/**
 * \brief 2つのAABBの交差判定
 * 
 * \param r1 AABB1個目
 * \param r2 AABB2個目
 * \return 交差していたらTrue
 */
bool Intersect(const AABB& r1, const AABB& r2);




