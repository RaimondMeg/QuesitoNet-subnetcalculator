#ifndef SUBNETCALCULATOR_H
#define SUBNETCALCULATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

class SubnetCalculator : public QWidget {
    Q_OBJECT

public:
    SubnetCalculator(QWidget *parent = nullptr);

private slots:
    void calcularSubneteo();

private:
    QLineEdit *ipInput;
    QLineEdit *parametroInput;
    QLabel *resultadoLabel;
    QRadioButton *hostsRadio;
    QRadioButton *cidrRadio;
    QButtonGroup *modoGroup;

    vector<int> dividirIP(const string& ip);
    string unirConPuntos(const vector<int>& octetos);
    QString calcularPorHosts(const string& ip, int hosts);
    QString calcularPorCIDR(const string& ip, int cidr);
};

#endif // SUBNETCALCULATOR_H