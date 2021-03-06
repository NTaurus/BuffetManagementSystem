# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'LoginWindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_LoginWindow(object):
    def setupUi(self, LoginWindow):
        LoginWindow.setObjectName("LoginWindow")
        LoginWindow.setWindowModality(QtCore.Qt.ApplicationModal)
        LoginWindow.resize(760, 500)
        LoginWindow.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)
        LoginWindow.setLayoutDirection(QtCore.Qt.LeftToRight)
        LoginWindow.setStyleSheet("")
        LoginWindow.setIconSize(QtCore.QSize(25, 25))
        LoginWindow.setToolButtonStyle(QtCore.Qt.ToolButtonFollowStyle)
        LoginWindow.setAnimated(True)
        LoginWindow.setDocumentMode(True)
        LoginWindow.setTabShape(QtWidgets.QTabWidget.Triangular)
        LoginWindow.setDockNestingEnabled(True)
        LoginWindow.setUnifiedTitleAndToolBarOnMac(True)
        self.centralWidget = QtWidgets.QWidget(LoginWindow)
        self.centralWidget.setObjectName("centralWidget")
        self.Blogin = QtWidgets.QPushButton(self.centralWidget)
        self.Blogin.setEnabled(True)
        self.Blogin.setGeometry(QtCore.QRect(330, 370, 111, 41))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(15)
        self.Blogin.setFont(font)
        self.Blogin.setMouseTracking(True)
        self.Blogin.setTabletTracking(False)
        self.Blogin.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self.Blogin.setAcceptDrops(False)
        self.Blogin.setToolTipDuration(-1)
        self.Blogin.setAutoFillBackground(False)
        self.Blogin.setStyleSheet("")
        self.Blogin.setInputMethodHints(QtCore.Qt.ImhLowercaseOnly|QtCore.Qt.ImhUppercaseOnly)
        self.Blogin.setIconSize(QtCore.QSize(25, 25))
        self.Blogin.setCheckable(False)
        self.Blogin.setChecked(False)
        self.Blogin.setAutoRepeat(False)
        self.Blogin.setAutoExclusive(False)
        self.Blogin.setAutoRepeatDelay(0)
        self.Blogin.setAutoRepeatInterval(0)
        self.Blogin.setAutoDefault(False)
        self.Blogin.setDefault(False)
        self.Blogin.setObjectName("Blogin")
        self.label = QtWidgets.QLabel(self.centralWidget)
        self.label.setGeometry(QtCore.QRect(220, 170, 81, 41))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setStyleSheet("")
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.centralWidget)
        self.label_2.setGeometry(QtCore.QRect(220, 280, 81, 41))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("")
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralWidget)
        self.label_3.setGeometry(QtCore.QRect(230, 30, 481, 41))
        font = QtGui.QFont()
        font.setFamily("????????????")
        font.setPointSize(21)
        font.setBold(True)
        font.setWeight(75)
        self.label_3.setFont(font)
        self.label_3.setStyleSheet("")
        self.label_3.setObjectName("label_3")
        self.comboBox = QtWidgets.QComboBox(self.centralWidget)
        self.comboBox.setEnabled(True)
        self.comboBox.setGeometry(QtCore.QRect(180, 370, 101, 41))
        self.comboBox.setBaseSize(QtCore.QSize(0, 0))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.comboBox.setFont(font)
        self.comboBox.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.comboBox.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)
        self.comboBox.setStyleSheet("")
        self.comboBox.setEditable(False)
        self.comboBox.setInsertPolicy(QtWidgets.QComboBox.InsertAtCurrent)
        self.comboBox.setDuplicatesEnabled(False)
        self.comboBox.setFrame(True)
        self.comboBox.setModelColumn(0)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.lineEdit = QtWidgets.QLineEdit(self.centralWidget)
        self.lineEdit.setGeometry(QtCore.QRect(310, 169, 211, 41))
        self.lineEdit.setStyleSheet("")
        self.lineEdit.setText("")
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(self.centralWidget)
        self.lineEdit_2.setGeometry(QtCore.QRect(310, 279, 211, 41))
        self.lineEdit_2.setStyleSheet("")
        self.lineEdit_2.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.comboBox_theme = QtWidgets.QComboBox(self.centralWidget)
        self.comboBox_theme.setEnabled(True)
        self.comboBox_theme.setGeometry(QtCore.QRect(490, 370, 131, 41))
        self.comboBox_theme.setBaseSize(QtCore.QSize(0, 0))
        font = QtGui.QFont()
        font.setFamily("Adobe Arabic")
        font.setPointSize(14)
        self.comboBox_theme.setFont(font)
        self.comboBox_theme.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.comboBox_theme.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)
        self.comboBox_theme.setStyleSheet("")
        self.comboBox_theme.setEditable(False)
        self.comboBox_theme.setInsertPolicy(QtWidgets.QComboBox.InsertAtCurrent)
        self.comboBox_theme.setDuplicatesEnabled(False)
        self.comboBox_theme.setFrame(True)
        self.comboBox_theme.setModelColumn(0)
        self.comboBox_theme.setObjectName("comboBox_theme")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        self.comboBox_theme.addItem("")
        LoginWindow.setCentralWidget(self.centralWidget)
        self.menuBar = QtWidgets.QMenuBar(LoginWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 760, 17))
        self.menuBar.setObjectName("menuBar")
        LoginWindow.setMenuBar(self.menuBar)
        self.statusBar = QtWidgets.QStatusBar(LoginWindow)
        self.statusBar.setObjectName("statusBar")
        LoginWindow.setStatusBar(self.statusBar)

        self.retranslateUi(LoginWindow)
        self.comboBox.setCurrentIndex(0)
        self.comboBox_theme.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(LoginWindow)

    def retranslateUi(self, LoginWindow):
        _translate = QtCore.QCoreApplication.translate
        LoginWindow.setWindowTitle(_translate("LoginWindow", "MainWindow"))
        self.Blogin.setText(_translate("LoginWindow", "??????"))
        self.label.setText(_translate("LoginWindow", "?????????"))
        self.label_2.setText(_translate("LoginWindow", "<html><head/><body><p>?????????</p></body></html>"))
        self.label_3.setText(_translate("LoginWindow", "?????????????????????"))
        self.comboBox.setItemText(0, _translate("LoginWindow", "??????"))
        self.comboBox.setItemText(1, _translate("LoginWindow", "?????????"))
        self.comboBox_theme.setItemText(0, _translate("LoginWindow", "??????"))
        self.comboBox_theme.setItemText(1, _translate("LoginWindow", "??????"))
        self.comboBox_theme.setItemText(2, _translate("LoginWindow", "?????????"))
        self.comboBox_theme.setItemText(3, _translate("LoginWindow", "??????"))
        self.comboBox_theme.setItemText(4, _translate("LoginWindow", "?????????"))
        self.comboBox_theme.setItemText(5, _translate("LoginWindow", "?????????"))
        self.comboBox_theme.setItemText(6, _translate("LoginWindow", "??????"))
        self.comboBox_theme.setItemText(7, _translate("LoginWindow", "?????????"))
        self.comboBox_theme.setItemText(8, _translate("LoginWindow", "??????"))
