#pragma once
#include <gl2d/gl2d.h>

void renderTarget(
	gl2d::Renderer2D& renderer,
	gl2d::Rect transforms, float size,
	gl2d::Texture texture,
	glm::vec4 uvs);