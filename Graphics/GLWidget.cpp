#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "GLWidget.h"
#include "GLBox.h"

GLWidget::GLWidget(QWidget* parent)
	: QOpenGLWidget(parent), m_grabCursor(Qt::BlankCursor) {}

GLWidget::~GLWidget() {
	makeCurrent();
	delete m_shaderProgram;

	foreach(auto* item, m_itemList) {
		delete item;
	}

	doneCurrent();
}

void GLWidget::initializeGL() {
	initializeOpenGLFunctions();

	m_shaderProgram = new QOpenGLShaderProgram;
	m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.vert");
	m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.frag");

	m_shaderProgram->bind();

	QImage boxTexture(":/Textures/cube.png");

	auto* box = new GLBox(QVector3D(-1, -1, -1),
						  QVector3D(1, 1, 1),
						  boxTexture.mirrored());
	m_itemList.append(box);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int width, int height) {
	float vfov = 45.0f;
	float aspectRatio = width / float(height ? height : 1);
	float nearPlane = 0.1f;
	float farPlane = 20.0f;

	m_projection.setToIdentity();
	m_projection.perspective(vfov, aspectRatio, nearPlane, farPlane);
}

void GLWidget::paintGL() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 view;
	view.translate(0.0f, 0.0f, -5.0f);
	view.rotate(m_rotation);

	m_shaderProgram->setUniformValue("mvpMatrix", m_projection * view);

	foreach(auto* item, m_itemList) {
		item->draw(m_shaderProgram);
	}
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
	grabMouse(m_grabCursor);
	m_mousePos = event->globalPos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
	QVector2D diff(event->globalPos() - m_mousePos);
	if (diff.isNull()) { return; }

	//qDebug() << diff << endl;

	float angle = diff.length() / 8.0f;
	QVector3D axis(diff.y(), diff.x(), 0.0f);

	m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

	m_grabCursor.setPos(m_mousePos);
	update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event) {
	releaseMouse();
	Q_UNUSED(event);
}
