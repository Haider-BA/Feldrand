/* Copyright (C) 2013  Marco Heisig

This file is part of Feldrand.

Feldrand is free software: you can redistribute it and/or modify it under the
terms of the GNU Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
details.

You should have received a copy of the GNU Affero General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "MainWindow.hpp"
#include <iostream>
#include <fstream>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QKeySequence>
#include <QFileDialog>
#include <QTabWidget>
#include <thread>
#include "OpenGLWidget.hpp"
#include "AboutWindow.hpp"
#include "Simulation.hpp"

using namespace std;

namespace Feldrand {

MainWindow::MainWindow() {

    sim = make_shared<Simulation>(Simulation::create_from_image("./fau.png"));

    sim->action(Simulation::Action::run);

    using namespace std::chrono;
    QWidget* widget = new QWidget();
    setCentralWidget(widget);

    openGLWidget = new OpenGLWidget;
    openGLWidget->setSimulation(sim);

    // QTabWidget* tabWidget = new QTabWidget();
    // QWidget* infoTab = new QWidget();
    // QWidget* drawTab = new QWidget();
    // tabWidget->addTab(infoTab, QString("Info"));
    // tabWidget->addTab(drawTab, QString("Draw"));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(openGLWidget);
    // layout->addWidget(tabWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Feldrand"));
    setMinimumSize(300, 40);
    resize(560, 400);
}

void MainWindow::newFile() {
    // TODO
}

void MainWindow::open() {
    QString filename
        = QFileDialog::getOpenFileName(this, "Simulation file name",
                                       QString(),
                                       "FELDRAND Files (*.feldrand)");
    if (filename.isEmpty()) return;
    try {
        ifstream src(filename.toStdString(), ios_base::in);
        src >> (*sim);
    }
    catch (std::runtime_error e) {
        cerr << e.what() << endl;
        return;
    }
}

void MainWindow::save() {
    QString filename
        = QFileDialog::getSaveFileName(this, "Simulation file name",
                                       QString(),
                                       "FELDRAND Files (*.feldrand)");
    if (filename.isEmpty()) return;
    try {
        ofstream dest(filename.toStdString(), ios_base::out);
        dest << (*sim);
    }
    catch (std::runtime_error e) {
        cerr << e.what() << endl;
        return;
    }
}

void MainWindow::clear() {
    sim->action(Simulation::Action::clear);
}

void MainWindow::pause() {
    sim->action(Simulation::Action::pause);
}

void MainWindow::resume() {
    sim->action(Simulation::Action::run);
}

void MainWindow::colorMono() {
    openGLWidget->setColor(color_t::MONO);
}

void MainWindow::colorVelocity() {
    openGLWidget->setColor(color_t::VELOCITY);
}

void MainWindow::colorDensity() {
    openGLWidget->setColor(color_t::DENSITY);
}

void MainWindow::visPlain() {
    openGLWidget->setVisualisation(vis_t::PLAIN);
}

void MainWindow::visStreamlines() {
    openGLWidget->setVisualisation(vis_t::STREAMLINES);
}

void MainWindow::visArrows() {
    openGLWidget->setVisualisation(vis_t::ARROWS);
}

void MainWindow::visLic() {
    openGLWidget->setVisualisation(vis_t::LIC);
}

void MainWindow::screenshot() {
    openGLWidget->takeScreenshot();
}

void MainWindow::fullscreen() {
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
}

void MainWindow::about() {
    AboutWindow* p = new AboutWindow(this);
    p->show();
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new simulation"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing simulation"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the simulation to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    clearAct = new QAction(tr("Clea&r"), this);
    clearAct->setStatusTip(tr("reset the simulation to empty state"));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));

    pauseAct = new QAction(tr("&Pause"), this);
    pauseAct->setStatusTip(tr("Pause the simlation"));
    connect(pauseAct, SIGNAL(triggered()), this, SLOT(pause()));

    resumeAct = new QAction(tr("R&esume"), this);
    resumeAct->setStatusTip(tr("Resume the simulationn"));
    connect(resumeAct, SIGNAL(triggered()), this, SLOT(resume()));

    colorMonoAct = new QAction(tr("Mono color"), this);
    colorMonoAct->setStatusTip(tr("Use only a single color"));
    connect(colorMonoAct, SIGNAL(triggered()), this, SLOT(colorMono()));

    colorVelocityAct = new QAction(tr("From velocity"), this);
    colorVelocityAct->setStatusTip(tr("The simulation is colored "
                                      "based on the velocity"));
    connect(colorVelocityAct, SIGNAL(triggered()), this, SLOT(colorVelocity()));

    colorDensityAct = new QAction(tr("From density"), this);
    colorDensityAct->setStatusTip(tr("The simulation is colored "
                                      "based on the density"));
    connect(colorDensityAct, SIGNAL(triggered()), this, SLOT(colorDensity()));

    visPlainAct = new QAction(tr("Plain"), this);
    visPlainAct->setStatusTip(tr("A colormap is drawn"));
    connect(visPlainAct, SIGNAL(triggered()), this, SLOT(visPlain()));

    visStreamlinesAct = new QAction(tr("Streamlines"), this);
    visStreamlinesAct->setStatusTip(tr("Streamlines are drawn"));
    connect(visStreamlinesAct, SIGNAL(triggered()), this, SLOT(visStreamlines()));

    visArrowsAct = new QAction(tr("Arrows"), this);
    visArrowsAct->setStatusTip(tr("Arrows are drawn"));
    connect(visArrowsAct, SIGNAL(triggered()), this, SLOT(visArrows()));

    visLicAct = new QAction(tr("LIC"), this);
    visLicAct->setStatusTip(tr("Line Integrated Convolution"));
    connect(visLicAct, SIGNAL(triggered()), this, SLOT(visLic()));

	screenshotAct = new QAction(tr("Screenshot"), this);
    visLicAct->setStatusTip(tr("Take a screenshot"));
    connect(screenshotAct, SIGNAL(triggered()), this, SLOT(screenshot()));


    fullscreenAct = new QAction(tr("Fullscreen"), this);
    fullscreenAct->setShortcut(QKeySequence(Qt::Key_F11));
    fullscreenAct->setStatusTip(tr("Toggle fullscreen mode"));
    connect(fullscreenAct, SIGNAL(triggered()), this, SLOT(fullscreen()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Information about the FELDRAND software"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(clearAct);
    editMenu->addSeparator();
    editMenu->addAction(pauseAct);
    editMenu->addAction(resumeAct);

    colorMenu = menuBar()->addMenu(tr("&Color"));
    colorMenu->addAction(colorMonoAct);
    colorMenu->addAction(colorVelocityAct);
    colorMenu->addAction(colorDensityAct);

    colorMenu = menuBar()->addMenu(tr("&Visualisation"));
    colorMenu->addAction(visPlainAct);
    colorMenu->addAction(visStreamlinesAct);
    colorMenu->addAction(visArrowsAct);
    colorMenu->addAction(visLicAct);
    colorMenu->addAction(fullscreenAct);
	colorMenu->addAction(screenshotAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
}
