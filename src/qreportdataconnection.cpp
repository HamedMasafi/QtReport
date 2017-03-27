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

LReportDataConnection::LReportDataConnection() : LReportXMLSeriazble()
{
}


QString LReportDataConnection::driver() const
{
   return _driver;
}

QString LReportDataConnection::databaseName() const
{
   return _databaseName;
}

QString LReportDataConnection::serverName() const
{
   return _serverName;
}

QString LReportDataConnection::username() const
{
   return _username;
}

QString LReportDataConnection::password() const
{
    return _password;
}

void LReportDataConnection::setDriver(QString driver)
{
    _driver = driver;
}

void LReportDataConnection::setDatabaseName(QString databaseName)
{
    _databaseName = databaseName;
}

void LReportDataConnection::setServerName(QString serverName)
{
    _serverName = serverName;
}

void LReportDataConnection::setUsername(QString username)
{
    _username = username;
}

void LReportDataConnection::setPassword(QString password)
{
    _password = password;
}

void LReportDataConnection::setDatabaseInfo( QString driver,
                               QString database, QString serverName,
                               QString username, QString password )
{
   _driver = driver;
   _databaseName = database;
   _serverName = serverName;
   _username = username;
   _password = password;
}

bool LReportDataConnection::operator ==(LReportDataConnection &other)
{
    return objectName() == other.objectName();
}

LEAF_END_NAMESPACE
