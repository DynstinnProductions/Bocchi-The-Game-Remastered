#include <hitRender.h>

void renderHitCircles(gl2d::Renderer2D& renderer,
	glm::vec2 position,
	float size,
	gl2d::Texture texture,
	glm::vec4 uvs)
{
	renderer.renderRectangle({ position - glm::vec2(size / 2, size / 2), size, size },
		texture, uvs);
}