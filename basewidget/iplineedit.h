#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include<QWidget>
#include<QLineEdit>
#include<QEvent>
#include<QKeyEvent>
#include<QString>

#define ip_max 4
class iplineedit : public QLineEdit
{
public:
    iplineedit(QWidget *parent=nullptr);
    ~iplineedit();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    QString text();
private:
    QLineEdit *m_lineedi[ip_max];
    int getIndex(QLineEdit *PLineEdit);
};

#endif // IPLINEEDIT_H
