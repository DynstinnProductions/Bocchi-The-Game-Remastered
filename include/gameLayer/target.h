#pragma once
#include <gl2d/gl2d.h>

constexpr float enemyShipSize = 250.f;

struct Target
{

	glm::ivec2 type = {}; // used to index into texture atlas AKA used to select the enemy sprite
	gl2d::Rect transforms = {};

	float speed = 0.f;
	float spawnRate = 0.f;

	void render(gl2d::Renderer2D& renderer,gl2d::Rect& transforms, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas);

	bool update(float deltaTime, gl2d::Rect tranforms, float speed);
};