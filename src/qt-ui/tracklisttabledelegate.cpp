
#include "tracklisttabledelegate.h"

#include <QPainter>
#include <QApplication>

TrackListTableDelegate::TrackListTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

void TrackListTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);
    
    // const QWidget *widget = QStyledItemDelegatePrivate::widget(option);
    QStyle *style = QApplication::style();
    
    if (index.row() > 2) {
        // used for changing the text color of table cells
        opt.palette.setColor(QPalette::Text, Qt::darkGray);
        
        // used for changing the background color of table cells
        // opt.backgroundBrush = QBrush(Qt::darkRed);
    }
    
    // stole this line from http://qt4-x11.sourcearchive.com/documentation/4.4.2/qstyleditemdelegate_8cpp-source.html
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);
}