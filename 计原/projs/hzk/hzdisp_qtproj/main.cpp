#include "widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QPainter>
#include <QTextCodec>


char hzkpath[]="HZK16";
unsigned char cch[3]={211,192,0};
int offset;
int mat[16][16];
int wi=20;
int hi=20;
int italic=0;
QBrush pencolor=Qt::white;

void showHZ(unsigned char cch[]){
    unsigned char q, w;
    unsigned long offset;
    q=(cch[0]-0xA1)&0xFF;
    w=(cch[1]-0xA1)&0xFF;
    offset=(q*94+w)*32;

    FILE *hzk;
    unsigned short m[16];
    if((hzk=fopen(hzkpath,"rb"))==NULL){
        printf("Failed to open hzk16\n");
        exit(1);
    }
    fseek(hzk,offset,SEEK_SET);
    fread(m,sizeof(short),16,hzk);
        for(int i=0;i<16;i++){
        unsigned short flag=0x8000;
        for(int j=8;j<16;j++){
            if(flag>>j & m[i]){
                mat[i][j-8]=1;
            }else{
                mat[i][j-8]=0;
            }
        }
        for(int j=0;j<8;j++){
            if(flag>>j & m[i]){
                mat[i][j+8]=1;
            }else{
                mat[i][j+8]=0;
            }
        }
        //printf("\n");
    }
    fclose(hzk);
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPixmap pixmap(size());

    QPainter p(&pixmap);

    p.setRenderHint(QPainter::SmoothPixmapTransform);//消锯齿
    p.setPen(QPen(pencolor, 2, Qt::DashDotLine));//设置画笔属性
    p.setBrush(Qt::CrossPattern);//设置封闭图像的填充颜色

    int base=0;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            base=(15-i)*2*italic;
            if(mat[i][j]){
                p.drawEllipse(QPointF(wi*(j+1)+base, hi*(i+1)), wi*0.25, hi*0.25);
            }
        }
    }

    p.end();
    p.begin(this);
    p.drawPixmap(QPoint(0, 0), pixmap);
}

void Widget::mouseMoveEvent(QMouseEvent *ev){
    //强制重绘
    update();
}

void Widget::mousePressEvent(QMouseEvent *ev){

}

void Widget::mouseReleaseEvent(QMouseEvent *ev){

}

void Widget::handleButton(){
    QString str=input->text();
    myButton->setText(str);
    std::string s = str.toStdString();

    char tmp[3];
    if(s.length()>=3){
        tmp[0]=s[0];
        tmp[1]=s[1];
        tmp[2]=s[2];
    }
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");       //获取UTF-8编码对象
    QString  unicode = utf8->toUnicode(tmp,3);

    QTextCodec *gbk = QTextCodec::codecForName("GBK");          //获取GBK编码对象
    QByteArray arr=gbk->fromUnicode(unicode);                   //从Unicode编码转为自身编码类型(GBK)

    if(arr.length()>=2){
        cch[0]=arr[0];
        cch[1]=arr[1];
    }

    showHZ(cch);
    update();
}
void Widget::hzLarger(){
    wi++;
    hi++;
    update();
}
void Widget::hzSmaller(){
    wi--;
    hi--;
    update();
}
void Widget::hzItalic(){
    italic=(italic+1)%5;
    if(italic==0){
        btn_italic->setText("italic: off");
    }else if(italic==1){
        btn_italic->setText("italic: 1");
    }else if(italic==2){
        btn_italic->setText("italic: 2");
    }else if(italic==3){
        btn_italic->setText("italic: 3");
    }else if(italic==4){
        btn_italic->setText("italic: 4");
    }
    update();
}
void Widget::hzRotate(){
    int n=16;
    int tmp[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tmp[i][j]=mat[n-1-j][i];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat[i][j]=tmp[i][j];
        }
    }
    update();
}
void Widget::hzColor(){
    if(pencolor==Qt::white){
        pencolor=Qt::red;
    }else if(pencolor==Qt::red){
        pencolor=Qt::blue;
    }else if(pencolor==Qt::blue){
        pencolor=Qt::yellow;
    }else if(pencolor==Qt::yellow){
        pencolor=Qt::green;
    }else if(pencolor==Qt::green){
        pencolor=Qt::magenta;
    }else if(pencolor==Qt::magenta){
        pencolor=Qt::cyan;
    }else if(pencolor==Qt::cyan){
        pencolor=Qt::gray;
    }else{
        pencolor=Qt::white;
    }
    update();
}

int main(int argc, char *argv[])
{
    showHZ(cch);
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("hzDisp");

    w.show();
    return a.exec();
}
