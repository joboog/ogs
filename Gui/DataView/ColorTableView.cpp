/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 *
 * \file ColorTableView.cpp
 *
 * Created on 2010-06-17 by Karsten Rink
 *
 */

#include "ColorTableView.h"
#include <QHeaderView>
#include <QPainter>

ColorTableView::ColorTableView( QWidget* parent /*= 0*/ ) : QTableView(parent)
{
	this->verticalHeader()->hide();
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->resizeColumnsToContents();
	this->resizeRowsToContents();
}

void ColorTableViewDelegate::paint(QPainter* painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
	QColor val;
	if (index.column() == 1)
	{
		if (qVariantCanConvert<QColor>(index.data()))
		{
			val = qVariantValue<QColor>(index.data());
			QBrush brush(val);
			painter->fillRect(option.rect, brush);
		}
	}
	else
		QItemDelegate::paint(painter, option, index);
}

QSize ColorTableViewDelegate::sizeHint( const QStyleOptionViewItem &option,
                                        const QModelIndex &index ) const
{
	QSize s = QItemDelegate::sizeHint(option, index);
	if( s.isValid() )
		s.setHeight((int)(0.5 * s.height()));
	return s;
}

