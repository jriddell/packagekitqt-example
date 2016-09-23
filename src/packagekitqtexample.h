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

#ifndef PACKAGEKITQTEXAMPLE_H
#define PACKAGEKITQTEXAMPLE_H


#include "ui_packagekitqtexample.h"

#include <QMainWindow>
#include <PackageKit/Daemon>
#include <PackageKit/Transaction>

/**
 * This class serves as the main window for packagekitqtexample.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author jr <>
 * @version 0.1
 */
class packagekitqtexample : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    packagekitqtexample();

    /**
     * Default Destructor
     */
    virtual ~packagekitqtexample();

public slots:
    void clicked();
    void packageInstall(PackageKit::Transaction::Info, QString, QString);
    void packageFinished(PackageKit::Transaction::Exit, uint);

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::mainWidget m_ui;
};

#endif // PACKAGEKITQTEXAMPLE_H
