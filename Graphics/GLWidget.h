#ifndef FORTHEREST_GLWIDGET_H
#define FORTHEREST_GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

#include "GLGraphicsItem.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    GLWidget(QWidget* parent = nullptr);
	~GLWidget();

    void initializeGL() override;
	void resizeGL(int width, int height) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QOpenGLShaderProgram* m_shaderProgram;
	QList<GLGraphicsItem*> m_itemList;

	QCursor m_grabCursor;
	QPoint m_mousePos;

	QMatrix4x4 m_projection;
	QQuaternion m_rotation;
};


#endif //FORTHEREST_GLWIDGET_H
