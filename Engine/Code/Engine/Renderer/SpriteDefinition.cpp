#include "Engine/Renderer/SpriteDefinition.hpp"
#include "Engine/Renderer/SpriteSheet.hpp"

SpriteDefinition::SpriteDefinition( const SpriteSheet& spriteSheet, int spriteIndex, const Vec2& uvAtMins, const Vec2& uvAtMaxs ):m_spriteSheet(spriteSheet),m_spriteIndex(spriteIndex),m_uvAtMins(uvAtMins), m_uvAtMaxs(uvAtMaxs)
{

}

void SpriteDefinition::GetUVs( Vec2& out_uvAtmins, Vec2& out_uvAtMaxs ) const
{
	out_uvAtmins = m_uvAtMins;
	out_uvAtMaxs = m_uvAtMaxs;
}

const SpriteSheet& SpriteDefinition::GetSpriteSheet() const
{
	return m_spriteSheet;
}

const Texture& SpriteDefinition::GetTexture() const
{
	return m_spriteSheet.GetTexture();
}

float SpriteDefinition::GetAspect() const
{
	float aspect =(m_uvAtMaxs.x-m_uvAtMins.x ) / (m_uvAtMaxs.y - m_uvAtMins.y);
	return aspect;
}
