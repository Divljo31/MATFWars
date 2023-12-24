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
    m_leaderboardMembers.clear();
    emit menuResultClicked();
}

void Result::evaluateForLeaderboard(int score)
{
    ui->score_label->setText(QString::number(score));
    loadLeaderboardMembers();
    auto minElement = std::min_element(m_leaderboardMembers.begin(), m_leaderboardMembers.end());
    if(score<=(minElement->first)){   
        ui->congrats_label->hide();
        ui->label_2->hide();
        ui->enter_result_button->hide();
        ui->result_lineEdit->hide();
    }
    else{
        ui->congrats_label->show();
        ui->label_2->show();
        ui->enter_result_button->show();
        ui->result_lineEdit->show();
    }
}

void Result::loadLeaderboardMembers()
{
    QString appDirPath = QCoreApplication::applicationDirPath();

    std::ifstream file(appDirPath.toStdString() + "/../MATFWars/txt/leaderboard.txt");

    std::regex pattern("<li> &nbsp; (\\d+) &nbsp; (.+?) </li>");

    std::smatch matches;

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {
            if (std::regex_search(line, matches, pattern)) {

                std::string number = matches[1].str();
                std::string stringValue = matches[2].str();

                int numericValue = std::stoi(number);
                m_leaderboardMembers.push_back(std::make_pair(numericValue, stringValue));
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file in loadLeaderboardMembers()" << std::endl;
    }

}


void Result::on_enter_result_button_clicked()
{
    ui->label_2->hide();
    ui->enter_result_button->hide();
    ui->result_lineEdit->hide();
    QString playerName = ui->result_lineEdit->text();
    if(playerName.isEmpty())
        playerName = "player";
    m_leaderboardMembers.erase(std::min_element(m_leaderboardMembers.begin(), m_leaderboardMembers.end()));
    m_leaderboardMembers.push_back(std::make_pair((ui->score_label->text()).toInt(),playerName.toStdString()));
    auto comparePairs = [](const auto& a, const auto& b) {
        return a.first > b.first;
    };

    std::sort(m_leaderboardMembers.begin(), m_leaderboardMembers.end(), comparePairs);

    QString appDirPath = QCoreApplication::applicationDirPath();

    std::ofstream outputFile(appDirPath.toStdString() + "/../MATFWars/txt/leaderboard.txt");

    if (outputFile.is_open()) {

        outputFile << "<ol>" << std::endl;
        for (const auto& pair : m_leaderboardMembers) {
            outputFile << "<li> &nbsp; ";
            if(pair.first < 10)
                outputFile << "0";
            outputFile << pair.first << " &nbsp; " << pair.second << " </li>" << std::endl;
        }
        outputFile << "<ol>" << std::endl;

        outputFile.close();
    }
    else{
        std::cerr << "Error opening the file in on_enter_result_button_clicked() " << std::endl;
    }
}

