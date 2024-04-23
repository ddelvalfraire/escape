#include "pch.h"

#include "../game-client/TextureManager.h"


class TextureManagerTest : public::testing::Test
{
protected:
	const std::string texture = "../game-client/Entities/door1.png";
	TextureManager texManager;
};

TEST_F(TextureManagerTest, hasTextureTest)
{
	EXPECT_FALSE(texManager.hasTexture(texture));

	texManager.loadTexture(texture);

	EXPECT_TRUE(texManager.hasTexture(texture));
}

TEST_F(TextureManagerTest, loadTextureTest)
{
	EXPECT_NE(texManager.loadTexture(texture), nullptr);
}

TEST_F(TextureManagerTest, getTextureTest)
{
	EXPECT_ANY_THROW(texManager.getTexture(texture));

	texManager.loadTexture(texture);

	EXPECT_NE(texManager.getTexture(texture), nullptr);
}

TEST_F(TextureManagerTest, deleteTextureTest)
{
	texManager.loadTexture(texture);

	EXPECT_NO_THROW(texManager.deleteTexture(texture));
}