#include "pch.h"

#include "../game-client/TextureManager.h"

class TextureManagerTest : public::testing::Test
{
protected:
	// filepath will show as "" if debugging libraries are not used in project properties for test
	std::string filePath = "test_texture.png";
	TextureManager texManager;
};

TEST_F(TextureManagerTest, getTextureFailureTest)
{
	// texture notloaded here
	EXPECT_ANY_THROW(texManager.getTexture(filePath));
}

TEST_F(TextureManagerTest, hasTextureTest)
{
	EXPECT_FALSE(texManager.hasTexture(filePath));

	texManager.loadTexture(filePath);

	EXPECT_TRUE(texManager.hasTexture(filePath));
}

TEST_F(TextureManagerTest, loadTextureTest)
{
	EXPECT_NE(texManager.loadTexture(filePath), nullptr);
}

TEST_F(TextureManagerTest, getTextureTest)
{
	texManager.loadTexture(filePath);

	EXPECT_NE(texManager.getTexture(filePath), nullptr);
}

TEST_F(TextureManagerTest, deleteTextureTest)
{
	texManager.loadTexture(filePath);

	EXPECT_NO_THROW(texManager.deleteTexture(filePath));
}