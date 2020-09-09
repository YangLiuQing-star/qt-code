#include "domxml.h"


DomXML::DomXML()
{

}

/*
    1.创建XML文件
    @return filePath:文件路径
 */
void DomXML::createXML(QString filePath){

    QFile file(filePath);//关联文件名字
    if(file.exists() == true){//打开成功
        cout << "文件已经存在";
        return;
    }else{
        //打开文件
        bool isOk = file.open(QIODevice::WriteOnly);

        if(isOk == true){//打开文件成功
            //创建XML文档对象
            QDomDocument doc;
            //创建格式头（进程指令）
            QDomProcessingInstruction ins;
            ins = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"");
            //追加元素
            doc.appendChild(ins);

            //创建根节点元素
            QDomElement root = doc.createElement("日销售单");
            doc.appendChild(root);

            //保存
            QTextStream stream(&file);//文本流
            doc.save(stream,4);//4:缩进4个字符
            file.close();
        }else{
            cout << "文件打开失败";
            file.close();
            return;
        }
    }
}

void DomXML::appendXML(QString filePath, QStringList ls){
    QFile file(filePath);
    //打开文件
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk == true){
        //创建XML文档对象
        QDomDocument doc;

        //文件与XML进行关联
        bool flag = doc.setContent(&file);

        if(flag == true){
            file.close();
            //获取根节点元素
            QDomElement root = doc.documentElement();

            //获取当前时间
            QDateTime date = QDateTime::currentDateTime();

            QString dateStr = date.toString("yyyy-MM-dd hh:mm:ss");
            //判断根节点下有没有子结点元素
            if(root.hasChildNodes()){//有子节点

            }else{//没有子结点
                //创建日期结点
                QDomElement dateElement = doc.createElement("日期");

                //创建date属性
                QDomAttr dateAttr = doc.createAttribute("date");
                //设置属性值
                dateAttr.setNodeValue(dateStr);

                //把结点和属性关联
                dateElement.setAttributeNode(dateAttr);

                //把新增结点加入到根节点
                root.appendChild(dateElement);

                //继续添加子节点
                writeXML(doc,root,ls);

                //保存文件
                bool isSave = file.open(QIODevice::WriteOnly);
                if(isSave == true){//保存成功
                    QTextStream stream(&file);//文本流
                    doc.save(stream,4);//4:缩进4个字符
                    file.close();
                }else{
                    file.close();
                    cout << "文件打开失败";
                }
            }

        }else{
            cout << "setContent Error";
            return;
        }

        //保存
        QTextStream stream(&file);//文本流
        doc.save(stream,4);//4:缩进4个字符


    }else{
        cout << "文件打开失败";
        return;
    }
}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &ls){

    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("hh:mm:ss");

    //创建结点元素
    QDomElement timeEmt = doc.createElement("时间");
    //创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    //给属性设置值
    timeAttr.setNodeValue(timeStr);
    //时间结点和属性结点进行绑定
    timeEmt.setAttributeNode(timeAttr);

    //把子节点添加到父结点后面
    root.appendChild(timeEmt);

    QDomElement factory = doc.createElement("厂家");
    QDomElement brand = doc.createElement("品牌");
    QDomElement price = doc.createElement("报价");
    QDomElement num = doc.createElement("数量");
    QDomElement total = doc.createElement("金额");

    QDomText factoryText = doc.createTextNode(ls.at(0));
    QDomText brandText = doc.createTextNode(ls.at(1));
    QDomText priceText = doc.createTextNode(ls.at(2));
    QDomText numText = doc.createTextNode(ls.at(3));
    QDomText totalText = doc.createTextNode(ls.at(4));

    //为结点添加文本
    factory.appendChild(factoryText);
    brand.appendChild(brandText);
    price.appendChild(priceText);
    num.appendChild(numText);
    total.appendChild(totalText);


    //为时间结点添加子节点
    timeEmt.appendChild(factory);
    timeEmt.appendChild(brand);
    timeEmt.appendChild(price);
    timeEmt.appendChild(num);
    timeEmt.appendChild(total);
}
