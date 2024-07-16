#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QWidget>
#include <QListWidget>
#include <QFont>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

#include <QStyledItemDelegate>
class NoSpacingDelegate : public QStyledItemDelegate {
public:
    NoSpacingDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        QFont font = opt.font;
        font.setPointSize(18); 
        painter->setFont(font);
        painter->setPen(QColor(0, 0, 0)); 
        painter->save();
        painter->drawText(opt.rect, opt.displayAlignment, index.data().toString());
        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setWidth(size.width() - 8); 
        size.setHeight(size.height() - 8); 
        return size;
    }
};


class CustomDelegate : public QStyledItemDelegate {
public:
    CustomDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        opt.palette.setColor(QPalette::Text, QColor(0, 0, 255));       
        painter->save();
        painter->setPen(QColor(0, 0, 255)); 
        painter->drawText(opt.rect, opt.displayAlignment, index.data().toString());
        painter->restore();
    }
};


class ColorDelegate : public QStyledItemDelegate {
public:
    ColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;
        if (index.row() == 0) {
            opt.palette.setColor(QPalette::Text, QColor(0, 0, 255)); 
        } else {
            opt.palette.setColor(QPalette::Text, QColor(0, 0, 0)); 
		}
        QStyledItemDelegate::paint(painter, opt, index);
    }
};

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void SumOperatorClicked();
    void productOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clearAll();

private:   
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);
    double currentresult;
    double factorresult;
    QString SumOperator;
    QString ProductOperator;
    bool waitingForOperand;
    QLineEdit *display;
    QListWidget *listWidget;
    QFont itemFont;
    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};

#endif


