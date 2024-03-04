#include "iplineedit.h"
#include<QSizePolicy>
#include<QHBoxLayout>
#include<QLabel>
#include<QRegExp>
#include<QRegExpValidator>
#include<QEvent>
#include<QKeyEvent>
#include<QDebug>
iplineedit::iplineedit(QWidget *parent)
{   QHBoxLayout *hboxlanout =new QHBoxLayout(this);
    hboxlanout->setContentsMargins(1,1,1,1);
    QRegExp reg("(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})");
    QLabel *labelDot[3];
    QValidator *validator = new QRegExpValidator(reg, this);
    for (int i=0;i<ip_max;i++) {
         m_lineedi[i] = new QLineEdit(this);
         m_lineedi[i]->setMaxLength(3);//设置输入框框的大小（每个框最多输入3位）
         //m_lineedi[i]->alignment(Qt::AlignCenter);//让框框居中
        m_lineedi[i]->setAlignment(Qt::AlignCenter);//让框框居中
        m_lineedi[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);//保存小部件的默认布局
        m_lineedi[i]->setStyleSheet("QLineEdit { border: none; }");
        hboxlanout->addWidget(m_lineedi[i]);
        m_lineedi[i]->setValidator(validator);
        m_lineedi[i]->installEventFilter(this);//安装事件过过滤器(EventFilter),注意重写函数的时候别打错了
        //，过滤子控件事件，截获控件按键，鼠标事件
        qDebug()<<"iaaaa";
        if (i<3) {
            labelDot[i] =new QLabel;
            labelDot[i]->setText(".");
            labelDot[i]->setFixedWidth(2);
            hboxlanout->addWidget(labelDot[i]);
        }

        this->setReadOnly(true);
        m_lineedi[0]->setFocus();
        m_lineedi[0]->selectAll();

    }

}

iplineedit::~iplineedit()
{
    qDebug()<<iplineedit::text();
}

bool iplineedit::eventFilter(QObject *watched, QEvent *event)
{
    if(children().contains(watched)&&QEvent::KeyPress==event->type())
    {
        QKeyEvent *keyEvent =dynamic_cast<QKeyEvent*>(event);
        QLineEdit *pCurrent =qobject_cast<QLineEdit*>(watched);
        //通过键盘事件自动换lineedit
        switch(keyEvent->key()){
        //事件一，通过输入所需要的数据进行更换lineedit
            case Qt::Key_0:
             case Qt::Key_1:
            case Qt::Key_2:
                 case Qt::Key_3:
                 case Qt::Key_4:
                 case Qt::Key_5:
                 case Qt::Key_6:
                 case Qt::Key_7:
                 case Qt::Key_8:
        case Qt::Key_9:{
            QString strtex =pCurrent->text();
            if(strtex.length()<=3&& strtex.toInt()*10>255){
                int index =getIndex(pCurrent);
                if(index!=-1&&index!=3){
                    m_lineedi[index+1]->setFocus();
                    m_lineedi[index+1]->selectAll();

                }

            }
        return QLineEdit::eventFilter(watched,event);
        }
            break ;
        //事件二，通过键盘的左键向左边移动
        case    Qt::Key_Left :{
            if(!pCurrent->cursorPosition()){
                int index =getIndex(pCurrent);
                if(index!=-1&&index!=0){
                    m_lineedi[index-1]->setFocus();
                    int lenth =m_lineedi[index-1]->text().length();
                    m_lineedi[index-1]->setCursorPosition(lenth?lenth:0);
                   // qDebug()<<"index"<<index;
                }
            } return QLineEdit::eventFilter(watched,event);
        }break;

        case   Qt::Key_Right :{
            if(!pCurrent->cursorPosition()){
                int index =getIndex(pCurrent);
                if(index!=3&&index!=-1){
                    m_lineedi[index+1]->setFocus();
                    int lenth =m_lineedi[index+1]->text().length();
                    m_lineedi[index+1]->setCursorPosition(lenth?lenth:0);
                   // qDebug()<<"index"<<index;
                }
            }return QLineEdit::eventFilter(watched,event);
        }break;
        case Qt::Key_Backspace: //后退键
        {
            QString strText = pCurrent->text();
            if (strText.isEmpty()) {
                int index = getIndex(pCurrent);
                if (index != -1 && index !=0) {
                    m_lineedi[index-1]->setFocus();
                    int length = m_lineedi[index-1]->text().length();
                    m_lineedi[index-1]->setCursorPosition(length?length:0);
                }
            }

            return QLineEdit::eventFilter(watched, event);
        }
        break;
        case Qt::Key_Period: //就是一个点号(.)
        {
            int index = getIndex(pCurrent);
            if (index != -1 && index !=3) {
                m_lineedi[index+1]->setFocus();
                m_lineedi[index+1]->selectAll();
            }

            return QLineEdit::eventFilter(watched, event);
        }
        break;




        }

    }
}

QString iplineedit::text()
{
    QString ip;
    for (int i=0;i<ip_max;i++) {
        ip.append(m_lineedi[i]->text());
        ip.append(".");
    }
    return ip;
}
//判断当前的lineedit是哪个
int iplineedit::getIndex(QLineEdit *PLineEdit)
{
    int index=-1;
    for (int i=0;i<ip_max;i++) {
        if(PLineEdit==m_lineedi[i]){
            index=i;
            //qDebug()<<"iplineeditindex"<<index;
        }
    }
    return  index;
}
