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

#include <QtCore/QString>

#include "qreportdataconnection.h"

LEAF_BEGIN_NAMESPACE

QReportDataConnection::QReportDataConnection() : QReportXMLSeriazble()
{
}


QString QReportDataConnection::driver() const
{
   return _driver;
}

QString QReportDataConnection::databaseName() const
{
   return _databaseName;
}

QString QReportDataConnection::serverName() const
{
   return _serverName;
}

QString QReportDataConnection::username() const
{
   return _username;
}

QString QReportDataConnection::password() const
{
    return _password;
}

void QReportDataConnection::setDriver(QString driver)
{
    _driver = driver;
}

void QReportDataConnection::setDatabaseName(QString databaseName)
{
    _databaseName = databaseName;
}

void QReportDataConnection::setServerName(QString serverName)
{
    _serverName = serverName;
}

void QReportDataConnection::setUsername(QString username)
{
    _username = username;
}

void QReportDataConnection::setPassword(QString password)
{
    _password = password;
}

void QReportDataConnection::setDatabaseInfo( QString driver,
                               QString database, QString serverName,
                               QString username, QString password )
{
   _driver = driver;
   _databaseName = database;
   _serverName = serverName;
   _username = username;
   _password = password;
}

bool QReportDataConnection::operator ==(QReportDataConnection &other)
{
    return objectName() == other.objectName();
}

LEAF_END_NAMESPACE
