#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
}

Result::~Result()
{
    delete ui;
}

void Result::on_menu_result_button_clicked()
{
    this->hide();
    emit menuResultClicked();
}

void Result::evaluateForLeaderboard(int score)
{
    ui->score_label->setText(QString::number(score));
    loadLeaderboardMembers();
    auto minElement = std::min_element(m_leaderboardMembers.begin(), m_leaderboardMembers.end());
    if(score>(minElement->first)){
        std::cout << "add-to-leaderboard" << std::endl;
    }
    else{
        ui->label_2->hide();
        ui->enter_result_button->hide();
        ui->result_lineEdit->hide();
    }
}

void Result::loadLeaderboardMembers()
{
    QFile file(QString::fromStdString(":/txt/leaderboard.txt"));

    std::regex pattern("<li> &nbsp; (\\d+) &nbsp; (.+?) <li>");

    std::smatch matches;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString qLine = stream.readLine();
            std::string line = qLine.toStdString();
            if (std::regex_search(line, matches, pattern)) {

                std::string number = matches[1].str();
                std::string stringValue = matches[2].str();

                int numericValue = std::stoi(number);
                m_leaderboardMembers.push_back(std::make_pair(numericValue, stringValue));

            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

