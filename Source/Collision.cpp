// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
// MinDistSq between two line segments:
// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used, distributed and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.
// ----------------------------------------------------------------

#include "Collision.h"
#include "Components/ColliderComponents/CircleColliderComponent.h"
#include "Components/ColliderComponents/AABBColliderComponent.h"
#include <algorithm>
#include <array>

bool Intersect(const CircleColliderComponent& s, const AABBColliderComponent& box)
{
	float distSq = box.MinDistSq(s.GetCenter());
	return distSq <= (s.GetRadius() * s.GetRadius());
}