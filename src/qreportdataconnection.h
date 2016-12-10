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

#ifndef QREPORTDATASOURCE_H
#define QREPORTDATASOURCE_H

#include "qreportxmlseriazble.h"

class QString;

class QReportDataConnection : public QReportXMLSeriazble
{
    Q_OBJECT

    Q_PROPERTY(QString driver READ driver WRITE setDriver USER true)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName USER true)
    Q_PROPERTY(QString serverName READ serverName WRITE setServerName USER true)
    Q_PROPERTY(QString username READ username WRITE setUsername USER true)
    Q_PROPERTY(QString password READ password WRITE setPassword USER true)

public:
    QReportDataConnection();

    QString driver() const;
    QString databaseName() const;
    QString serverName() const;
    QString username() const;
    QString password() const;

    void setDriver(QString driver);
    void setDatabaseName(QString databaseName);
    void setServerName(QString serverName);
    void setUsername(QString username);
    void setPassword(QString password);

    void setDatabaseInfo( QString driver, QString database, QString serverName, QString username, QString password );

    bool operator ==(QReportDataConnection &other);

private:
    QString _name;
    QString _driver, _databaseName, _serverName, _username, _password;

};

#endif // QREPORTDATASOURCE_H
