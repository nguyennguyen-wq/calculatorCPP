#include "calculator.h"
#include "button.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>
#include "./ui_mainwindow.h"
#include "mainwindow.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), currentresult(0.0), listWidget(new QListWidget(this))
    , factorresult(0.0), waitingForOperand(true)
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);
    for (int i = 0; i < NumDigitButtons; ++i)
    digitButtons[i]->setStyleSheet("font: bold;background-color: white;font-size: 36px;height: 48px;width: 120px;");
 
    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
	pointButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;"
       "    color: white; 
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue;"
       "    color: black; "
       "}"
       );
	
    Button *changeSignButton = createButton(tr("\u2212"), &Calculator::changeSignClicked);
    changeSignButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue; "
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; "
       "    color: black; "
       "}"
       );
  
    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    backspaceButton->setStyleSheet("font: bold;background-color:white;color: red;font-size: 36px;height: 48px;width: 120px;"); 
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);
    clearAllButton->setStyleSheet("font: bold;background-color: white;color: red;  selection-color: yellow ;font-size: 36px;height: 48px;width: 120px;");
    Button *divisionButton = createButton(tr("\303\267"), &Calculator::productOperatorClicked);
    divisionButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue; "
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue;"
       "    color: black; "
       "}"
       );
	
    Button *timesButton = createButton(tr("\303\227"), &Calculator::productOperatorClicked);
    timesButton->setStyleSheet(
       "QToolButton {"	
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;"
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue;"
       "    color: black; "
       "}"
       );

   Button *minusButton = createButton(tr("-"), &Calculator::SumOperatorClicked); 
   minusButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;
       "    color: white; 
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; 
       "    color: black;
       "}"
       );
		
    Button *plusButton = createButton(tr("+"), &Calculator::SumOperatorClicked);
    plusButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;" 
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; "
       "    color: black; "
       "}"
       );
     
   Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
   squareRootButton->setStyleSheet("font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;");
   squareRootButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue; "
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; /* Hover state background color */"
       "    color: black; "
       "}"
       );
	  
    Button *powerButton = createButton(tr("x\302\262"), &Calculator::unaryOperatorClicked);   
    powerButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue; "
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue;"
       "    color: black; "
       "}"
       );
	
     Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
     reciprocalButton->setStyleSheet(
       "QToolButton {"
	"font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;"
       "    color: white;"
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; "
       "    color: black;"
       "}"
       );
	
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);
    equalButton->setStyleSheet(
       "QToolButton {"
	   "font: bold;background-color: navy;color: yellow;font-size: 36px;height: 48px;width: 120px;"
       "    background-color: darkblue;"
       "    color: white; "
       "}"
       "QToolButton:hover {"
       "    background-color: lightblue; "
       "    color: black; "
       "}"
       );
	
    QGridLayout *mainLayout = new QGridLayout;
    listWidget->setFixedHeight(40);
    listWidget->setViewMode(QListView::IconMode);  
    listWidget->setFlow(QListView::LeftToRight);   
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setSpacing(0);
    listWidget->setItemDelegate(new NoSpacingDelegate(this));
    itemFont.setPointSize(28);
    itemFont.setBold(true);
    mainLayout->addWidget(listWidget, 0, 0, 1, 5);
    mainLayout->addWidget(display, 0, 0, 1, 5);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 2, 1, 2);
    mainLayout->addWidget(squareRootButton, 2, 0);
    mainLayout->addWidget(powerButton, 3, 0);
    mainLayout->addWidget(reciprocalButton, 4, 0);
    mainLayout->addWidget(equalButton, 5, 0);
    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);
    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);
    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
}

void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setEchoMode(QLineEdit::NoEcho);
    display->setText(display->text() + QString::number(digitValue)   );
    QListWidgetItem *newItem = new QListWidgetItem(QString::number(digitValue));
    newItem->setSizeHint(QSize(20, 30)); 
    newItem->setFont(itemFont);
    newItem->setBackground(QBrush(QColor("red")));
    listWidget->addItem(newItem);
}

void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    QListWidgetItem *newItem = new QListWidgetItem(clickedOperator);
    listWidget->addItem(newItem);
    double operand2 = newItem->text().toDouble();
    double result ;
    if (clickedOperator == tr("Sqrt")) {    
		result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {	
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::SumOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!ProductOperator.isEmpty()) {
        if (!calculate(operand, ProductOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorresult));
        operand = factorresult;
        ProductOperator.clear();
    }
    if (!SumOperator.isEmpty()) {
        if (!calculate(operand, SumOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(currentresult));
    } else {
        currentresult = operand;
    }
    QListWidgetItem *newItem = new QListWidgetItem(clickedOperator);
    newItem->setSizeHint(QSize(20, 30)); 
    newItem->setFont(itemFont); 
    listWidget->addItem(newItem);
    SumOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::productOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!SumOperator.isEmpty()) {
        if (!calculate(operand, SumOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(currentresult));
        operand = currentresult;
        SumOperator.clear();
    }
    if (!ProductOperator.isEmpty()) {
        if (!calculate(operand, ProductOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorresult));
    } else {
        factorresult = operand;
    }
    QListWidgetItem *newItem = new QListWidgetItem(clickedOperator);
    newItem->setSizeHint(QSize(20, 30)); 
    newItem->setFont(itemFont); 
    listWidget->addItem(newItem);
    ProductOperator = clickedOperator;
    waitingForOperand = true;
}
void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    if (!ProductOperator.isEmpty()) {
        if (!calculate(operand, ProductOperator)) {
            abortOperation();
            return;
        }
        operand = factorresult;
        factorresult = 0.0;
        ProductOperator.clear();
    }
    if (!SumOperator.isEmpty()) {
        if (!calculate(operand, SumOperator)) {
            abortOperation();
            return;
        }
        SumOperator.clear();
    } else {
        currentresult = operand;
    }
    display->setEchoMode(QLineEdit::Normal);
    display->setText("= " + QString::number(currentresult));
    waitingForOperand = true;
}
void Calculator::pointClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    	QString clickedOperator =  clickedButton->text();
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
		waitingForOperand = false;
        display->setText(display->text() + tr("."));   
	QListWidgetItem *newItem = new QListWidgetItem(clickedOperator);
    newItem->setSizeHint(QSize(20, 30)); 
    newItem->setFont(itemFont); 
    listWidget->addItem(newItem);
}
void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();
	if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    QListWidgetItem *newItem = new QListWidgetItem(clickedOperator);
    newItem->setSizeHint(QSize(20, 30)); 
    newItem->setFont(itemFont); 
    listWidget->insertItem(listWidget->count() - 3, newItem);
}
void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
    if (!listWidget->count())
        return;
    delete listWidget->takeItem(listWidget->count() - 1);
}

void Calculator::clearAll()
{
    currentresult = 0.0;
    factorresult = 0.0;
    SumOperator.clear();
    ProductOperator.clear();
    display->setText("0");
    listWidget->clear();
    waitingForOperand = true;
}

template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Calculator::abortOperation()
{
	display->setEchoMode(QLineEdit::Normal);
    display->setText(tr("inf"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        currentresult += rightOperand;
    } else if (pendingOperator == tr("-")) {
        currentresult -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorresult *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorresult /= rightOperand;
    }
    return true;
}

Calculator::~Calculator()
{
    delete listWidget;
}
