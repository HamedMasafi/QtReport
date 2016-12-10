/***************************************************************************
 *   QtReport                                                              *
 *   Qt Report Builder Soultion                                            *
 *                                                                         * 
 *   Copyright (C) 2010 by Hamed Masafi                                    *
 *   Hamed.Masafi@GMail.COM                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef QDATABASEINFODIALOG_H
#define QDATABASEINFODIALOG_H

#include "ui_qreportdatabaseinfodialog.h"
class QReport;
class QReportDataConnection;
class QReportDatabaseInfoDialogPrivate;
class QReportDatabaseInfoDialog : public QDialog, private Ui::QReportDatabaseInfoDialog
{
    Q_OBJECT
    QReportDatabaseInfoDialogPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(QReportDatabaseInfoDialog)


public:
    QReportDatabaseInfoDialog(QReport *report, QReportDataConnection *dataConnection = 0);

//    QString name() const;
//    QString driver() const;
//    QString databaseName() const;
//    QString serverName() const;
//    QString username() const;
//    QString password() const;

//    void setName(QString name);
//    void setDriver(QString driver);
//    void setDatabaseName(QString databaseName);
//    void setServerName(QString serverName);
//    void setUsername(QString username);
//    void setPassword(QString password);

    void setDatabaseInfo( QString driver,
                                   QString database, QString serverName,
                                   QString username, QString password );


    QReportDataConnection *dataConnection() const;
    void setDataConnection(const QReportDataConnection *dataConnection);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_accepted();
    void on_pushButtonTest_clicked();
};

#endif // QDATABASEINFODIALOG_H
