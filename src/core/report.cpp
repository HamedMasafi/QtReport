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
#include "core/reportprintsettings.h"
#include "parametere.h"
#include "reportmodel.h"


#define ZMINBAND   10.
#define ZMAXBAND   99.
#define ZMINWIDGET   100.
#define ZMAXWIDGET   999.

LEAF_BEGIN_NAMESPACE

class ReportPrivate
{
public:
    ReportPrivate(Report *parent) : q_ptr(parent), model(new ReportModel(parent))
    {

    }

    QList<Band*>           bands;
    QList<WidgetBase*>     widgets;
    QList<DataConnection*> connections;

    qreal marginLeft;
    qreal marginBottom;
    qreal marginTop;
    qreal marginRight;

    QSizeF pageSize;

    QString filePath;

    QList<DataTable*> tables;
    QList<Parametere*> parameters;

    ReportModel *model;

private :
    Report  *q_ptr;
    Q_DECLARE_PUBLIC(Report)
};


/*!
  \classlass
  define a new Report class. Report class can be used for rendering or designing reports
*/
Report::Report() : d_ptr(new ReportPrivate(this)), _printSetting(new PrintSettings)
{
}


QList<Band*> *Report::bands()
{
    Q_D(Report);
    return &d->bands;
}
QList<WidgetBase*> *Report::widgets()
{
    Q_D(Report);
    return &d->widgets;
}

void Report::removeBand(QString name)
{
    Q_D(Report);
    name = name.toLower();
    foreach (Band *band, d->bands)
        if(band->objectName().toLower() == name) {
            d->bands.removeOne(band);
            d->model->removeBand(band);
        }
}

void Report::removeWidget(QString name)
{
    Q_D(Report);
    name = name.toLower();
    foreach (WidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == name)
            d->widgets.removeOne(widget);
}

/*!
  ery WidgetBase can be placed on one QSectionBand, This methos change
  rent section of the widget
  aram widget The RReportWidgetBase
  aram parent The new parent of widget
*/
void Report::changeParent(WidgetBase *widget, Band *parent)
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

QList<DataTable*> Report::dataTablesByName(QString tableName)
{
    Q_D(Report);
    QList<DataTable*> ret;

    foreach(DataTable *datasource, d->tables)
        if(datasource->objectName() == tableName)
            ret.append(datasource);

    return ret;
}


QString Report::filePath() const
{
    Q_D(const Report);
    return d->filePath;
}

ReportModel *Report::model() const
{
    Q_D(const Report);
    return d->model;
}


bool Report::load( QString path )
{
    Q_D(Report);

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
            DataConnection *connection = new DataConnection();
            QDomElement el = connections.at(i).toElement();
            connection->loadDom(&el);
            addConnection(connection);
        }

    //load datasources
    if(dataSources.count() != 0)
        for(int i = 0; i < dataSources.count(); i++){
            QDomElement el = dataSources.at(i).toElement();
            DataTable *dataTable = new DataTable(el.attribute("connectionName"));
            dataTable->loadDom(&el);
            addDataTable(dataTable);
        }

    if(parameteres.count() != 0)
        for(int i = 0; i < parameteres.count(); i++){
            QDomElement el = parameteres.at(i).toElement();
            Parametere *param = new Parametere();
            param->loadDom(&el);
            addParametere(param);
        }

    if(bands.count() != 0) {
        for(int i = 0; i < bands.count(); i++){
            QDomElement elBand = bands.at(i).toElement();
            int type = elBand.attribute( "bandType", "0" ).toInt();
            Band *band = new Band(::BandType(type));
            band->loadDom( &elBand );

            QDomElement elWidget = elBand.firstChildElement(XML_NODE_WIDGET);
            for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement(XML_NODE_WIDGET)) {
                WidgetBase *widget;
                widget = WidgetBase::createWidget( &elWidget );

                d->widgets.append( widget );
                changeParent( widget, band );

                widget->loadDom( &elWidget );
            }

            d->bands.append(band);
        }
    }//for

    file.close();
    d->filePath = path;
    return true;
}

void Report::save(QString path)
{
    Q_D(Report);

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

QByteArray Report::getXmlContent(int NodeFlags) const
{
    Q_D(const Report);

    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(XML_NODE_REPORT);

    if(NodeFlags & ConnectionType){
        QDomElement connectionsDom = doc.createElement(XML_NODE_CONNECTIONS);
        foreach(DataConnection *conn, d->connections){
            QDomElement elConn = doc.createElement(XML_NODE_CONNECTION);
            conn->saveDom(&elConn);
            connectionsDom.appendChild(elConn);
        }//foreach
        report.appendChild( connectionsDom );
    }//if

    if(NodeFlags & ParametereType){
        QDomElement parametersDom = doc.createElement(XML_NODE_PARAMETERS);
        foreach(Parametere *param, d->parameters){
            QDomElement elParam = doc.createElement(XML_NODE_PARAMETER);
            param->saveDom(&elParam);
            parametersDom.appendChild(elParam);
            report.appendChild( parametersDom );
        }//foreach
    }//if

    if(NodeFlags & DataTableType){
        QDomElement dataSourcesDom = doc.createElement(XML_NODE_DATATABLES);
        foreach(DataTable *dataSource, d->tables){
            QDomElement elDataSource = doc.createElement(XML_NODE_DATATABLE);
            dataSource->saveDom(&elDataSource);
            dataSourcesDom.appendChild(elDataSource);
        }//foreach
        report.appendChild( dataSourcesDom );
    }//if


    if(NodeFlags & BandType){
        QDomElement bandDom = doc.createElement(XML_NODE_BANDS);
        //save bands
        for( int i = 0; i < d->bands.count(); i++ ) {
            QDomElement band = doc.createElement(XML_NODE_BAND);
            band.setAttribute( "name", d->bands.at(i)->objectName() );
            band.setAttribute( "headerHeight", d->bands.at(i)->headerHeight() );
            band.setAttribute( "bandType", d->bands.at(i)->bandType() );
            d->bands.at(i)->saveDom( &band );

            bandDom.appendChild( band );

            if(NodeFlags & WidgetType){
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
    if(NodeFlags & WidgetType){
        QDomElement widgetsDom = doc.createElement(XML_NODE_WIDGETS);

        foreach (WidgetBase *w, d->widgets) {
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

void Report::widgetToBack( WidgetBase *widget )
{
    Q_D(Report);
    if( !widget->parentBand() ) return;

    foreach( WidgetBase *child, d->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMAXWIDGET )
            child->setZValue( child->zValue() + 1 );

    widget->setZValue( ZMINWIDGET );
}

void Report::widgetToFront( WidgetBase *widget )
{
    if( !widget->parentBand() ) return;

    foreach( WidgetBase *child, d_ptr->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMINWIDGET )
            child->setZValue( child->zValue() - 1 );

    widget->setZValue( ZMAXWIDGET );
}

void Report::bandToBack( Band *band )
{
    Q_D(Report);
    foreach( Band *section, d->bands )
        if( section->zValue() != ZMAXBAND )
            section->setZValue( section->zValue() + 1 );

    band->setZValue( ZMINBAND );
}

void Report::bandToFront( Band *band )
{
    Q_D(Report);
    foreach( Band *section, d->bands )
        if( section->zValue() != ZMINBAND )
            section->setZValue( section->zValue() - 1 );

    band->setZValue( ZMAXBAND );
}

Band *Report::section(QString sectionName)
{
    Q_D(Report);
    sectionName = sectionName.toLower();

    foreach(Band *section, d->bands)
        if(section->objectName().toLower() == sectionName)
            return section;

    return nullptr;
}

WidgetBase *Report::findWidgetByName(QString widgetName)
{
    Q_D(Report);
    widgetName = widgetName.toLower();

    foreach(WidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == widgetName)
            return widget;

    return nullptr;
}

Band *Report::findBandByName(QString bandName)
{
    Q_D(Report);
    bandName = bandName.toLower();

    foreach(Band *band, d->bands)
        if(band->objectName().toLower() == bandName)
            return band;

    return nullptr;
}

DataConnection *Report::findConnectionByName(QString connectionName)
{
    Q_D(Report);
    connectionName = connectionName.toLower();

    foreach(DataConnection *conn, d->connections)
        if(conn->objectName().toLower() == connectionName)
            return conn;

    return nullptr;
}



QList<DataTable*> Report::dataTablesByConnections(QString connectionName)
{
    Q_D(Report);
    QList<DataTable*> ret;

    foreach(DataTable *datatable, d->tables)
        if(datatable->connectionName() == connectionName)
            ret.append(datatable);

    return ret;
}

QList<DataTable*> Report::dataTables()
{
    Q_D(Report);
    return d->tables;
}

void Report::addDataTable(DataTable *table)
{
    Q_D(Report);
    d->tables.append(table);
    d->model->addDataTable(table);
}

DataTable *Report::dataTable(QString tableName)
{
    Q_D(Report);
    tableName = tableName.toLower();

    foreach(DataTable *table, d->tables)
        if(table->objectName().toLower() == tableName)
            return table;

    return nullptr;
}

DataTable *Report::dataTable(QString tableName, QString connectionName)
{
    Q_D(Report);
    tableName = tableName.toLower();
    connectionName = connectionName.toLower();

    foreach(DataTable *table, d->tables)
        if(table->objectName().toLower() == tableName && table->connectionName() == connectionName)
            return table;

    return nullptr;
}

void Report::removeDataTable(DataTable *table)
{
    Q_D(Report);
    d->tables.removeOne(table);
}

Parametere *Report::parameter(QString name)
{
    Q_D(Report);
    foreach(Parametere *param, d->parameters)
        if(param->objectName() == name)
            return param;
    return nullptr;
}

QList<Parametere*> Report::parameters()
{
    Q_D(Report);
    return d->parameters;
}

void Report::addParametere( QString name, QVariant value )
{
    addParametere(new Parametere(name, value));
}

void Report::addParametere( Parametere *param )
{
    Q_D(Report);
    if( !parameter(param->objectName())) {
        d->parameters.append( param );
        d->model->addParametere(param);
    }
}

void Report::setParametereValue(QString name, QVariant value)
{
    Q_D(Report);
    foreach(Parametere *param, d->parameters)
        if(param->objectName() == name)
            param->setValue(value);
}

void Report::removeParametere(Parametere *param)
{
    Q_D(Report);
    d->parameters.removeOne(param);
    d->model->removeParametere(param);
}

/**
  * Return all connections in current report
  */
QList<DataConnection*> Report::connections() const
{
    Q_D(const Report);
    return d->connections;
}

/**
  * Add new connection to report. A connection is an object of \e DataConnection type
  * that can have one or more datasource for data defention. A connection used for report
  * designing, At runtime data from QtSql module replace by this connections.
  */
void Report::addConnection(DataConnection *conn)
{
    Q_D(Report);
    if(!connection(conn->objectName())) {
//        d->model->addConnection(conn);
        d->connections.append(conn);
    }
}

void Report::removeConnection(DataConnection *conn)
{
    Q_D(Report);
    for(int i = 0; i < d->connections.count(); i++)
        if(d->connections.at(i)->objectName() == conn->objectName()){
            d->model->removeDataConnection(d->connections.at(i));
            d->connections.removeAt(i);
            break;
        }
}

void Report::setDataSource(QString dataTableName, QSqlQuery &query)
{
    Q_UNUSED(dataTableName);
    Q_UNUSED(query);
}

void Report::print()
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

PrintSettings *Report::printSetting() const
{
    return _printSetting;
}

void Report::setPrintSetting(PrintSettings *printSetting)
{
    _printSetting = printSetting;
}

/*!
  Find and return a connection named \e connectionName if there are no connection names
  \e connectionName return 0.
  */
DataConnection *Report::connection(QString connectionName)
{
    Q_D(Report);
    foreach(DataConnection *conn, d->connections)
        if(conn->objectName() == connectionName)
            return conn;

    return nullptr;
}

LEAF_END_NAMESPACE
