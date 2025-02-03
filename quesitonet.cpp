#include "subnetcalculator.h"
#include <QApplication>
#include <QPalette>

// Función para dividir una IP en octetos
vector<int> SubnetCalculator::dividirIP(const string& ip) {
    vector<int> octetos;
    stringstream ss(ip);
    string segmento;
    while (getline(ss, segmento, '.')) {
        octetos.push_back(stoi(segmento));
    }
    return octetos;
}

// Función para unir octetos en formato de dirección IP
string SubnetCalculator::unirConPuntos(const vector<int>& octetos) {
    stringstream ss;
    for (size_t i = 0; i < octetos.size(); ++i) {
        if (i > 0) ss << ".";
        ss << octetos[i];
    }
    return ss.str();
}

// Función para calcular subneteo por número de hosts
QString SubnetCalculator::calcularPorHosts(const string& ip, int hosts) {
    int total_direcciones = hosts + 2;
    int tamano_subred = 1;
    while (tamano_subred < total_direcciones) {
        tamano_subred *= 2;
    }

    int diagonal = 32, temp = tamano_subred;
    while (temp > 1) {
        temp /= 2;
        diagonal--;
    }

    vector<int> mascara_decimal(4, 0);
    int diagonal_temp = diagonal;
    for (int i = 0; i < 4; i++) {
        if (diagonal_temp >= 8) {
            mascara_decimal[i] = 255;
            diagonal_temp -= 8;
        } else {
            mascara_decimal[i] = 256 - pow(2, (8 - diagonal_temp));
            diagonal_temp = 0;
        }
    }

    vector<int> octetos = dividirIP(ip);
    int bloque = 256 - mascara_decimal[3];
    vector<int> red = octetos;
    red[3] = (octetos[3] / bloque) * bloque;
    vector<int> broadcast = red;
    broadcast[3] += bloque - 1;
    vector<int> primera_asignable = red;
    primera_asignable[3]++;
    vector<int> ultima_asignable = broadcast;
    ultima_asignable[3]--;

    QString resultado = QString("Resultados de la subred:\n");
    resultado += "Dirección de red: " + QString::fromStdString(unirConPuntos(red)) + "\n";
    resultado += "Máscara de red: " + QString::fromStdString(unirConPuntos(mascara_decimal)) + "\n";
    resultado += "Primera dirección asignable: " + QString::fromStdString(unirConPuntos(primera_asignable)) + "\n";
    resultado += "Última dirección asignable: " + QString::fromStdString(unirConPuntos(ultima_asignable)) + "\n";
    resultado += "Dirección de broadcast: " + QString::fromStdString(unirConPuntos(broadcast)) + "\n";
    resultado += "Notación CIDR: /" + QString::number(diagonal);

    return resultado;
}

// Función para calcular subneteo por diagonal CIDR
QString SubnetCalculator::calcularPorCIDR(const string& ip, int cidr) {
    vector<int> mascara_decimal(4, 0);
    int diagonal_temp = cidr;
    for (int i = 0; i < 4; i++) {
        if (diagonal_temp >= 8) {
            mascara_decimal[i] = 255;
            diagonal_temp -= 8;
        } else {
            mascara_decimal[i] = 256 - pow(2, (8 - diagonal_temp));
            diagonal_temp = 0;
        }
    }

    vector<int> octetos = dividirIP(ip);
    int bloque = 256 - mascara_decimal[3];
    vector<int> red = octetos;
    red[3] = (octetos[3] / bloque) * bloque;
    vector<int> broadcast = red;
    broadcast[3] += bloque - 1;
    vector<int> primera_asignable = red;
    primera_asignable[3]++;
    vector<int> ultima_asignable = broadcast;
    ultima_asignable[3]--;

    QString resultado = QString("Resultados de la subred:\n");
    resultado += "Dirección de red: " + QString::fromStdString(unirConPuntos(red)) + "\n";
    resultado += "Máscara de red: " + QString::fromStdString(unirConPuntos(mascara_decimal)) + "\n";
    resultado += "Primera dirección asignable: " + QString::fromStdString(unirConPuntos(primera_asignable)) + "\n";
    resultado += "Última dirección asignable: " + QString::fromStdString(unirConPuntos(ultima_asignable)) + "\n";
    resultado += "Dirección de broadcast: " + QString::fromStdString(unirConPuntos(broadcast)) + "\n";
    resultado += "Notación CIDR: /" + QString::number(cidr);

    return resultado;
}

SubnetCalculator::SubnetCalculator(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Configuración de colores
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(48, 46, 59)); // Gunmetal
    palette.setColor(QPalette::WindowText, Qt::white);
    this->setPalette(palette);

    QLabel *titleLabel = new QLabel("<h1>QuesitoNet</h1>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;");
    layout->addWidget(titleLabel);

    ipInput = new QLineEdit(this);
    ipInput->setPlaceholderText("Ejemplo: 192.168.10.1");
    ipInput->setStyleSheet("background-color: #61647C; color: white;"); // Dark Electric Blue
    layout->addWidget(ipInput);

    QLabel *modoLabel = new QLabel("Seleccione el modo de cálculo:", this);
    modoLabel->setStyleSheet("color: white;");
    layout->addWidget(modoLabel);

    hostsRadio = new QRadioButton("Por número de hosts", this);
    hostsRadio->setStyleSheet("color: white;");
    cidrRadio = new QRadioButton("Por diagonal CIDR", this);
    cidrRadio->setStyleSheet("color: white;");

    modoGroup = new QButtonGroup(this);
    modoGroup->addButton(hostsRadio);
    modoGroup->addButton(cidrRadio);
    hostsRadio->setChecked(true);

    layout->addWidget(hostsRadio);
    layout->addWidget(cidrRadio);

    parametroInput = new QLineEdit(this);
    parametroInput->setPlaceholderText("Ingrese el valor");
    parametroInput->setStyleSheet("background-color: #61647C; color: white;"); // Dark Electric Blue
    layout->addWidget(parametroInput);

    QPushButton *calcularBtn = new QPushButton("Calcular", this);
    calcularBtn->setStyleSheet("background-color: #7C8DA6; color: white;"); // Shadow Blue
    layout->addWidget(calcularBtn);

    resultadoLabel = new QLabel(this);
    resultadoLabel->setStyleSheet("color: white;");
    layout->addWidget(resultadoLabel);

    QLabel *footerLabel = new QLabel("Made by Tortugas Ninja", this);
    footerLabel->setAlignment(Qt::AlignCenter);
    footerLabel->setStyleSheet("color: #BEB3C3;"); // Gray (X11)
    layout->addWidget(footerLabel);

    QLabel *megLabel = new QLabel("Meg is awesome", this);
    megLabel->setAlignment(Qt::AlignCenter);
    megLabel->setStyleSheet("color: #E6E6FA;"); // Lavender
    layout->addWidget(megLabel);

    connect(calcularBtn, &QPushButton::clicked, this, &SubnetCalculator::calcularSubneteo);
}

void SubnetCalculator::calcularSubneteo() {
    string ip = ipInput->text().toStdString();
    int parametro = parametroInput->text().toInt();

    QString resultado;
    if (hostsRadio->isChecked()) {
        resultado = calcularPorHosts(ip, parametro);
    } else if (cidrRadio->isChecked()) {
        resultado = calcularPorCIDR(ip, parametro);
    }

    resultadoLabel->setText(resultado);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SubnetCalculator window;
    window.setWindowTitle("QuesitoNet - Calculadora de Subneteo");
    window.resize(400, 500);
    window.show();
    return app.exec();
}