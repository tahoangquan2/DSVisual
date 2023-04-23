#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
	class main_window;
}
QT_END_NAMESPACE

class main_window : public QMainWindow {
	Q_OBJECT

public:
	main_window(QWidget *parent = nullptr);
	~main_window();

private slots:
	void on_backMenu1_clicked();

	void on_backMenu2_clicked();

	void on_backMenu3_clicked();

	void on_backMenu4_clicked();

	void on_backMenu5_clicked();

	void on_backMenu6_clicked();

	void on_backMenu7_clicked();

private:
	Ui::main_window *uiMenu;
};

#endif // MAIN_WINDOW_H
