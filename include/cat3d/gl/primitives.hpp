#pragma once

#include <GL/glew.h>

namespace cat3d::gl {

enum primitive {
	Points		  = GL_POINTS,
	Lines		  = GL_LINES,
	LineStrip	  = GL_LINE_STRIP,
	LineLoop	  = GL_LINE_LOOP,
	Triangles	  = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan	  = GL_TRIANGLE_FAN,
};

}