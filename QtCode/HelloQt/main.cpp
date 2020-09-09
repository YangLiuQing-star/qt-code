#include <QApplication>
#include <QWidget>//窗口控件基类

#include <QPushButton>

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QWidget w;
    //设置标题
    w.setWindowTitle("主要看气质");

    //创建一个按钮
    QPushButton b;
    b.setText("^_^");//给按钮设置内容
    b.setParent(&w);//指定父对象
    b.move(100,100);//移动坐标相对于父组件

    QPushButton b1(&w);
    b1.setText("abc");

    /*
     * 如果不指定父对象，对象和父对象（窗口和窗口）没有关系，各自独立
     * 如果b为a的父对象,则a放在b的上面
     *
     * 指定父对象:有两种方式:
     * 1.setParent
     * 2.通过构造函数传参
     *
     * 指定父对象，只需要父对象显示，上面的子对象自动显示
    */

    w.show();

    app.exec();
    return 0;
}
