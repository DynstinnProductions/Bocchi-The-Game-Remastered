#include <target.h>
#include <targetInit.h>

void Target::render(gl2d::Renderer2D& renderer, gl2d::Rect& transforms, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas)
{
	renderTarget(renderer, transforms, enemyShipSize, sprites, atlas.get(type.x, type.y)); 
}