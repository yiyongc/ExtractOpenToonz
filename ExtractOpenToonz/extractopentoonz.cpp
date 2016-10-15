#include "extractopentoonz.h"
#include "SheetCanvas.h"

ExtractOpenToonz::ExtractOpenToonz(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget* window = new QWidget;
	QVBoxLayout* bodyLayout = new QVBoxLayout;
	QMenuBar* menubar = new QMenuBar();

	//First Menu
	QMenu* menu1 = new QMenu("Menu1");

	QAction* action1 = new QAction("Action 1", menu1);
	menu1->addAction(action1);

	menubar->addMenu(menu1);
	menubar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	bodyLayout->addWidget(menubar);

	SheetCanvas* m_canvas = new SheetCanvas;

	
	bodyLayout->addWidget(m_canvas);

	window->setLayout(bodyLayout);
	setCentralWidget(window);
	setWindowTitle(tr("BVH Designer"));
	setWindowState(Qt::WindowMaximized);

}

ExtractOpenToonz::~ExtractOpenToonz()
{

}
