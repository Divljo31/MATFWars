#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();
    void evaluateForLeaderboard(int score);

signals:
    void menuResultClicked();

private slots:
    void on_menu_result_button_clicked();

    void on_enter_result_button_clicked();

private:
    void loadLeaderboardMembers();

private:
    Ui::Result *ui;
    std::vector<std::pair<int,std::string>> m_leaderboardMembers;
};

#endif // RESULT_H
