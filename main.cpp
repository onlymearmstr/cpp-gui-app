#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <QGroupBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
    }

private:
    QLabel *titleLabel;
    QLineEdit *inputLineEdit;
    QPushButton *clickButton;
    QPushButton *clearButton;
    QTextEdit *resultTextEdit;
    int clickCount;

    void setupUI() {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        titleLabel = new QLabel("C++ GUI Application", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; margin: 10px;");
        mainLayout->addWidget(titleLabel);

        QGroupBox *inputGroup = new QGroupBox("Input", this);
        QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);

        inputLineEdit = new QLineEdit(this);
        inputLineEdit->setPlaceholderText("请输入一些文字...");
        inputLineEdit->setStyleSheet("padding: 8px; font-size: 14px; border: 2px solid #3498db; border-radius: 5px;");
        inputLayout->addWidget(inputLineEdit);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        clickButton = new QPushButton("点击我", this);
        clickButton->setStyleSheet("background-color: #3498db; color: white; padding: 10px 20px; font-size: 14px; border-radius: 5px; font-weight: bold;");
        connect(clickButton, &QPushButton::clicked, this, &MainWindow::onClickButton);
        buttonLayout->addWidget(clickButton);

        clearButton = new QPushButton("清空", this);
        clearButton->setStyleSheet("background-color: #e74c3c; color: white; padding: 10px 20px; font-size: 14px; border-radius: 5px; font-weight: bold;");
        connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButton);
        buttonLayout->addWidget(clearButton);

        inputLayout->addLayout(buttonLayout);
        mainLayout->addWidget(inputGroup);

        QGroupBox *resultGroup = new QGroupBox("结果", this);
        QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);

        resultTextEdit = new QTextEdit(this);
        resultTextEdit->setReadOnly(true);
        resultTextEdit->setStyleSheet("padding: 8px; font-size: 14px; border: 2px solid #95a5a6; border-radius: 5px; background-color: #ecf0f1;");
        resultLayout->addWidget(resultTextEdit);

        mainLayout->addWidget(resultGroup);

        clickCount = 0;
        resultTextEdit->append("欢迎使用C++ GUI应用程序！");
        resultTextEdit->append("点击按钮开始使用...");

        setWindowTitle("C++ GUI Demo");
        setMinimumSize(500, 400);
        resize(600, 500);
    }

private slots:
    void onClickButton() {
        clickCount++;
        QString inputText = inputLineEdit->text();

        if (inputText.isEmpty()) {
            resultTextEdit->append(QString("\n第 %1 次点击：请先输入一些文字！").arg(clickCount));
            QMessageBox::warning(this, "提示", "请先输入一些文字！");
        } else {
            resultTextEdit->append(QString("\n第 %1 次点击：").arg(clickCount));
            resultTextEdit->append(QString("输入内容: %1").arg(inputText));
            resultTextEdit->append(QString("字符数: %1").arg(inputText.length()));
            resultTextEdit->append(QString("反转后: %1").arg(reverseString(inputText)));
        }
    }

    void onClearButton() {
        inputLineEdit->clear();
        resultTextEdit->clear();
        clickCount = 0;
        resultTextEdit->append("已清空所有内容！");
    }

    QString reverseString(const QString &str) {
        QString reversed;
        for (int i = str.length() - 1; i >= 0; --i) {
            reversed += str[i];
        }
        return reversed;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"