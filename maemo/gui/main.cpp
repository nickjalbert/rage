#include "rageform.h"

#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	RageForm *widget = new RageForm;
	widget->resize(320, 240);
	widget->setWindowTitle(QApplication::translate("rage", "RAGE!!"));
	widget->show();

#if 0
	/* parent window */
	QWidget window;
	window.resize(320, 240);  // maybe not, if we're doing the layout
	window.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));

	/* Random button, child of window */
	QPushButton *button = new QPushButton(QApplication::translate("xme", "Press Me!"), &window);
	button->move(100, 100);
	button->show();
	window.show();
#endif

#if 0
	/* nested layouts and such */
	QLabel *label = new QLabel(QApplication::translate("xme", "Name"));
	QLineEdit *lineEdit = new QLineEdit();
	QTableView *resultView = new QTableView();

	QHBoxLayout *queryLayout = new QHBoxLayout();
	queryLayout->addWidget(label);
	queryLayout->addWidget(lineEdit);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(queryLayout);
	mainLayout->addWidget(resultView);
	/* reparent the button.  should be okay... */
	mainLayout->addWidget(button);

	window.setLayout(mainLayout);
	window.setWindowTitle(QApplication::translate("xme", "Nested Layout"));
	window.show();
#endif
	
	return app.exec();
}
