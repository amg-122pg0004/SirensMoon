/*****************************************************************//**
 * \file   Collision.h
 * \brief  衝突判定を行うためにクラス
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "Collision.h"

#include <DxLib.h>


bool Intersect(const AABB& r1, const AABB& r2) {

    if (r1.max.x < r2.min.x) {
        return false;
    }
    if (r2.max.x < r1.min.x) {
        return false;
    }
    if (r1.max.y < r2.min.y) {
        return false;
    }
    if (r2.max.y < r1.min.y) {
        return false;
    }
    return true;
}

void AABB::Draw(int red, int green, int blue) const {
    DrawBox(min.x, min.y, max.x, max.y, GetColor(red, green, blue), FALSE);
}
