#pragma once
#include <gl2d/gl2d.h>

void renderHitCircles(
	gl2d::Renderer2D& renderer,
	glm::vec2 position, float size,
	gl2d::Texture texture,
	glm::vec4 uvs);