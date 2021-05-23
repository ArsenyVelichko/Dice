#ifndef GLCUBE_H
#define GLCUBE_H

#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "GLGraphicsItem.h"

class GLBox : public GLGraphicsItem{
public:
	GLBox(const QVector3D& min, const QVector3D& max, const QImage& texture);
    ~GLBox();

    void draw(QOpenGLShaderProgram *program) const override;
	void setTexture(const QImage &texture);

private:
    void initGeometry(const QVector3D& min, const QVector3D& max);
	void allocateTexture(const QSize& texSize);

	QOpenGLTexture* m_texture = nullptr;

    QOpenGLBuffer* m_vbo;
	QOpenGLBuffer* m_ebo;
};

#endif // GLCUBE_H
