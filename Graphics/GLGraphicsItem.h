#ifndef GLGRAPHICSITEM_H
#define GLGRAPHICSITEM_H

#include <QOpenGLShaderProgram>

class GLGraphicsItem {
public:
	struct VertexData {
		QVector3D pos;
		QVector3D texCoord;
	};

	virtual void draw(QOpenGLShaderProgram* program) const = 0;

	virtual ~GLGraphicsItem() = default;
};

#endif // GLGRAPHICSITEM_H
