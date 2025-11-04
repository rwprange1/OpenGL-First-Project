#include "RenderableObject.h"


RenderableObject::RenderableObject() {

}

RenderableObject::RenderableObject(Shader s, Texture t){
	this->t = t;
	this->s = s;
}

void RenderableObject::setShader(Shader s) {
	this->s = s;
}
void  RenderableObject::setTexture(Texture t) {
	this->t = t;
}

