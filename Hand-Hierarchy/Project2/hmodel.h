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
#include <glm\gtx\matrix_decompose.hpp>

#include "Model.h"
#include "Shader.h"
#include "rotate.h"

class Bone {
public:
	string nodeName;
	Bone *parent;
	vector<Bone> children;
	glm::mat4 transform;
	glm::mat4 R;

	void Print(string indent, bool last);
	void UpdatePosition(glm::mat4 parent, bool last);

};

void Bone::Print(string indent, bool last)
{
	cout << indent;
	if (last)
	{
		cout << "\\-";
		indent += "  ";
	}
	else {
		cout << "|\t-";
		indent += "| \t";
	}
	cout << this->nodeName << endl;
	for(int i=0; i<this->children.size();i++)
	{
		children[i].Print(indent, i == children.size());
	}
	
}


void Bone::UpdatePosition(glm::mat4 parent, bool last)
{
	//rotate
	//parent=glm::scale(parent, glm::vec3(5.0f));
	//this->transform *= parent;

	/*
	glm::vec3 scale;
	glm::quat R;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	
	glm::decompose(parent,
		scale,
		R,
		translation,
		skew,
		perspective);

	glm::vec3 ptranslation;
	
	glm::decompose(this->transform,
		scale,
		R,
		translation,
		skew,
		perspective);
	*/
	
	this->transform = glm::mat4(parent);
	
	glm::vec3 translate=glm::vec3(0.0f);
	
	if (this->nodeName == "finger_1_1")
	{
		translate = glm::vec3(-5.0f, 10.0f, 0.0f);

	}else if (this->nodeName == "finger_1_2" || this->nodeName == "finger_1_3")
	{
		translate = glm::vec3(0.0f, 2.5f, 0.0f);
	}else if (this->nodeName == "finger_2_1")
	{
		translate=glm::vec3(-2.0f, 11.5f, 0.0f);
	}
	else if (this->nodeName == "finger_2_2" || this->nodeName == "finger_2_3")
	{
		translate = glm::vec3(0.0f, 3.0f, 0.0f);
	}
	else if (this->nodeName == "finger_3_1")
	{
		translate = glm::vec3(1.0f, 11.5f, 0.0f);
	}
	else if (this->nodeName == "finger_3_2" || this->nodeName == "finger_3_3")
	{
		translate = glm::vec3(0.0f, 4.0f, 0.0f);
	}
	else if (this->nodeName == "finger_4_1")
	{
		translate = glm::vec3(4.0f, 11.5f, 0.0f);
	}
	else if (this->nodeName == "finger_4_2" || this->nodeName == "finger_4_3")
	{
		translate = glm::vec3(0.0f, 3.25f, 0.0f);
	}
	else if (this->nodeName == "thumb_1")
	{
		translate = glm::vec3(7.5f, 5.25f, 0.0f);
	}
	else if (this->nodeName == "thumb_2" || this->nodeName == "thumb_3")
	{
		translate = glm::vec3(0.0f, 3.25f, 0.0f);
	}
	
	this->transform = glm::translate(this->transform, translate);//translate
	this->transform *= this->R;//rotate

	//pass on rotation
	for (int i = 0; i<this->children.size(); i++)
	{
		children[i].UpdatePosition(this->transform, i == children.size());
	}

}


class Skeleton
{
public:
	Model model = NULL;
	Bone root;
	Skeleton(Model model);
	void RenderObject(Shader shader,Bone *pNode);
	void Draw(Shader shader);
	void DisplayHierarchy();
	void wave(Bone *bone,glm::vec3 rot);

private:

};

Skeleton::Skeleton(Model model)
	: model(model)
{
	//base bone wrist
	root = Bone();
	root.nodeName = "base";
	root.transform = glm::scale(glm::vec3(0.2f,0.2f,0.2f));
	root.R= qRotate(glm::vec3(45.0f));


	#pragma region Finger1
	//finger 1
	Bone f1_part1 = Bone();
	f1_part1.nodeName = "finger_1_1";

	glm::mat4 cTransform = glm::mat4(root.transform);
	f1_part1.transform = glm::translate(cTransform, glm::vec3(-5.0f, 10.0f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));
	

	Bone f1_part2 = Bone();
	f1_part2.nodeName = "finger_1_2";

	glm::mat4 c2Transform = glm::mat4(f1_part1.transform);
	f1_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 2.5f, 0.0f));
	//f1_part2.transform *= qRotate(glm::vec3(45.0f));

	
	Bone f1_part3 = Bone();
	f1_part3.nodeName = "finger_1_3";

	glm::mat4 c3Transform = glm::mat4(f1_part2.transform);
	f1_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 2.5f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	
	f1_part2.children.push_back(f1_part3);
	f1_part1.children.push_back(f1_part2);
	f1_part1.children.push_back(f1_part3);

	root.children.push_back(f1_part1);
	root.children.push_back(f1_part2);
	root.children.push_back(f1_part3);
#pragma endregion
	
	#pragma region Finger2
	//finger 2
	Bone f2_part1 = Bone();
	f2_part1.nodeName = "finger_2_1";

	cTransform = glm::mat4(root.transform);
	f2_part1.transform = glm::translate(cTransform, glm::vec3(-2.0f, 11.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));



	Bone f2_part2 = Bone();
	f2_part2.nodeName = "finger_2_2";

	c2Transform = glm::mat4(f2_part1.transform);
	f2_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));


	Bone f2_part3 = Bone();
	f2_part3.nodeName = "finger_2_3";

	c3Transform = glm::mat4(f2_part2.transform);
	f2_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));
	
	f2_part2.children.push_back(f2_part3);
	f2_part1.children.push_back(f2_part2);
	f2_part1.children.push_back(f2_part3);

	root.children.push_back(f2_part3);
	root.children.push_back(f2_part2);
	root.children.push_back(f2_part1);

#pragma endregion

	#pragma region Finger3
	//finger 3
	Bone f3_part1 = Bone();
	f3_part1.nodeName = "finger_3_1";

	cTransform = glm::mat4(root.transform);
	f3_part1.transform = glm::translate(cTransform, glm::vec3(1.0f, 11.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));



	Bone f3_part2 = Bone();
	f3_part2.nodeName = "finger_3_2";

	c2Transform = glm::mat4(f3_part1.transform);
	f3_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 4.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone f3_part3 = Bone();
	f3_part3.nodeName = "finger_3_3";

	c3Transform = glm::mat4(f3_part2.transform);
	f3_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 4.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));
	
	f3_part2.children.push_back(f3_part3);
	f3_part1.children.push_back(f3_part2);
	f3_part1.children.push_back(f3_part3);
	
	root.children.push_back(f3_part3);
	root.children.push_back(f3_part2);
	root.children.push_back(f3_part1);

#pragma endregion

	#pragma region Finger4
	//finger 1
	Bone f4_part1 = Bone();
	f4_part1.nodeName = "finger_4_1";

	cTransform = glm::mat4(root.transform);
	f4_part1.transform = glm::translate(cTransform, glm::vec3(4.0f, 11.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));


	Bone f4_part2 = Bone();
	f4_part2.nodeName = "finger_4_2";

	c2Transform = glm::mat4(f4_part1.transform);
	f4_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone f4_part3 = Bone();
	f4_part3.nodeName = "finger_4_3";

	c3Transform = glm::mat4(f4_part2.transform);
	f4_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));
	
	
	
	f4_part1.children.push_back(f4_part3);
	f4_part2.children.push_back(f4_part3);
	f4_part1.children.push_back(f4_part2);

	root.children.push_back(f4_part3);
	root.children.push_back(f4_part2);
	root.children.push_back(f4_part1);

#pragma endregion

	#pragma region Thumb
	//finger 1
	Bone t_part1 = Bone();
	t_part1.nodeName = "thumb_1";

	cTransform = glm::mat4(root.transform);
	t_part1.transform = glm::translate(cTransform, glm::vec3(7.0f, 5.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));

	Bone t_part2 = Bone();
	t_part2.nodeName = "thumb_2";

	c2Transform = glm::mat4(t_part1.transform);
	t_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone t_part3 = Bone();
	t_part3.nodeName = "thumb_3";

	c3Transform = glm::mat4(t_part2.transform);
	t_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	t_part1.children.push_back(t_part3);
	t_part2.children.push_back(t_part3);
	t_part1.children.push_back(t_part2);

	root.children.push_back(t_part3);
	root.children.push_back(t_part2);
	root.children.push_back(t_part1);

#pragma endregion
	
	DisplayHierarchy();



	root.UpdatePosition(root.transform,true);
	//wave(&this->root);
	//root.UpdatePosition(root.transform, true);


}

void Skeleton::DisplayHierarchy() {

	root.Print("", true);
}

void Skeleton::wave(Bone *bone,glm::vec3 rot) {


	bone->R = qRotate(rot);
	
	for (int i=0;i<bone->children.size(); i++)
	{
		if (bone->children[i].nodeName != "thumb_1"
			&& bone->children[i].nodeName != "thumb_2"
			&& bone->children[i].nodeName != "thumb_2") {
			wave(&bone->children[i],rot*6.0f);
		}
	}
	
}


void Skeleton::RenderObject(Shader shader,Bone *pNode)
{
	glm::mat4 transformation;
	transformation = pNode->transform;
	
	
		
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));
	
	model.Draw(shader);

	for each (Bone var in pNode->children)
	{
		RenderObject(shader, &var);
	}
}

void Skeleton::Draw(Shader shader) {
	this->RenderObject(shader,&root);
}




/*
void Skeleton::Rotate(Node )
{
	for each (Node var in pNode->children)
	{
		RenderObject(shader, &var);
	}
}*/
