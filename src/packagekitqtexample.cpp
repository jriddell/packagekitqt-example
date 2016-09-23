/*
 Copyright (C) 2016 by jr <>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation; either version 2 of
 the License or (at your option) version 3 or any later version
 accepted by the membership of KDE e.V. (or its successor approved
 by the membership of KDE e.V.), which shall act as a proxy 
 defined in Section 14 of version 3 of the license.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "packagekitqtexample.h"
#include <QDebug>

#include <AppstreamQt/database.h>
#include <AppstreamQt/component.h>

packagekitqtexample::packagekitqtexample()
    : QMainWindow()
{
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    m_ui.setupUi(widget);
    connect(m_ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(clicked()));
    m_ui.successLabel->hide();
    Appstream::Database* appstreamDatabase = new Appstream::Database();
    appstreamDatabase->open();
    QList<Appstream::Component> components = appstreamDatabase->allComponents();
    //qDebug() << components[1].name() << endl;
    foreach(Appstream::Component component, components) {
      //qDebug() << component.name() << endl;
      //qDebug() << "id: " << component.id() << endl;
      //qDebug() << component.description() << endl;
      foreach(QString packagename, component.packageNames()) {
        //qDebug() << "package name:" << packagename << endl;
        if (packagename=="kipi-plugins") {
          qDebug() << "XXX kipi-plugins id:" << component.id() << endl;
        }
      }
    }
    Appstream::Component kipiPlugins = appstreamDatabase->componentById("photolayoutseditor.desktop");
    qDebug() << "The Package: " << kipiPlugins.packageNames()[0] << endl;
}

packagekitqtexample::~packagekitqtexample()
{
}

void packagekitqtexample::clicked() {
    Appstream::Database* appstreamDatabase = new Appstream::Database();
    appstreamDatabase->open();
    Appstream::Component kipiPlugins = appstreamDatabase->componentById("photolayoutseditor.desktop");
    qDebug() << "The Package: " << kipiPlugins.packageNames()[0] << endl;
    QString package = kipiPlugins.packageNames()[0];
    
    PackageKit::Transaction *transaction = PackageKit::Daemon::resolve("kipi-plugins",
//                                                   PackageKit::Transaction::FilterNone);
                                                   PackageKit::Transaction::FilterArch);
    connect(transaction,
            SIGNAL(package(PackageKit::Transaction::Info,QString,QString)),
            SLOT(packageInstall(PackageKit::Transaction::Info,QString,QString)));
    m_ui.installProgress->setMaximum(0);
    m_ui.installProgress->setMinimum(0);
    m_ui.installProgress->show();
    m_ui.pushButton->hide();

}

void packagekitqtexample::packageInstall(PackageKit::Transaction::Info, QString packageID, QString summary) {
  qDebug() << "packageInstall()" << packageID << endl; 
  qDebug() << "packageInstall()" << summary << endl; 
    PackageKit::Transaction *installTransaction = PackageKit::Daemon::installPackage(packageID);
    connect(installTransaction,
            SIGNAL(finished(PackageKit::Transaction::Exit, uint)),
            SLOT(packageFinished(PackageKit::Transaction::Exit, uint)));
}

void packagekitqtexample::packageFinished(PackageKit::Transaction::Exit status, uint runtime) {
  qDebug() << "packageFinished() status: " << status << endl; 
  qDebug() << "packageFinished() no of seconds: " << runtime << endl; 
  if (status == PackageKit::Transaction::Exit::ExitSuccess) {
    m_ui.successLabel->setText("yay");
    m_ui.successLabel->show();
  } else {
    m_ui.successLabel->setText("nay");
    m_ui.successLabel->show();
  } 
}

