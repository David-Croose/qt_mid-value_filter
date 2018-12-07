#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

#include "midfilt.h"

#define HOLTER_MODE   0
#define ECG_MODE      1

uint8_t mode;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 刚开始默认是Holter模式
    mode = HOLTER_MODE;
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(false);

    // 现在暂时不读dat文件
    ui->checkBox->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileloc = ui->lineEdit->text();    // file location
    QString dfileloc = fileloc;
    uint32_t startline = ui->lineEdit_2->text().toInt();
    uint32_t totalline = ui->lineEdit_3->text().toInt();
    /// uint32_t readcnt = (mode == HOLTER_MODE) ? 16 : 17;

    dfileloc.remove(dfileloc.length() - strlen(".txt"), strlen(".txt"));
    dfileloc.append("__proc.txt");
    QFile dfile(dfileloc);

    if(dfile.exists() == true)
    {
        dfile.remove();
    }

    // 打开源文件，读取源文件，把源文件的内容处理后存储到目标文件
    QFile file(fileloc);
    if(file.open(QIODevice::ReadOnly) == true)
    {
        char buffer[300];
        QString line;
        QStringList list;
        data_t mid[12];
        data_t calc[ARR_CNT(mid)];
        uint32_t readcnt = 0;

        for(uint32_t i = 0; i < startline + totalline; i++)
        {
            // 略过不要的行
            if(i < startline)
            {
                continue;
            }

            // 读取一行
            memset(buffer, 0, sizeof(buffer));
            file.readLine(buffer, sizeof(buffer));
            line = QString("%1").arg(buffer);
            list = line.split(',');

            // 求出中值。第一列是时间
            memset(mid, 0, sizeof(mid));
            memset(calc, 0, sizeof(calc));
            midfilt1 (list[1].toFloat(),  &mid[0]);
            midfilt2 (list[2].toFloat(),  &mid[1]);
            midfilt3 (list[3].toFloat(),  &mid[2]);
            midfilt4 (list[4].toFloat(),  &mid[3]);
            midfilt5 (list[5].toFloat(),  &mid[4]);
            midfilt6 (list[6].toFloat(),  &mid[5]);
            midfilt7 (list[7].toFloat(),  &mid[6]);
            midfilt8 (list[8].toFloat(),  &mid[7]);
            midfilt9 (list[9].toFloat(),  &mid[8]);
            midfilt10(list[10].toFloat(), &mid[9]);
            midfilt11(list[11].toFloat(), &mid[10]);
            midfilt12(list[12].toFloat(), &mid[11]);

            // 最后的结果等于当前采样值减去中值
            if(++readcnt >= BUFFER_SIZE)
            {
                for(unsigned int i = 0; i < ARR_CNT(mid); i++)
                {
                    calc[i] = list[i + 1].toFloat() - mid[i];
                    /// calc[i] = mid[i];
                }
            }
            else
            {
                for(unsigned int i = 0; i < ARR_CNT(mid); i++)
                {
                    calc[i] = 0;
                }
            }

            // 存到新的文件
            if(dfile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            {
                QTextStream in(&dfile);
                in << list[0] << ",";
                in << calc[0] << "," << calc[1] << "," << calc[2] << "," << calc[3] << "," \
                   << calc[4] << "," << calc[5] << "," << calc[6] << "," << calc[7] << "," \
                   << calc[8] << "," << calc[9] << "," << calc[10] << "," << calc[11] << "\n";
            }
            dfile.close();
        }
    }
    file.close();
    ui->statusBar->showMessage("Done", 3000);
}

void MainWindow::on_checkBox_clicked()
{
    mode = HOLTER_MODE;
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(false);
}

void MainWindow::on_checkBox_2_clicked()
{
    mode = ECG_MODE;
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(true);
}


