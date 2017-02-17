
#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include <GLFW/glfw3.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"

#include "Model.h"
#include "Shader.h"

class Node {
public:
	string nodeName;
	Node *parent;
	vector<Node*> children;
	glm::mat4 transform;
};


class Skeleton
{
public:
	Model model=NULL;
	Node root;
	Skeleton(Model model);
	void RenderObject(Shader shader);
private:

};

Skeleton::Skeleton(Model _model)
{
	model = _model;
	root = Node();
	root.nodeName = "base";
	root.transform = glm::mat4(0.0f);
}

void Skeleton::RenderObject(Shader shader)
{
	glm::mat4 transformation;
	transformation = root.transform;
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));
	model.Draw(shader);
}
