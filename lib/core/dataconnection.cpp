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

#include "dataconnection.h"

LEAF_BEGIN_NAMESPACE

DataConnection::DataConnection() : SeriazbleObject()
{
}


QString DataConnection::driver() const
{
   return _driver;
}

QString DataConnection::databaseName() const
{
   return _databaseName;
}

QString DataConnection::serverName() const
{
   return _serverName;
}

QString DataConnection::username() const
{
   return _username;
}

QString DataConnection::password() const
{
    return _password;
}

void DataConnection::setDriver(QString driver)
{
    _driver = driver;
}

void DataConnection::setDatabaseName(QString databaseName)
{
    _databaseName = databaseName;
}

void DataConnection::setServerName(QString serverName)
{
    _serverName = serverName;
}

void DataConnection::setUsername(QString username)
{
    _username = username;
}

void DataConnection::setPassword(QString password)
{
    _password = password;
}

void DataConnection::setDatabaseInfo( QString driver,
                               QString database, QString serverName,
                               QString username, QString password )
{
   _driver = driver;
   _databaseName = database;
   _serverName = serverName;
   _username = username;
   _password = password;
}

bool DataConnection::operator ==(DataConnection &other)
{
    return objectName() == other.objectName();
}

LEAF_END_NAMESPACE
