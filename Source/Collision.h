// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Math.h"
#include <vector>
#include "Components/ColliderComponents/CircleColliderComponent.h"
#include "Components/ColliderComponents/AABBColliderComponent.h"

// Intersection functions
bool Intersect(const CircleColliderComponent& s, const AABBColliderComponent& box);