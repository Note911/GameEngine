#include "AbstractRenderer.h"

void AbstractRenderer::setColor(glm::vec3 color){
	renderColor = color;
}

glm::vec3 AbstractRenderer::getColor() {
	return renderColor;
}

void AbstractRenderer::setWireFrameMode(bool enable) {
	wireFrameMode = enable;
}

bool AbstractRenderer::isWireFrameEnabled() {
	return wireFrameMode;
}