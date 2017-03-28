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

#include <QList>
#include <QHash>
#include <QVariant>
#include <QSizeF>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QXmlParseException>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintPreviewDialog>

#include "dataconnection.h"
#include "widgets/widgetbase.h"
#include "widgets/band.h"
#include "core/report.h"
#include "datatable.h"
#include "lreportprintsettings.h"
#include "parametere.h"


#define ZMINBAND   10
#define ZMAXBAND   99
#define ZMINWIDGET   100
#define ZMAXWIDGET   999

LEAF_BEGIN_NAMESPACE

class LReportPrivate
{
public:
    LReportPrivate(LReport *parent) : q_ptr(parent)
    {

    }

    QList<LReportBand*>           bands;
    QList<LReportWidgetBase*>     widgets;
    QList<LReportDataConnection*> connections;

    qreal marginLeft;
    qreal marginBottom;
    qreal marginTop;
    qreal marginRight;

    QSizeF pageSize;

    QString filePath;

    QList<LReportDataTable*> tables;
    QList<LReportParametere*> parameters;

private :
    LReport  *q_ptr;
    Q_DECLARE_PUBLIC(LReport)
};


/*!
  \classlass LReport
  define a new Report class. Report class can be used for rendering or designing reports
*/
LReport::LReport() : d_ptr(new LReportPrivate(this)), _printSetting(new LReportPrintSettings)
{
}


QList<LReportBand*> *LReport::bands()
{
    Q_D(LReport);
    return &d->bands;
}
QList<LReportWidgetBase*> *LReport::widgets()
{
    Q_D(LReport);
    return &d->widgets;
}

void LReport::removeBand(QString name)
{
    Q_D(LReport);
    name = name.toLower();
    foreach (LReportBand *band, d->bands)
        if(band->objectName().toLower() == name)
            d->bands.removeOne(band);
}

void LReport::removeWidget(QString name)
{
    Q_D(LReport);
    name = name.toLower();
    foreach (LReportWidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == name)
            d->widgets.removeOne(widget);
}

/*!
  ery LReportWidgetBase can be placed on one QSectionBand, This methos change
  rent section of the widget
  aram widget The RReportWidgetBase
  aram parent The new parent of widget
*/
void LReport::changeParent(LReportWidgetBase *widget, LReportBand *parent)
{
    //TODO ...
    if( widget->parentBand() )
        widget->parentBand()->childs()->removeOne( widget );

    if(parent){
        widget->setParentBand( parent );
        widget->setChildPos( parent->mapFromScene( widget->scenePos() ) );
        parent->childs()->append( widget );
    }//if
}

QList<LReportDataTable*> LReport::dataTablesByName(QString tableName)
{
    Q_D(LReport);
    QList<LReportDataTable*> ret;

    foreach(LReportDataTable *datasource, d->tables)
        if(datasource->objectName() == tableName)
            ret.append(datasource);

    return ret;
}


QString LReport::filePath() const
{
    Q_D(const LReport);
    return d->filePath;
}


bool LReport::load( QString path )
{
    Q_D(LReport);

    QFile file( path );

    //QDataStream stream( &file );

    QDomDocument doc("ReportDocument");

    if ( !file.open(QIODevice::ReadWrite) )
        return false;


    QString ems;
    int errorLine = 0;
    int errorColumn = 00;
    if ( !doc.setContent(&file, &ems, &errorLine, &errorColumn) )
    {
        qDebug() << "Error in XML file: "
                 << ems << " Error line:" << errorLine
                 << " Error col:" << errorColumn;
        file.close();
        return false;
    }//if

    QDomElement report = doc.firstChildElement(XML_NODE_REPORT);
    QDomNodeList bands = report.elementsByTagName(XML_NODE_BANDS).at(0).childNodes();
    QDomNodeList connections = report.elementsByTagName(XML_NODE_CONNECTIONS).at(0).childNodes();
    QDomNodeList dataSources = report.elementsByTagName(XML_NODE_DATATABLES).at(0).childNodes();
    QDomNodeList parameteres = report.elementsByTagName(XML_NODE_PARAMETERS).at(0).childNodes();

    //load connections
    if(connections.count() != 0)
        for(int i = 0; i < connections.count(); i++){
            LReportDataConnection *connection = new LReportDataConnection();
            QDomElement el = connections.at(i).toElement();
            connection->loadDom(&el);
            addConnection(connection);
        }

    //load datasources
    if(dataSources.count() != 0)
        for(int i = 0; i < dataSources.count(); i++){
            QDomElement el = dataSources.at(i).toElement();
            LReportDataTable *dataTable = new LReportDataTable(el.attribute("connectionName"));
            dataTable->loadDom(&el);
            addDataTable(dataTable);
        }

    if(parameteres.count() != 0)
        for(int i = 0; i < parameteres.count(); i++){
            QDomElement el = parameteres.at(i).toElement();
            LReportParametere *param = new LReportParametere();
            param->loadDom(&el);
            addParametere(param);
        }

    if(bands.count() != 0)
        for(int i = 0; i < bands.count(); i++){
            QDomElement elBand = bands.at(i).toElement();
            int type = elBand.attribute( "bandType", "0" ).toInt();
            LReportBand *band = new LReportBand( (BandType)type );
            band->loadDom( &elBand );

            QDomElement elWidget = elBand.firstChildElement(XML_NODE_WIDGET);
            for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement(XML_NODE_WIDGET)) {
                LReportWidgetBase *widget;
                widget = LReportWidgetBase::createWidget( &elWidget );

                d->widgets.append( widget );
                changeParent( widget, band );

                widget->loadDom( &elWidget );
            }

            d->bands.append(band);
        }//for

    file.close();
    d->filePath = path;
    return true;
}

void LReport::save(QString path)
{
    Q_D(LReport);

    if(path.isEmpty())
        path = d->filePath;

    QFile file(path);
    if(file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly)){
        file.write(getXmlContent());
        file.close();
        d->filePath = path;
    }else{
        //TODO: Show warning message
    }
}

QByteArray LReport::getXmlContent(int NodeFlags) const
{
    Q_D(const LReport);

    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(XML_NODE_REPORT);

    if(NodeFlags & Connection){
        QDomElement connectionsDom = doc.createElement(XML_NODE_CONNECTIONS);
        foreach(LReportDataConnection *conn, d->connections){
            QDomElement elConn = doc.createElement(XML_NODE_CONNECTION);
            conn->saveDom(&elConn);
            connectionsDom.appendChild(elConn);
        }//foreach
        report.appendChild( connectionsDom );
    }//if

    if(NodeFlags & Parametere){
        QDomElement parametersDom = doc.createElement(XML_NODE_PARAMETERS);
        foreach(LReportParametere *param, d->parameters){
            QDomElement elParam = doc.createElement(XML_NODE_PARAMETER);
            param->saveDom(&elParam);
            parametersDom.appendChild(elParam);
            report.appendChild( parametersDom );
        }//foreach
    }//if

    if(NodeFlags & DataTable){
        QDomElement dataSourcesDom = doc.createElement(XML_NODE_DATATABLES);
        foreach(LReportDataTable *dataSource, d->tables){
            QDomElement elDataSource = doc.createElement(XML_NODE_DATATABLE);
            dataSource->saveDom(&elDataSource);
            dataSourcesDom.appendChild(elDataSource);
        }//foreach
        report.appendChild( dataSourcesDom );
    }//if


    if(NodeFlags & Band){
        QDomElement bandDom = doc.createElement(XML_NODE_BANDS);
        //save bands
        for( int i = 0; i < d->bands.count(); i++ ) {
            QDomElement band = doc.createElement(XML_NODE_BAND);
            band.setAttribute( "name", d->bands.at(i)->objectName() );
            band.setAttribute( "headerHeight", d->bands.at(i)->headerHeight() );
            band.setAttribute( "bandType", d->bands.at(i)->bandType() );
            d->bands.at(i)->saveDom( &band );

            bandDom.appendChild( band );

            if(NodeFlags & Widget){
                //save current band's widgets
                for( int j = 0; j < d->bands.at(i)->childs()->count(); j++ ) {
                    QDomElement child = doc.createElement(XML_NODE_WIDGET);
                    d->bands.at(i)->childs()->at(j)->saveDom( &child );
                    band.appendChild( child );
                }//for
            }//if
        }//for
        report.appendChild(bandDom);
    }


    //TODO: does not work ***
    if(NodeFlags & Widget){
        QDomElement widgetsDom = doc.createElement(XML_NODE_WIDGETS);

        foreach (LReportWidgetBase *w, d->widgets) {
            if(w->parentBand())
                break;
            QDomElement child = doc.createElement(XML_NODE_WIDGET);
            w->saveDom( &child );
            widgetsDom.appendChild( child );
        }//for

        report.appendChild(widgetsDom);
    }

    doc.appendChild( report );
    return doc.toByteArray();
}

void LReport::widgetToBack( LReportWidgetBase *widget )
{
    Q_D(LReport);
    if( !widget->parentBand() ) return;

    foreach( LReportWidgetBase *child, d->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMAXWIDGET )
            child->setZValue( child->zValue() + 1 );

    widget->setZValue( ZMINWIDGET );
}

void LReport::widgetToFront( LReportWidgetBase *widget )
{
    if( !widget->parentBand() ) return;

    foreach( LReportWidgetBase *child, d_ptr->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMINWIDGET )
            child->setZValue( child->zValue() - 1 );

    widget->setZValue( ZMAXWIDGET );
}

void LReport::bandToBack( LReportBand *band )
{
    Q_D(LReport);
    foreach( LReportBand *section, d->bands )
        if( section->zValue() != ZMAXBAND )
            section->setZValue( section->zValue() + 1 );

    band->setZValue( ZMINBAND );
}

void LReport::bandToFront( LReportBand *band )
{
    Q_D(LReport);
    foreach( LReportBand *section, d->bands )
        if( section->zValue() != ZMINBAND )
            section->setZValue( section->zValue() - 1 );

    band->setZValue( ZMAXBAND );
}

LReportBand *LReport::section(QString sectionName)
{
    Q_D(LReport);
    sectionName = sectionName.toLower();

    foreach(LReportBand *section, d->bands)
        if(section->objectName().toLower() == sectionName)
            return section;

    return 0;
}

LReportWidgetBase *LReport::findWidgetByName(QString widgetName)
{
    Q_D(LReport);
    widgetName = widgetName.toLower();

    foreach(LReportWidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == widgetName)
            return widget;

    return 0;
}

LReportBand *LReport::findBandByName(QString bandName)
{
    Q_D(LReport);
    bandName = bandName.toLower();

    foreach(LReportBand *band, d->bands)
        if(band->objectName().toLower() == bandName)
            return band;

    return 0;
}

LReportDataConnection *LReport::findConnectionByName(QString connectionName)
{
    Q_D(LReport);
    connectionName = connectionName.toLower();

    foreach(LReportDataConnection *conn, d->connections)
        if(conn->objectName().toLower() == connectionName)
            return conn;

    return 0;
}



QList<LReportDataTable*> LReport::dataTablesByConnections(QString connectionName)
{
    Q_D(LReport);
    QList<LReportDataTable*> ret;

    foreach(LReportDataTable *datatable, d->tables)
        if(datatable->connectionName() == connectionName)
            ret.append(datatable);

    return ret;
}

QList<LReportDataTable*> LReport::dataTables()
{
    Q_D(const LReport);
    return d->tables;
}

void LReport::addDataTable(LReportDataTable *tableName)
{
    Q_D(LReport);
    d->tables.append( tableName );
}

LReportDataTable *LReport::dataTable(QString tableName)
{
    Q_D(LReport);
    tableName = tableName.toLower();

    foreach(LReportDataTable *table, d->tables)
        if(table->objectName().toLower() == tableName)
            return table;

    return 0;
}

LReportDataTable *LReport::dataTable(QString tableName, QString connectionName)
{
    Q_D(LReport);
    tableName = tableName.toLower();
    connectionName = connectionName.toLower();

    foreach(LReportDataTable *table, d->tables)
        if(table->objectName().toLower() == tableName && table->connectionName() == connectionName)
            return table;

    return 0;
}

void LReport::removeDataTable(LReportDataTable *table)
{
    Q_D(LReport);
    d->tables.removeOne(table);
}

LReportParametere *LReport::parameter(QString name)
{
    Q_D(LReport);
    foreach(LReportParametere *param, d->parameters)
        if(param->objectName() == name)
            return param;
    return 0;
}

QList<LReportParametere*> LReport::parameters()
{
    Q_D(const LReport);
    return d->parameters;
}

void LReport::addParametere( QString name, QVariant value )
{
    LReportParametere *param = new LReportParametere( name, value );
    addParametere( param );
}

void LReport::addParametere( LReportParametere *param )
{
    Q_D(LReport);
    if( !parameter(param->objectName()))
        d->parameters.append( param );
}

void LReport::setParametereValue(QString name, QVariant value)
{
    Q_D(LReport);
    foreach(LReportParametere *param, d->parameters)
        if(param->objectName() == name)
            param->setValue(value);
}

void LReport::removeParametere(LReportParametere *param)
{
    Q_D(LReport);
    d->parameters.removeOne(param);
}

/**
  * Return all connections in current report
  */
QList<LReportDataConnection*> LReport::connections() const
{
    Q_D(const LReport);
    return d->connections;
}

/**
  * Add new connection to report. A connection is an object of \e LReportDataConnection type
  * that can have one or more datasource for data defention. A connection used for report
  * designing, At runtime data from QtSql module replace by this connections.
  */
void LReport::addConnection(LReportDataConnection *conn)
{
    Q_D(LReport);
    if(!connection(conn->objectName()))
        d->connections.append(conn);
}

void LReport::removeConnection(LReportDataConnection *conn)
{
    Q_D(LReport);
    for(int i = 0; i < d->connections.count(); i++)
        if(d->connections.at(i)->objectName() == conn->objectName()){
            d->connections.removeAt(i);
            break;
        }
}

void LReport::setDataSource(QString dataTableName, QSqlQuery &query)
{
    Q_UNUSED(dataTableName);
    Q_UNUSED(query);
}

void LReport::print()
{
    QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setPageMargins (15,15,15,15,QPrinter::Millimeter);
    printer.setFullPage(false);
    printer.setOutputFileName("output.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat); //you can use native format of system usin QPrinter::NativeFormat

    QPainter painter(&printer); // create a painter which will paint 'on printer'.
    painter.setFont(QFont("Tahoma",8));
    painter.drawText(200,200,"Test");
    painter.end();

    QPrintPreviewDialog dialog(&printer);
    dialog.exec();
}

LReportPrintSettings *LReport::printSetting() const
{
    return _printSetting;
}

void LReport::setPrintSetting(LReportPrintSettings *printSetting)
{
    _printSetting = printSetting;
}

/*!
  Find and return a connection named \e connectionName if there are no connection names
  \e connectionName return 0.
  */
LReportDataConnection *LReport::connection(QString connectionName)
{
    Q_D(LReport);
    foreach(LReportDataConnection *conn, d->connections)
        if(conn->objectName() == connectionName)
            return conn;

    return 0;
}

LEAF_END_NAMESPACE
