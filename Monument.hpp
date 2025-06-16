#pragma once
#include <vector>

#pragma once
class Monument {
public:
	float x;
	float y;
	float z;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int shader;
	std::vector<float>& vertices;
	std::vector<unsigned int>& indices;
	unsigned texture;
	void (*generateVertices)(Monument* m);

	Monument(float x, float y, float z, unsigned texture, unsigned shader);
	Monument();
	~Monument();
public:
	virtual void draw();
	virtual void drawStill();
	virtual void drawLetter();
	virtual void setup();
};