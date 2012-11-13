
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QComboBox;
class QGroupBox;
class QPushButton;
class QSplitter;
class TrackList;
class StockListWidget;
class PlayListWidget;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
		void update(TrackList *stockList, TrackList *playList);
	private slots:
		void addButtonClicked();
	private:
		QGroupBox          *stockListGroupBox;
		QGroupBox          *playListGroupBox;
		QSplitter          *splitter;
		QPushButton        *addButton;
		StockListWidget    *stockListWidget;
		PlayListWidget     *playListWidget;
};

#endif
