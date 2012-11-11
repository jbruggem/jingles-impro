
#ifndef TRACKLISTTABLEDELEGATE_H
#define TRACKLISTTABLEDELEGATE_H

#include <QStyledItemDelegate>

class TrackListTableDelegate : public QStyledItemDelegate {
    
    Q_OBJECT

    public:
        TrackListTableDelegate(QObject *parent = 0);
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
 };

 #endif