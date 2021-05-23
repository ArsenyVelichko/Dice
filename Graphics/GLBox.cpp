#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "GLBox.h"

GLBox::GLBox(const QVector3D& min, const QVector3D& max, const QImage& texture) {
	allocateTexture(texture.size());
	setTexture(texture);

	m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

	m_vbo->create();
	m_ebo->create();

	initGeometry(min, max);
}

GLBox::~GLBox() {
	delete m_texture;
	delete m_vbo;
	delete m_ebo;
}

void GLBox::draw(QOpenGLShaderProgram* program) const {
	m_vbo->bind();
	m_ebo->bind();

	m_texture->bind();

	int offset = 0;

	int vertexLocation = program->attributeLocation("a_pos");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);

	int texcoordLocation = program->attributeLocation("a_texCoord");
	program->enableAttributeArray(texcoordLocation);
	program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

	auto* glFuncs = QOpenGLContext::currentContext()->functions();

	int indicesNum = m_ebo->size() / sizeof(GLushort);
	glFuncs->glDrawElements(GL_TRIANGLE_STRIP, indicesNum, GL_UNSIGNED_SHORT, nullptr);

	m_vbo->release();
	m_ebo->release();

	m_texture->release();
}

void GLBox::setTexture(const QImage& texture) {
	if (texture.format() != QImage::Format_ARGB32) {
		qWarning("Invalid texture format");
		return;
	}

	m_texture->setData(QOpenGLTexture::BGRA,
					   QOpenGLTexture::UInt8,
					   texture.constBits());
}

void GLBox::initGeometry(const QVector3D& min, const QVector3D& max) {
	 m_vbo->bind();
	 m_ebo->bind();

	 VertexData vertices[] = {
		 // Vertex data for face 0
		 {QVector3D(min.x(), min.y(), max.z()), QVector2D(0.0f, 0.0f)},  // v0
		 {QVector3D(max.x(), min.y(), max.z()), QVector2D(0.33f, 0.0f)}, // v1
		 {QVector3D(min.x(), max.y(), max.z()), QVector2D(0.0f, 0.5f)},  // v2
		 {QVector3D(max.x(), max.y(), max.z()), QVector2D(0.33f, 0.5f)}, // v3

		 // Vertex data for face 1
		 {QVector3D(max.x(), min.y(), max.z()), QVector2D( 0.0f, 0.5f)}, // v4
		 {QVector3D(max.x(), min.y(), min.z()), QVector2D(0.33f, 0.5f)}, // v5
		 {QVector3D(max.x(), max.y(), max.z()), QVector2D(0.0f, 1.0f)},  // v6
		 {QVector3D(max.x(), max.y(), min.z()), QVector2D(0.33f, 1.0f)}, // v7

		 // Vertex data for face 2
		 {QVector3D(max.x(), min.y(), min.z()), QVector2D(0.66f, 0.5f)}, // v8
		 {QVector3D(min.x(), min.y(), min.z()), QVector2D(1.0f, 0.5f)},  // v9
		 {QVector3D(max.x(), max.y(), min.z()), QVector2D(0.66f, 1.0f)}, // v10
		 {QVector3D(min.x(), max.y(), min.z()), QVector2D(1.0f, 1.0f)},  // v11

		 // Vertex data for face 3
		 {QVector3D(min.x(), min.y(), min.z()), QVector2D(0.66f, 0.0f)}, // v12
		 {QVector3D(min.x(), min.y(), max.z()), QVector2D(1.0f, 0.0f)},  // v13
		 {QVector3D(min.x(), max.y(), min.z()), QVector2D(0.66f, 0.5f)}, // v14
		 {QVector3D(min.x(), max.y(), max.z()), QVector2D(1.0f, 0.5f)},  // v15

		 // Vertex data for face 4
		 {QVector3D(min.x(), min.y(), min.z()), QVector2D(0.33f, 0.0f)}, // v16
		 {QVector3D(max.x(), min.y(), min.z()), QVector2D(0.66f, 0.0f)}, // v17
		 {QVector3D(min.x(), min.y(), max.z()), QVector2D(0.33f, 0.5f)}, // v18
		 {QVector3D(max.x(), min.y(), max.z()), QVector2D(0.66f, 0.5f)}, // v19

		 // Vertex data for face 5
		 {QVector3D(min.x(),  max.y(), max.z()), QVector2D(0.33f, 0.5f)}, // v20
		 {QVector3D(max.x(),  max.y(), max.z()), QVector2D(0.66f, 0.5f)}, // v21
		 {QVector3D(min.x(),  max.y(), min.z()), QVector2D(0.33f, 1.0f)}, // v22
		 {QVector3D(max.x(),  max.y(), min.z()), QVector2D(0.66f, 1.0f)}  // v23
	 };

	 GLushort indices[] = {
		  0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
		  4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
		  8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
		 12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
		 16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
		 20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
	 };

	 m_vbo->allocate(vertices, sizeof(vertices));
	 m_ebo->allocate(indices, sizeof(indices));

	 m_vbo->release();
	 m_ebo->release();
}

void GLBox::allocateTexture(const QSize& texSize) {
	delete m_texture;

	m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);

	m_texture->setSize(texSize.width(), texSize.height());
	m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);

	//m_texture->setMinificationFilter(QOpenGLTexture::Linear);
	//m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

	m_texture->allocateStorage();
}
