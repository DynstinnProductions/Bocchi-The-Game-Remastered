#include <targetInit.h>

void renderTarget(gl2d::Renderer2D& renderer,
	gl2d::Rect transforms, float size,
	gl2d::Texture texture, glm::vec4 uvs)
{
	renderer.renderRectangle(transforms,
		texture, Colors_White, {}, 0.f, uvs);
}