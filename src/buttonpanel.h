
#ifndef BUTTONPANEL_H_
#define BUTTONPANEL_H_

#include <QWidget>
#include <stdint.h>

class PushButtonWithExtras;
class QStringList;
class QHBoxLayout;
class QSignalMapper;

class ButtonPanel : public QWidget {
	
	Q_OBJECT
	
	public:
		ButtonPanel();
		ButtonPanel(const QStringList &);
		void addButton(const QString &);
		void addButtons(const QStringList &);
		void clear();
	signals:
		void buttonShortClicked(int);
		void buttonLongClicked(int);
	private:
		void init();
		QList<PushButtonWithExtras *> buttonList;
		QHBoxLayout *layout;
		QSignalMapper *shortClickMapper;
		QSignalMapper *longClickMapper;
};

#endif
