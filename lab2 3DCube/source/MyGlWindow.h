//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "colorCube.h"
#include "Viewer.h"


class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	void draw();

	void setSize(int w, int h) { m_width = w; m_height = h; }
	void setAspect(float aspect) { if (m_viewer) m_viewer->setAspectRatio(aspect); }
	Viewer* getViewer() const { return m_viewer.get(); }

private:
	GLuint vaohandle;

	std::unique_ptr<ShaderProgram> shaderProgram;
	std::unique_ptr<ColorCube> m_cube;
	std::unique_ptr<Viewer> m_viewer;

	int m_width;
	int m_height;
	
	void setupBuffer();

};
